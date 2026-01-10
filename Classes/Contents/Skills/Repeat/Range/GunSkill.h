#pragma once
#include "Contents/Skills/Repeat/RepeatSkill.h"

class Range;

class GunSkill : public RepeatSkill
{
	using Super = RepeatSkill;

public:
	GunSkill(Creature* parent, int level = 1);
	virtual ~GunSkill();

	virtual bool SetLevel(int level) override;

	CREATE_FUNC_SKILL(GunSkill);

	virtual bool init() override;

protected:
	virtual void DoSkillJob() override;

private:
	// รั
	Range* range;

};