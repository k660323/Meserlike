#pragma once
#include "Monster.h"
#include "Interface/IHitable.h"

class BossMonsterController;
class UI_BossInfo;

class BossMonster : public Monster, public IHitable
{
	using Super = Monster;

public:
	BossMonster(MonsterType monsterType);
	virtual ~BossMonster();

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;

	virtual bool onContactEnter(cocos2d::PhysicsContact& contact) override;
	virtual void onContactExit(cocos2d::PhysicsContact& contact) override;

	virtual void OnAttacked(float damage) override;
	virtual void OnAttacked(cocos2d::Node* other, float damage) override;

	BossMonsterController* GetBossMonsterController();

	CREATE_FUNC_Monster(BossMonster);

public:
	UI_BossInfo* bossInfo;
};