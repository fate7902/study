#include "stdafx.h"
#include "objectManager.h"

bool ObjectManager::calcInRange(Object& objA, Object& objB)
{
    double objA_x = objA.m_x.load(), objA_y = objA.m_y.load();
    double objB_x = objB.m_x.load(), objB_y = objB.m_y.load();
    double distance = (objA_x - objB_x) * (objA_x - objB_x) +
        (objA_y - objB_y) * (objA_y - objB_y);
    if (distance <= VIEWRANGE * VIEWRANGE) return true;
    else return false;
}
