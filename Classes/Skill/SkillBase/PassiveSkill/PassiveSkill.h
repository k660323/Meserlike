#pragma once
#include "SkillBase.h"
#include "Define.h"

class PassiveSkill : public SkillBase
{
	using Super = SkillBase;
public:
	PassiveSkill(Creature* parent, SkillId skillId, int level = 1);
	virtual ~PassiveSkill();

	virtual bool SetLevel(int level);

	virtual bool init() override;

	CREATE_FUNC_SKILL_PASSIVE(PassiveSkill);
};