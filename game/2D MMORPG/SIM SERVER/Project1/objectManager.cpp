#include "stdafx.h"
#include "objectManager.h"

ObjectManager::ObjectManager()
{
    m_player = new concurrent_unordered_map<int, Player>;
    m_zone = new concurrent_unordered_set<int>[ZONE];
    m_zoneMutex = new mutex[ZONE];
}

ObjectManager::~ObjectManager()
{
    delete m_player;
    delete[] m_zone;
    delete[] m_zoneMutex;
}

bool ObjectManager::calcInRange(Object& objA, Object& objB)
{
    double objA_x = objA.m_x.load(), objA_y = objA.m_y.load();
    double objB_x = objB.m_x.load(), objB_y = objB.m_y.load();
    double distance = (objA_x - objB_x) * (objA_x - objB_x) +
        (objA_y - objB_y) * (objA_y - objB_y);
    if (distance <= VIEWRANGE * VIEWRANGE) return true;
    else return false;
}
