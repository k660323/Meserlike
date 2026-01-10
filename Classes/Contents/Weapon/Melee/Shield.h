#pragma once
#include "Melee.h"

class Shield : public Melee
{
	using Super = Melee;

public:
	Shield(Creature* parent, SkillBase* skillBase);
	virtual ~Shield();

	virtual bool init() override;

	CREATE_FUNC_WEAPON(Shield);

protected:
	virtual bool onContactEnter(cocos2d::PhysicsContact& contact);
	virtual void onContactExit(cocos2d::PhysicsContact& contact);

protected:
	// 도끼 이미지
	cocos2d::Sprite* shieldSprite;
};