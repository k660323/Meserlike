#pragma once
#include "cocos2d.h"
#include "Define.h"
#include "Managers.h"
#include "DataManager.h"
#include "Data.h"

class Creature;

namespace cocos2d
{
	class Vec2;
	class Action;
}

class SkillBase : public cocos2d::Node
{
public:
	SkillBase(SkillType skillType, Creature* parent, int level = 1);
	virtual ~SkillBase();

	virtual bool SetLevel(int level);
	int GetLevel();

	virtual void ActivateSkill();

	void StartDestroy(float delaySeconds);
	void StopDestory();

	SkillStatData GetSkillStatData();

	SkillType GetSkillType();

	cocos2d::Node* GetOwner();
	Creature* GetCreatureOwner();
protected:
	virtual void GenerateProjectile(int templateID, Creature* owner, cocos2d::Vec2 startPos, cocos2d::Vec2 dir, cocos2d::Vec2 targetPos);

protected:
	Creature* _owner;
	SkillType _skillType;
	SkillId _skillId;

	int _level;
	SkillStatData skillStatData;
};