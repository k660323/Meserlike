#include "RepeatSpeedBuff.h"
#include "Contents/Creature/Creature.h"
#include "Contents/Stat/Stat.h"
#include "Manager/Managers.h"
#include "Manager/Core/DataManager.h"

RepeatSpeedBuff::RepeatSpeedBuff(Creature* parent, int level) : Super(parent, level)
{
    _skillId = SkillId::RepeatSpeedBuff;
    flag = false;
    SetLevel(level);
}

RepeatSpeedBuff::~RepeatSpeedBuff()
{
}

bool RepeatSpeedBuff::SetLevel(int level)
{
    bool result = Super::SetLevel(level);

    if (result)
    {
        ActivateSkill();
    }

    return result;
}

bool RepeatSpeedBuff::init()
{
    if (!Super::init())
        return false;

    return true;
}

void RepeatSpeedBuff::StartSkillAction()
{
    DoSkillJob();
}

void RepeatSpeedBuff::DoSkillJob()
{
    auto stat = _owner->GetStat();

    if (flag)
    {
        stat->SetExtraMoveSpeed(stat->GetExtraMoveSpeed() - skillStatData.extraMoveSpeed);
    }
    else
    {
        stat->SetExtraMoveSpeed(stat->GetExtraMoveSpeed() + skillStatData.extraMoveSpeed);
    }

    flag = !flag;
}
