#pragma once
#include "RepeatSkill.h"

class Bullet;

class EnemyRangeBullet : public RepeatSkill
{
	using Super = RepeatSkill;
public:
	EnemyRangeBullet(Creature* parent, int level = 1);
	virtual ~EnemyRangeBullet();

	virtual bool SetLevel(int level) override;

	CREATE_FUNC_SKILL(EnemyRangeBullet);

	virtual bool init() override;

protected:
	virtual void StartSkillAction() override;

	virtual void DoSkillJob() override;

private:
};