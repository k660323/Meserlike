#pragma once
#include "Melee.h"

class Axe : public Melee
{
	using Super = Melee;

public:
	Axe(Creature* parent, SkillBase* skillBase);
	virtual ~Axe();

	virtual bool init() override;

	CREATE_FUNC_WEAPON(Axe);

protected:
	virtual bool onContactEnter(cocos2d::PhysicsContact& contact);
	virtual void onContactExit(cocos2d::PhysicsContact& contact);

protected:
	// 도끼 이미지
	cocos2d::Sprite* axeSprite;

};