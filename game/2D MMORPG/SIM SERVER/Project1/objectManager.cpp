#include "stdafx.h"
#include "objectManager.h"

bool ObjectManager::calcInRange(Object& objA, Object& objB)
{
    int objA_x = objA.m_x.load(), objA_y = objA.m_y.load();
    int objB_x = objB.m_x.load(), objB_y = objB.m_y.load();
    int distance = (objA_x - objB_x) * (objA_x - objB_x) +
        (objA_y - objB_y) * (objA_y - objB_y);
    if (distance <= VIEWRANGE * VIEWRANGE) return true;
    else return false;
}
