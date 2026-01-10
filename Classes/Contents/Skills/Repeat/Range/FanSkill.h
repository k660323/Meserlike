#pragma once
#include "Contents/Skills/Repeat/RepeatSkill.h"
#include "Contents/Weapon/Range/Range.h"

class FanSkill : public RepeatSkill
{
	using Super = RepeatSkill;
public:
	FanSkill(Creature* parent, int level);
	virtual ~FanSkill();

	virtual bool SetLevel(int level) override;

	virtual bool init() override;

	CREATE_FUNC_SKILL(FanSkill);

protected:
	virtual void DoSkillJob() override;

private:
	// รั
	Range* range;
};