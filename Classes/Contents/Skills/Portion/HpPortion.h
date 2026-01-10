#pragma once
#include "Portion.h"

class HpPortion : public Portion
{
	using Super = Portion;
public:
	HpPortion(Creature* parent, SkillId skillId, int level = 1);
	virtual ~HpPortion();

	virtual bool SetLevel(int level) override;

	virtual bool init() override;

	CREATE_FUNC_SKILL_PASSIVE(HpPortion);
};