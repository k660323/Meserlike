#pragma once
#include "cocos2d.h"
#include "Define.h"
#include "SkillBase.h"
#include "Creature.h"

class Weapon : public cocos2d::Node
{
	using Super = cocos2d::Node;

public:
	Weapon(Creature* parent, SkillBase* skillBase);
	virtual ~Weapon();

	virtual bool init() override;
	virtual void Ultimate();

	CREATE_FUNC_WEAPON(Weapon);

protected:
	Creature* _owner;
	SkillBase* _skillBase;
	cocos2d::Action* ultimateAction;

	float spawnDistance;

	bool limitCount;
	int curHitCount;
	int maxHitCount;
};