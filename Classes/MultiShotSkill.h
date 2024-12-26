#pragma once
#include "RepeatSkill.h"

class Bullet;

class MultiShotSkill : public RepeatSkill
{
	using Super = RepeatSkill;
public:
	MultiShotSkill(Creature* parent, int level = 1);
	virtual ~MultiShotSkill();

	virtual bool SetLevel(int level) override;

	CREATE_FUNC_SKILL(MultiShotSkill);

	virtual bool init() override;

protected:
	virtual void StartSkillAction() override;

	virtual void DoSkillJob() override;
};