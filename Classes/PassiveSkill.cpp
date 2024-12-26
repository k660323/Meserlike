#include "PassiveSkill.h"
#include "Creature.h"
#include "Stat.h"

PassiveSkill::PassiveSkill(Creature* parent, SkillId skillId, int level) : Super(SkillType::Buff, parent, level)
{
    _skillId = skillId;
}

PassiveSkill::~PassiveSkill()
{
}

bool PassiveSkill::SetLevel(int level)
{
    int preLevel = level;
    SkillStatData preStatData = skillStatData;

    bool result = Super::SetLevel(level);

    if (result)
    {
        // 새로운 레벨의 버프 적용
        auto stat = _owner->GetStat();

        // 이전에 적용한 버프 제거
        if (preStatData.level != 0)
        {
            stat->SetExtraMaxHp(stat->GetExtraMaxHp() - preStatData.extraMaxHp);
            stat->SetExtraAtk(stat->GetExtraAtk() - preStatData.extraAtk);
            stat->SetExtraSpecialAtk(stat->GetExtraSpecialAtk() - preStatData.extraSpecialAtk);
            stat->SetExtraDefense(stat->GetExtraDefense() - preStatData.extraDefense);
            stat->SetExtraMoveSpeed(stat->GetExtraMoveSpeed() - preStatData.extraMoveSpeed);
        }

        // 새로운 버프 적용
        stat->SetExtraMaxHp(stat->GetExtraMaxHp() + skillStatData.extraMaxHp);
        stat->SetExtraAtk(stat->GetExtraAtk() + skillStatData.extraAtk);
        stat->SetExtraSpecialAtk(stat->GetExtraSpecialAtk() + skillStatData.extraSpecialAtk);
        stat->SetExtraDefense(stat->GetExtraDefense() + skillStatData.extraDefense);
        stat->SetExtraMoveSpeed(stat->GetExtraMoveSpeed() + skillStatData.extraMoveSpeed);
    }

    return true;
}

bool PassiveSkill::init()
{
    if (!Super::init())
        return false;

    SetLevel(_level);

    return true;
}
