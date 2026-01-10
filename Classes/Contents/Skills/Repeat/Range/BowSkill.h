#pragma once
#include "Contents/Skills/Repeat/RepeatSkill.h"

class Range;

class BowSkill : public RepeatSkill
{
	using Super = RepeatSkill;

public:
	BowSkill(Creature* parent, int level = 1);
	virtual ~BowSkill();

	virtual bool SetLevel(int level) override;

	virtual bool init() override;

	CREATE_FUNC_SKILL(BowSkill);

protected:
	virtual void DoSkillJob() override;

private:
	// Ȱ
	Range* range;
};