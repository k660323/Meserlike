#include "SpawnWeapon.h"

SpawnWeapon::SpawnWeapon(Creature* parent, SkillBase* skillBase) : Super(parent, skillBase)
{
}

SpawnWeapon::~SpawnWeapon()
{
}

bool SpawnWeapon::init()
{
    if (!Super::init())
        return false;

    return true;
}

bool SpawnWeapon::Attack()
{
    return false;
}

bool SpawnWeapon::DetectedNearObject(cocos2d::PhysicsWorld& world, cocos2d::PhysicsShape& shape, void* userData)
{
    return false;
}
