#pragma once
#include "Contents/Skills/SkillBase.h"


class RepeatSkill : public SkillBase
{
	using Super = SkillBase;
public:
	RepeatSkill(Creature* parent, int level = 1);
	virtual ~RepeatSkill();

	virtual bool SetLevel(int level);

	virtual bool init() override;

	virtual void ActivateSkill() override;

	virtual void DoSkillJob() = 0;

protected:
	virtual void StartSkillAction();

protected:
	cocos2d::Action* skillAction;
};