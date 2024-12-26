#pragma once
#include "SequenceSkill.h"

class Dash : public SequenceSkill
{
	using Super = SequenceSkill;
public:
	Dash(Creature* parent, int level = 1);
	virtual ~Dash();

	virtual bool init() override;

	virtual void DoSkill(DelegateAction<> callback);

	virtual void DoDash(float deltaTime);

	virtual bool SetLevel(int level) override;

	CREATE_FUNC_SKILL(Dash);

protected:
	cocos2d::Vec2 targetPosition;
};