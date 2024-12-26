#pragma once
#include "SequenceSkill.h"

class Move : public SequenceSkill
{
	using Super = SequenceSkill;
public:
	Move(Creature* parent, int level = 1);
	virtual ~Move();

	virtual bool init() override;

	virtual void DoSkill(DelegateAction<> callback) override;

	void DoMove(float deltaTime);

	virtual bool SetLevel(int level) override;

	CREATE_FUNC_SKILL(Move);


};