#pragma once
#include "Contents/Skills/Repeat/RepeatSkill.h"

class Shield;

class ProjectileSheid : public RepeatSkill
{
	using Super = RepeatSkill;

public:
	ProjectileSheid(Creature* parent, int level = 1);
	virtual ~ProjectileSheid();

	virtual bool SetLevel(int level) override;

	CREATE_FUNC_SKILL(ProjectileSheid);

	virtual bool init() override;

protected:
	virtual void DoSkillJob() override;

private:
	// πÊ∆–
	Shield* shield;
};