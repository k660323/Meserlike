#include "HpPortion.h"
#include "Player.h"
#include "Stat.h"

HpPortion::HpPortion(Creature* parent, SkillId skillId, int level) : Super(parent, skillId ,level)
{
    _skillId = skillId;
}

HpPortion::~HpPortion()
{
}

bool HpPortion::SetLevel(int level)
{
    bool result = Super::SetLevel(level);

    if (result)
    {
        _owner->GetStat()->SetCurHp(_owner->GetStat()->GetCurHp() + skillStatData.value);
    }

    return result;
}

bool HpPortion::init()
{
    if (!Super::init())
        return false;

    SetLevel(_level);

    return true;
}
