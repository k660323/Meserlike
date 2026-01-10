#pragma once
#include "Range.h"

class Gun : public Range
{
	using Super = Range;
public:
	Gun(Creature* parent, SkillBase* skillBase);
	virtual ~Gun();

	virtual bool init() override;
	virtual void Fire() override;
	virtual void Ultimate() override;

	CREATE_FUNC_WEAPON(Gun);

protected:

};