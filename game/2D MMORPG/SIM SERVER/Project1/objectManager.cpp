#include "stdafx.h"
#include "objectManager.h"

ObjectManager::ObjectManager()
{
    m_player = new concurrent_unordered_map<int, Player>;
    m_monster = new concurrent_unordered_map<int, Monster>;
    m_zone = new concurrent_unordered_set<int>[ZONE];
    m_zoneMutex = new mutex[ZONE];
    monsterInitialize();
}

ObjectManager::~ObjectManager()
{
    delete m_player;
    delete m_monster;
    delete[] m_zone;
    delete[] m_zoneMutex;
}

void ObjectManager::monsterInitialize()
{
    cout << "[Loading] 몬스터 초기화중\n";
    for (int i = MAXUSER; i < MAXUSER + MAXMONSTER; ++i) {
        m_monster->insert(make_pair(i, Monster(i, 100)));
        (*m_monster)[i].initialize();
    }
}

double ObjectManager::calcInRange(Object& objA, Object& objB)
{
    double objA_x = objA.m_x.load(), objA_y = objA.m_y.load();
    double objB_x = objB.m_x.load(), objB_y = objB.m_y.load();
    double distance = (objA_x - objB_x) * (objA_x - objB_x) +
        (objA_y - objB_y) * (objA_y - objB_y);
    return distance;    
}

void ObjectManager::changeZone(int zoneNumber, int key)
{
    if ((*m_player)[key].m_zone != zoneNumber) {
        int oldZone = (*m_player)[key].m_zone;
        m_zoneMutex[oldZone].lock();
        m_zone[oldZone].unsafe_erase(key);
        m_zoneMutex[oldZone].unlock();
        (*m_player)[key].m_zone = zoneNumber;
        m_zone[zoneNumber].insert(key);
    }
}

void ObjectManager::checkViewlist(int key, unsigned time)
{
    concurrent_unordered_set<int> oldlist = *((*m_player)[key].m_viewlist);
    for (const auto& id : oldlist) {
        if (id < MAXUSER) {
            double distance = calcInRange((*m_player)[key], (*m_player)[id]);
            if (distance > VIEWRANGE * VIEWRANGE) {
                // 이동 유저의 viewlist 처리
                (*m_player)[key].m_viewlistMutex.lock();
                (*m_player)[key].m_viewlist->unsafe_erase(id);
                (*m_player)[key].m_viewlistMutex.unlock();
                (*m_player)[key].sendDeleteObjectPacket(id);

                // 처리한 유저의 viewlist 처리
                (*m_player)[id].m_viewlistMutex.lock();
                (*m_player)[id].m_viewlist->unsafe_erase(key);
                (*m_player)[id].m_viewlistMutex.unlock();
                (*m_player)[id].sendDeleteObjectPacket(key);
            }
            else {
                (*m_player)[id].sendMoveAllowPacket((*m_player)[key], time);
            }
        }
        else {
            double distance = calcInRange((*m_player)[key], (*m_monster)[id]);
            if (distance > VIEWRANGE * VIEWRANGE) {
                // 이동 유저의 viewlist 처리
                (*m_player)[key].m_viewlistMutex.lock();
                (*m_player)[key].m_viewlist->unsafe_erase(id);
                (*m_player)[key].m_viewlistMutex.unlock();
                (*m_player)[key].sendDeleteObjectPacket(id);
            }
        }
    }
}

void ObjectManager::checkPlayerZone(int zoneNumber, int key)
{
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            int currentZone = zoneNumber + x + (MAPWIDTH / ZONESIZE) * y;
            if (currentZone < 0 || currentZone > 399 || (currentZone % 19 == 0 && x == 1) || (currentZone % 20 == 0 && x == -1)) continue;
            m_zoneMutex[currentZone].lock();
            concurrent_unordered_set<int> copylist = m_zone[currentZone];
            m_zoneMutex[currentZone].unlock();            
            for (const auto& id : copylist) {
                if (id == key) continue;
                if ((*m_player)[key].m_viewlist->find(id) != (*m_player)[key].m_viewlist->end()) continue;
                if (id < MAXUSER) {
                    double distance = calcInRange((*m_player)[key], (*m_player)[id]);
                    if (distance > VIEWRANGE * VIEWRANGE) continue;
                    (*m_player)[key].m_viewlist->insert(id);
                    (*m_player)[key].sendAddObjectPacket((*m_player)[id]);
                    (*m_player)[id].m_viewlist->insert(key);
                    (*m_player)[id].sendAddObjectPacket((*m_player)[key]);
                }
                else {
                    double distance = calcInRange((*m_player)[key], (*m_monster)[id]);
                    if (distance > VIEWRANGE * VIEWRANGE) continue;
                    (*m_player)[key].m_viewlist->insert(id);
                    (*m_player)[key].sendAddObjectPacket((*m_monster)[id]);
                }
            }
        }
    }
}

void ObjectManager::checkMonsterZone(int zoneNumber, int key)
{    
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            int currentZone = zoneNumber + x + (MAPWIDTH / ZONESIZE) * y;
            if (currentZone < 0 || currentZone > 399 || (currentZone % 19 == 0 && x == 1) || (currentZone % 20 == 0 && x == -1)) continue;
            m_zoneMutex[currentZone].lock();
            concurrent_unordered_set<int> copylist = m_zone[currentZone];
            m_zoneMutex[currentZone].unlock();
            int preDistance = VIEWRANGE * VIEWRANGE + 1;
            for (const auto& id : copylist) {
                if (id < MAXUSER){
                    double distance = calcInRange((*m_monster)[key], (*m_player)[id]);
                    // 유저 시야 리스트에 존재안하는 경우
                    if ((*m_player)[id].m_viewlist->find(key) != (*m_player)[id].m_viewlist->end()) {
                        // 이번 몬스터의 이동으로 인해 유저의 시야범위에 들어감
                        // 몬스터의 타입과 상태에 따라 추적할 대상인지 탐색
                        // 오브젝트 생성패킷 전송
                        if (distance <= VIEWRANGE * VIEWRANGE) {
                            if ((*m_monster)[key].m_monsterType == MONSTERTYPE::HARD && (*m_monster)[key].m_monsterState == MONSTERSTATE::IDLE) {
                                if (preDistance > distance) {
                                    preDistance = distance;
                                    (*m_monster)[key].m_targetID = id;
                                }
                            }
                            (*m_player)[id].m_viewlist->insert(key);
                            (*m_player)[id].sendAddObjectPacket((*m_monster)[key]);
                        }
                    }
                    else {
                        // 시야 리스트에 존재하나 이번 이동으로 시야를 벗어나면 삭제
                        if (distance > VIEWRANGE * VIEWRANGE) {
                            (*m_player)[id].m_viewlistMutex.lock();
                            (*m_player)[id].m_viewlist->unsafe_erase(key);
                            (*m_player)[id].m_viewlistMutex.unlock();
                            (*m_player)[id].sendDeleteObjectPacket(key);
                        }
                        // 시야 리스트에 존재하고 여전히 시야범위일 경우
                        // 몬스터의 타입과 상태에 따라 추적상대 탐색
                        else {
                            if ((*m_monster)[key].m_monsterType == MONSTERTYPE::HARD && (*m_monster)[key].m_monsterState == MONSTERSTATE::IDLE) {
                                if (preDistance > distance) {
                                    preDistance = distance;
                                    (*m_monster)[key].m_targetID = id;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
