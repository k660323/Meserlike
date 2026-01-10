#pragma once
#include "Stat.h"

class MonsterStat : public Stat
{
	using Super = Stat;
public:
	MonsterStat(Creature* owner);
	MonsterStat(Creature* owner, int id);
	virtual ~MonsterStat();

	virtual bool LoadStatData(int id) override;

	int GetScore();
	int GetDropExp();

	void SetScore(int val);
	void SetDropExp(int val);

protected:
	int score;
	int dropExp;
};