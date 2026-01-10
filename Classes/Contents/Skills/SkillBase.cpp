#include "SkillBase.h"
#include "Contents/Creature/Creature.h"

USING_NS_CC;

SkillBase::SkillBase(SkillType skillType, Creature* parent, int level) : _skillType(skillType), _owner(parent), _level(level)
{

}

SkillBase::~SkillBase()
{
	_owner = nullptr;
	
}


bool SkillBase::SetLevel(int level)
{
	_level = level;

	auto skillInfo = Managers::Data()->GetSkillInfoData(_skillId);
	auto skillDatas = skillInfo.skillDatas;
	if (skillDatas.find(level) != skillDatas.end())
	{
		skillStatData = skillDatas[level];

		return true;
	}
}

int SkillBase::GetLevel()
{
	return _level;
}

void SkillBase::ActivateSkill()
{
}

void SkillBase::StartDestroy(float delaySeconds)
{
}

void SkillBase::StopDestory()
{
}

SkillStatData SkillBase::GetSkillStatData()
{
	return skillStatData;
}

SkillType SkillBase::GetSkillType()
{
	return _skillType;
}

cocos2d::Node* SkillBase::GetOwner()
{
	return _owner;
}

Creature* SkillBase::GetCreatureOwner()
{
	return _owner;
}

void SkillBase::GenerateProjectile(int templateID, Creature* owner, cocos2d::Vec2 startPos, cocos2d::Vec2 dir, cocos2d::Vec2 targetPos)
{
}
