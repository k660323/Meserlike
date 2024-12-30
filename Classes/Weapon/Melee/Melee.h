#pragma once
#include "Weapon.h"

class Melee : public Weapon
{
	using Super = Weapon;

public:
	Melee(Creature* parent, SkillBase* skillBase);
	virtual ~Melee();

	virtual bool init() override;

	CREATE_FUNC_WEAPON(Melee);

protected:
	virtual bool onContactEnter(cocos2d::PhysicsContact& contact);
	virtual void onContactExit(cocos2d::PhysicsContact& contact);

protected:
	// 충돌 이벤트
	cocos2d::EventListenerPhysicsContact* contact;
};