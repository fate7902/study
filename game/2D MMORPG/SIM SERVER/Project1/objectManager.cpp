#include "stdafx.h"
#include "objectManager.h"

ObjectManager::ObjectManager()
{    
    m_zone = new concurrent_unordered_set<int>[ZONE];
    m_zoneMutex = new mutex[ZONE / ZONEGROUP];    
    for (int i = 0; i < MAXMONSTERSPECIES; ++i) {
        m_luaState[i] = luaL_newstate();
        luaL_openlibs(m_luaState[i]);
        if (luaL_loadfile(m_luaState[i], "monster.lua") || lua_pcall(m_luaState[i], 0, 0, 0)) {
            cout << "[��ƽ�ũ��Ʈ ����] " << lua_tostring(m_luaState[i], -1) << "\n";
        }
    }
    m_bZone = new atomic<bool>[ZONE];
    monsterInitialize();
}

ObjectManager::~ObjectManager()
{
    delete[] m_zone;
    delete[] m_zoneMutex;
    for (int i = 0; i < MAXMONSTERSPECIES; ++i) {
        lua_close(m_luaState[i]);
    }
    delete[] m_bZone;
}

void ObjectManager::monsterInitialize()
{
    cout << "[Loading] ���� �ʱ�ȭ��\n";
    for (int i = MAXUSER; i < MAXUSER + MAXMONSTER; ++i) {
        m_monster.insert(make_pair(i, make_shared<Monster>(i, 100)));
        m_monster[i]->initialize();
    }
    cout << "[Finished] ���� �ʱ�ȭ �Ϸ�\n";
}

double ObjectManager::calcInRange(const shared_ptr<Object>& objA, const shared_ptr<Object>& objB)
{
    double objA_x = objA->m_x.load(), objA_y = objA->m_y.load();
    double objB_x = objB->m_x.load(), objB_y = objB->m_y.load();
    double distance = (objA_x - objB_x) * (objA_x - objB_x) +
        (objA_y - objB_y) * (objA_y - objB_y);
    return distance;    
}

void ObjectManager::changeZone(int zoneNumber, int key)
{
    shared_ptr<Player> playerPtr = m_player[key];
    if (playerPtr != nullptr) {
        if (playerPtr->m_zone / ZONEGROUP != zoneNumber / ZONEGROUP) {
            int oldZone = playerPtr->m_zone;
            int oldZoneGroup = playerPtr->m_zone / ZONEGROUP;
            m_zoneMutex[oldZoneGroup].lock();
            m_zone[oldZone].unsafe_erase(key);
            m_zoneMutex[oldZoneGroup].unlock();
            playerPtr->m_zone = zoneNumber;
            m_zone[zoneNumber].insert(key);
        }
    }
}

void ObjectManager::checkViewAtPlayer(int zoneNumber, int key, unsigned time)
{
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            int currentZone = zoneNumber + x + (MAPWIDTH / ZONESIZE) * y;
            if (currentZone < 0 || currentZone > 399 || (currentZone % 19 == 0 && x == 1) || (currentZone % 20 == 0 && x == -1)) continue;
            int currentZoneGroup = currentZone / ZONEGROUP;
            m_zoneMutex[currentZoneGroup].lock();
            concurrent_unordered_set<int> copylist = m_zone[currentZone];
            m_zoneMutex[currentZoneGroup].unlock();
            for (const auto& id : copylist) {
                if (id == key) continue;
                // ����
                if (id < MAXUSER) {                    
                    double distance = calcInRange(m_player[key], m_player[id]);
                    // �þ� �� + �þ� ����Ʈ�� ���� X
                    if (distance <= VIEWRANGE * VIEWRANGE) {                        
                        if (m_player[key]->m_viewlist->find(id) == m_player[key]->m_viewlist->end()) {
                            m_player[key]->m_viewlist->insert(id);
                            m_player[key]->sendAddObjectPacket(m_player[id]);
                            m_player[id]->m_viewlist->insert(key);
                            m_player[id]->sendAddObjectPacket(m_player[key]);
                        }
                        // �þ� �� + �þ� ����Ʈ�� ���� O
                        else {
                            m_player[id]->sendMoveAllowPacket(m_player[key], time);
                        }
                    }
                    else {
                        // �þ� �� + �þ� ����Ʈ�� ���� O
                        if (m_player[key]->m_viewlist->find(id) != m_player[key]->m_viewlist->end()) {
                            m_player[key]->m_viewlistMutex.lock();
                            m_player[key]->m_viewlist->unsafe_erase(id);
                            m_player[key]->m_viewlistMutex.unlock();
                            m_player[key]->sendDeleteObjectPacket(id);
                            m_player[id]->m_viewlistMutex.lock();
                            m_player[id]->m_viewlist->unsafe_erase(key);
                            m_player[id]->m_viewlistMutex.unlock();
                            m_player[id]->sendDeleteObjectPacket(key);
                        }
                    }                    
                }
                // ����
                else {
                    double distance = calcInRange(m_player[key], m_monster[id]);
                    // �þ� �� + �þ� ����Ʈ�� ���� X
                    if (distance <= VIEWRANGE * VIEWRANGE) {
                        if (m_player[key]->m_viewlist->find(id) == m_player[key]->m_viewlist->end()) {
                            m_player[key]->m_viewlist->insert(id);
                            m_player[key]->sendAddObjectPacket(m_monster[id]);
                        }
                    }
                    // �þ� �� + �þ� ����Ʈ�� ���� O
                    else {
                        if (m_player[key]->m_viewlist->find(id) != m_player[key]->m_viewlist->end()) {
                            m_player[key]->m_viewlistMutex.lock();
                            m_player[key]->m_viewlist->unsafe_erase(id);
                            m_player[key]->m_viewlistMutex.unlock();
                            m_player[key]->sendDeleteObjectPacket(id);
                        }
                    }
                }
            }
        }
    }
}

void ObjectManager::checkViewAtMonster(int zoneNumber, int key)
{
    bool findTarget = false;
    int currentTargetDistance = CHASERANGE * CHASERANGE + 1;
    if (m_monster[key]->m_monsterType == MONSTERTYPE::HARD && m_monster[key]->m_monsterState == MONSTERSTATE::IDLE) {
        findTarget = true;
    }

    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            int currentZone = zoneNumber + x + (MAPWIDTH / ZONESIZE) * y;
            if (currentZone < 0 || currentZone > 399 || (currentZone % 19 == 0 && x == 1) || (currentZone % 20 == 0 && x == -1)) continue;
            int currentZoneGroup = currentZone / ZONEGROUP;
            m_zoneMutex[currentZoneGroup].lock();
            concurrent_unordered_set<int> copylist = m_zone[currentZone];
            m_zoneMutex[currentZoneGroup].unlock();
            for (const auto& id : copylist) {  
                // ������
                if (id >= MAXUSER) continue;                
                double distance = calcInRange(m_monster[key], m_player[id]);
                // �����Ÿ� ���̸� ��ŵ
                if (distance > CHASERANGE * CHASERANGE) continue;
                // �þ� ��
                if (distance <= VIEWRANGE * VIEWRANGE) {
                    // �þ� ����Ʈ�� ���� X
                    if (m_player[id]->m_viewlist->find(key) == m_player[id]->m_viewlist->end()) {
                        m_player[id]->m_viewlist->insert(key);
                        m_player[id]->sendAddObjectPacket(m_monster[key]);
                    }
                    // �þ� ����Ʈ�� ���� O
                    else {
                        m_player[id]->sendMoveAllowPacket(m_monster[key], 0);
                    }
                }
                // �þ� ��
                else {
                    // �þ� ����Ʈ�� ���� O
                    if (m_player[id]->m_viewlist->find(key) != m_player[id]->m_viewlist->end()) {
                        m_player[id]->m_viewlistMutex.lock();
                        m_player[id]->m_viewlist->unsafe_erase(key);
                        m_player[id]->m_viewlistMutex.unlock();
                        m_player[id]->sendDeleteObjectPacket(key);
                    }
                }

                // ���� ����� ã�� ������ ���
                // ���� ���캸�� �������� �Ÿ��� ���� ���� ������� �ľ�
                if (findTarget) {
                    if (currentTargetDistance > distance) {
                        currentTargetDistance = distance;
                        m_monster[key]->m_targetID = id;
                    }
                }
            }
        }
    }

    // ���� ����� ã�� ��� ���������� ����
    if (findTarget && m_monster[key]->m_targetID != -1) {
        m_monster[key]->m_monsterState = MONSTERSTATE::CHASE;
    }
    // ���� ���� �����̳� �ش� ���� �����Ÿ� ������ ��� ��� ���÷� ����
    else if (!findTarget && m_monster[key]->m_targetID != -1) {
        int targetID = m_monster[key]->m_targetID;
        if (calcInRange(m_monster[key], m_player[targetID]) > CHASERANGE * CHASERANGE) {
            m_monster[key]->m_monsterState = MONSTERSTATE::IDLE;
            m_monster[key]->m_targetID = -1;
        }
    }
}

void ObjectManager::checkFirstVisitZone(int zoneNumber)
{
    bool expected = false;
    if (m_bZone[zoneNumber].compare_exchange_strong(expected, true)) {
        for (int i = MAXUSER; i < MAXUSER + MAXMONSTER; ++i) {
            if (m_monster[i]->m_zone != zoneNumber) continue;
            TIMER timer;
            timer.activeID = i;
            timer.eventType = EVENTTYPE::RESPAWN;
            timer.actTime = system_clock::now() + 1000ms;
            m_timer.push(timer);
        }
    }
}
