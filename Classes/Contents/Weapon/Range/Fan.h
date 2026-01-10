#pragma once
#include "Range.h"

class Fan : public Range
{
	using Super = Range;
public:
	Fan(Creature* parent, SkillBase* skillBase);
	virtual ~Fan();

	virtual bool init() override;
	virtual void Fire() override;

	CREATE_FUNC_WEAPON(Fan);

protected:
};