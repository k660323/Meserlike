#pragma once
#include "RepeatSkill.h"
#include "Define.h"


class RepeatSpeedBuff : public RepeatSkill
{
	using Super = RepeatSkill;

public:
	RepeatSpeedBuff(Creature* parent, int level = 1);
	virtual ~RepeatSpeedBuff();

	virtual bool SetLevel(int level) override;

	CREATE_FUNC_SKILL(RepeatSpeedBuff);

	virtual bool init() override;

protected:
	virtual void StartSkillAction() override;

	virtual void DoSkillJob() override;

private:
	bool flag;
};