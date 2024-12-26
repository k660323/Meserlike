#pragma once
#include "Creature.h"

class MonsterStat;
class MonsterController;

class Monster : public Creature
{
	using Super = Creature;
public:
	Monster(MonsterType monsterType);
	virtual ~Monster();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	MonsterType GetMonsterType();
	MonsterStat* GetMonsterStat();
	MonsterController* GetMonsterController();

	CREATE_FUNC_Monster(Monster);


protected:
	MonsterType _monsterType;
};