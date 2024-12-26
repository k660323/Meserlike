#pragma once
#include "Define.h"
#include "cocos2d.h"

#include "SkillBase.h"
#include "SpinningAX.h"
#include "EnemyRangeBullet.h"
#include "RepeatSpeedBuff.h"
#include "MultiShotSkill.h"
#include "GunSkill.h"
#include "BowSkill.h"
#include "FanSkill.h"
#include "ProjectileSheid.h"

#include "PassiveSkill.h"

#include "Portion.h"
#include "HpPortion.h"

#include "Move.h"
#include "Dash.h"
#include "FullCircleShot.h"

class SkillDefine
{
public:
	static SkillBase* AddSkill(SkillId skillId, Creature* parent, int level = 1)
	{
		int id = static_cast<int>(skillId);

		SkillBase* skillBase;

		if (0 <= id && id < 1000)
		{
			skillBase = RepeatSkill(skillId, parent, level);
		}
		else if (1000 <= id && id < 2000)
		{
			skillBase = BuffSkill(skillId, parent, level);
		}
		else if (2000 <= id && id < 3000)
		{
			skillBase = SequenceSkill(skillId, parent,level);
		}
		else if (3000 <= id && id < 4000)
		{
			skillBase = PortionSkill(skillId, parent, level);
		}
		else if (4000 <= id && id < 5000)
		{
			skillBase = RepeatSkill(skillId, parent, level);
		}

		return skillBase;
	}

	static SkillBase* RepeatSkill(SkillId skillId, Creature* parent, int level = 1)
	{
		switch (skillId)
		{
		case SkillId::None:
			break;
		case SkillId::SpinningAX:
			return SpinningAX::create(parent, level);
		case SkillId::EnemyRangeBullet:
			return EnemyRangeBullet::create(parent, level);
		case SkillId::RepeatSpeedBuff:
			return RepeatSpeedBuff::create(parent, level);
		case SkillId::MultiShot:
			return MultiShotSkill::create(parent, level);
		case SkillId::Gun:
			return GunSkill::create(parent, level);
		case SkillId::Bow:
			return BowSkill::create(parent, level);
		case SkillId::Fan:
			return FanSkill::create(parent, level);
		case SkillId::ProjectileSheid:
			return ProjectileSheid::create(parent, level);
		default:
			break;
		}

		return nullptr;
	}

	static SkillBase* BuffSkill(SkillId skillId, Creature* parent, int level = 1)
	{
		return PassiveSkill::create(parent, skillId, level);
	}

	static SkillBase* PortionSkill(SkillId skillId, Creature* parent, int level = 1)
	{
		switch (skillId)
		{
		case SkillId::HpPortion:
			return HpPortion::create(parent, skillId, level);
		}

		return nullptr;
	}

	static SkillBase* SequenceSkill(SkillId skillId, Creature* parent, int level = 1)
	{
		switch (skillId)
		{
		case SkillId::Move:
			return Move::create(parent, level);
		case SkillId::Dash:
			return Dash::create(parent, level);
		case SkillId::FullCircleShot:
			return FullCircleShot::create(parent, level);
		default:
			break;
		}

		return nullptr;
	}
};