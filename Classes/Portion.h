#pragma once
#include "SkillBase.h"

class Portion : public SkillBase
{
	using Super = SkillBase;
public:
	Portion(Creature* parent, SkillId skillId, int level = 1);
	virtual ~Portion();

	virtual bool SetLevel(int level);

	virtual bool init() override;

	CREATE_FUNC_SKILL_PASSIVE(Portion);
};