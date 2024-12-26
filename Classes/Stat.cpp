#include "Stat.h"

Stat::Stat(Creature* owner) : _owner(owner)
{
	level = 0;
	curHp = 0;
	maxHp = 0;
	extraMaxHp = 0;
	atk = 0;
	extraAtk = 0;
	specialAtk = 0;
	extraSpecialAtk = 0;
	defense = 0;
	extraDefense = 0;
	moveSpeed = 0;
	extraMoveSpeed = 0;
}

Stat::~Stat()
{
	_owner = nullptr;
}

Creature* Stat::GetOwner()
{
	return _owner;
}

int Stat::GetLevel()
{
	return level;
}

float Stat::GetCurHp()
{
	return curHp;
}

float Stat::GetMaxHp()
{
	return maxHp;
}

float Stat::GetExtraMaxHp()
{
	return extraMaxHp;
}

float Stat::GetTotalMaxHp()
{
	return maxHp + extraMaxHp;
}

float Stat::GetAtk()
{
	return atk;
}

float Stat::GetExtraAtk()
{
	return extraAtk;
}

float Stat::GetTotalExtraAtk()
{
	return atk + extraAtk;
}

float Stat::GetSpecialAtk()
{
	return specialAtk;
}

float Stat::GetExtraSpecialAtk()
{
	return extraSpecialAtk;
}

float Stat::GetTotalSpecialAtk()
{
	return specialAtk + extraSpecialAtk;
}

float Stat::GetDefense()
{
	return defense;
}

float Stat::GetExtraDefense()
{
	return extraDefense;
}

float Stat::GetTotalDefense()
{
	return defense + extraDefense;
}

float Stat::GetMoveSpeed()
{
	return moveSpeed;
}

float Stat::GetExtraMoveSpeed()
{
	return extraMoveSpeed;
}

float Stat::GetTotalMoveSpeed()
{
	return moveSpeed + extraMoveSpeed;
}

void Stat::SetLevel(int val)
{
	level = std::max(0, val);
	levelDelegate.invoke(val);
}

void Stat::SetCurHp(float val)
{
	curHp = std::min(std::max(0.0f, val), GetTotalMaxHp());
	curHpDelegate.invoke(curHp, maxHp + extraMaxHp);
}

void Stat::SetMaxHp(float val)
{
	maxHp = std::max(0.0f, val);
	maxHpDelegate.invoke(curHp, maxHp + extraMaxHp);
}

void Stat::SetExtraMaxHp(float val)
{
	extraMaxHp = val;
	maxHpDelegate.invoke(curHp, maxHp + val);
}

void Stat::SetAtk(float val)
{
	atk = std::max(0.0f, val);
}

void Stat::SetExtraAtk(float val)
{
	extraAtk = val;
}

void Stat::SetSpecialAtk(float val)
{
	specialAtk = std::max(0.0f, val);
}

void Stat::SetExtraSpecialAtk(float val)
{
	extraSpecialAtk = val;
}

void Stat::SetDefense(float val)
{
	defense = std::max(0.0f, val);
}

void Stat::SetExtraDefense(float val)
{
	extraDefense = val;
}

void Stat::SetMoveSpeed(float val)
{
	moveSpeed = std::max(0.0f, val);
}

void Stat::SetExtraMoveSpeed(float val)
{
	extraMoveSpeed = val;
}

void Stat::Clear()
{
	curHpDelegate.removeAllCallback();
	levelDelegate.removeAllCallback();
	maxHpDelegate.removeAllCallback();
}
