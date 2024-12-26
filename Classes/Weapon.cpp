#include "Weapon.h"

USING_NS_CC;

Weapon::Weapon(Creature* parent, SkillBase* skillBase) : _owner(parent), _skillBase(skillBase)
{
	ultimateAction = nullptr;
	spawnDistance = 0.0f;
	curHitCount = 0;
	maxHitCount = 1;
	limitCount = true;
}

Weapon::~Weapon()
{
	_owner = nullptr;
	_skillBase = nullptr;
}

bool Weapon::init()
{
	if (!Super::init())
		return false;



	return true;
}

void Weapon::Ultimate()
{
}
