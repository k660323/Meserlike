#pragma once
#include "Contents/Skills/SkillBase.h"
#include "Contents/Ex/DelegateAction.h"

class SequenceSkill : public SkillBase
{
	using Super = SkillBase;
public:
	SequenceSkill(Creature* parent, int level = 1);
	virtual ~SequenceSkill();


	virtual bool init() override;

	virtual void DoSkill(DelegateAction<> callback);

protected:
	float elapsed = 0.0f;
	DelegateAction<> callback;
};