#pragma once
#include "cocos2d.h"
#include "Define.h"
#include "memory"
#include "DelegateAction.h"

class AnimateEx;
class Stat;
class BaseController;
class SkillBook;


class Creature : public cocos2d::Node
{
	using Super = Node;
public:
	Creature();
	virtual ~Creature();

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;

	virtual bool onContactEnter(cocos2d::PhysicsContact& contact);
	virtual void onContactExit(cocos2d::PhysicsContact& contact);

	CREATE_FUNC(Creature);

	Dir GetDir();
	void SetDir(Dir dir);
	void FlipDir();

	AnimateEx* GetAnimateEx();
	
	Stat* GetStat();
	BaseController* GetBaseController();
	SkillBook* GetSkillBook();
	void StopHitAction();
public:
	DelegateAction<> deadAction;

protected:
	Dir dir;

	cocos2d::Sprite* cSprite;

	std::shared_ptr<AnimateEx> animateEx;

	CreatureType _creatureType;

	std::shared_ptr<Stat> stat;
	std::shared_ptr<BaseController> controller;
	std::shared_ptr<SkillBook> skillBook;

	cocos2d::Action* invincibilityAction;

	cocos2d::EventListenerPhysicsContact* contact;
};