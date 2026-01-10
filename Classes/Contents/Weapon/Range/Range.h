#pragma once
#include "Contents/Weapon/Weapon.h"
#include "Contents/Weapon/Projectile/Projectile.h"
#include "cocos2d.h"
#include "Manager/Core/SceneManager.h"
#include "Scene/SceneEx.h"

class Range : public Weapon
{
	using Super = Weapon;

public:
	Range(Creature* parent, SkillBase* skillBase);
	virtual ~Range();

	virtual bool init() override;
	virtual void Fire();

	virtual bool DetectedNearObject(cocos2d::PhysicsWorld& world, cocos2d::PhysicsShape& shape, void* userData);

	CREATE_FUNC_WEAPON(Range);

protected:
	cocos2d::Sprite* rangeSprite;
	cocos2d::Vec2 firePosition;

	Projectile* fireObj;
	float curCooltime;

	float closestDistance;
	cocos2d::PhysicsBody* closestBody; 

	cocos2d::Vec2 dir;

	cocos2d::Vec2 detectRange;
};