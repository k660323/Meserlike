#pragma once
#include "Contents/Skills/Repeat/RepeatSkill.h"
#include "Define.h"

class Axe;

class SpinningAX : public RepeatSkill
{
	using Super = RepeatSkill;

public:
	SpinningAX(Creature* parent, int level = 1);
	virtual ~SpinningAX();

	virtual bool SetLevel(int level) override;

	CREATE_FUNC_SKILL(SpinningAX);

	virtual bool init() override;

protected:
	virtual void DoSkillJob() override;

private:
	// µµ³¢
	std::vector<Axe*> axes;
};