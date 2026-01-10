#pragma once
#include "Monster.h"
#include "Interface/IHitable.h"

class NormalMonsterController;

class NormalMonster : public Monster, public IHitable
{
	using Super = Monster;

public:
	NormalMonster(MonsterType monsterType);
	virtual ~NormalMonster();

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;

	virtual bool onContactEnter(cocos2d::PhysicsContact& contact) override;
	virtual void onContactExit(cocos2d::PhysicsContact& contact) override;

	virtual void OnAttacked(float damage) override;
	virtual void OnAttacked(cocos2d::Node* other, float damage) override;

	NormalMonsterController* GetNormalMonsterController();

	CREATE_FUNC_Monster(NormalMonster);

private:

};