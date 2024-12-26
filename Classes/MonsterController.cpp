#include "MonsterController.h"
#include "Monster.h"

MonsterController::MonsterController(Creature* owner) : Super(owner)
{
	
}

MonsterController::~MonsterController()
{
	_target = nullptr;
}

Monster* MonsterController::GetMonsterOwner()
{
	return dynamic_cast<Monster*>(_owner);
}

void MonsterController::SetTarget(Creature* target)
{
	_target = target;
}