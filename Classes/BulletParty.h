#pragma once
#include "SpawnWeapon.h"

class BulletParty : public SpawnWeapon
{
	using Super = SpawnWeapon;
public:
	BulletParty(Creature* parent, SkillBase* skillBase);
	virtual ~BulletParty();

	virtual bool init() override;

	virtual bool Attack() override;

	virtual bool DetectedNearObject(cocos2d::PhysicsWorld& world, cocos2d::PhysicsShape& shape, void* userData) override;

	CREATE_FUNC_WEAPON(BulletParty);

protected:
	float closestDistance;
	cocos2d::PhysicsBody* closestBody;
	float damage;

	int soundId;
};