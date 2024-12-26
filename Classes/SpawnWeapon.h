#pragma once
#include "Weapon.h"

class Creature;
class SkillBase;

class SpawnWeapon : public Weapon
{
	using Super = Weapon;
public:
	SpawnWeapon(Creature* parent, SkillBase* skillBase);
	virtual ~SpawnWeapon();

	virtual bool init() override;

	virtual bool Attack();

	virtual bool DetectedNearObject(cocos2d::PhysicsWorld& world, cocos2d::PhysicsShape& shape, void* userData);

	CREATE_FUNC_WEAPON(SpawnWeapon);

protected:
	float damage;
};