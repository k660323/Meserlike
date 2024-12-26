#pragma once
#include "SequenceSkill.h"

class FullCircleShot : public SequenceSkill
{
	using Super = SequenceSkill;
public:
	FullCircleShot(Creature* parent, int level = 1);
	virtual ~FullCircleShot();

	virtual bool init() override;

	virtual void DoSkill(DelegateAction<> callback);

	virtual void DoFullCircleShot(float deltaTime);

	virtual bool SetLevel(int level) override;

	CREATE_FUNC_SKILL(FullCircleShot);

protected:
	float fireAngle;
	float fireAdd;
	float fireDelay;
};