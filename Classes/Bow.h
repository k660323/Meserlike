#pragma once
#include "Range.h"

class Bow : public Range
{
	using Super = Range;
public:
	Bow(Creature* parent, SkillBase* skillBase);
	virtual ~Bow();

	virtual bool init() override;
	virtual void Fire() override;

	CREATE_FUNC_WEAPON(Bow);

protected:

};