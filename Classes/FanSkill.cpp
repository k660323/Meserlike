#include "FanSkill.h"
#include "Fan.h"

FanSkill::FanSkill(Creature* parent, int level) : Super(parent, level)
{
    range = nullptr;
    _skillId = SkillId::Fan;
    SetLevel(level);
}

FanSkill::~FanSkill()
{

}

bool FanSkill::SetLevel(int level)
{
    bool result = Super::SetLevel(level);

    if (result)
    {
        ActivateSkill();
    }

    return result;
}

bool FanSkill::init()
{
    if (!Super::init())
        return false;

    range = Fan::create(_owner, this);
    this->addChild(range);

    return true;
}

void FanSkill::DoSkillJob()
{
    range->Fire();
}
