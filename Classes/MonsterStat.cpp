#include "MonsterStat.h"
#include "Creature.h"
#include "DataManager.h"
#include "Managers.h"

MonsterStat::MonsterStat(Creature* owner) : Super(owner)
{
	score = 0;
	dropExp = 0;
}

MonsterStat::MonsterStat(Creature* owner, int id) : Super(owner)
{
	LoadStatData(id);
}

MonsterStat::~MonsterStat()
{
}

bool MonsterStat::LoadStatData(int id)
{
	MonsterStatData data = Managers::Data()->GetMonsterStatData(id);
	if (data.level > 0)
	{
		SetLevel(data.level);
		SetMaxHp(data.maxHp);
		SetCurHp(data.maxHp);
		atk = data.atk;
		specialAtk = data.specialAtk;
		defense = data.defense;
		moveSpeed = data.moveSpeed;
		score = data.score;
		dropExp = data.dropExp;
		
		return true;
	}

	return false;
}

int MonsterStat::GetScore()
{
	return score;
}

int MonsterStat::GetDropExp()
{
	return dropExp;
}

void MonsterStat::SetScore(int val)
{
	score = val;
}

void MonsterStat::SetDropExp(int val)
{
	dropExp = val;
}
