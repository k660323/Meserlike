#include "RepeatSkill.h"
#include "Creature.h"
#include "cocos2d.h"

USING_NS_CC;

RepeatSkill::RepeatSkill(Creature* parent, int level) : Super(SkillType::Repeat, parent, level), skillAction(nullptr)
{
    
}

RepeatSkill::~RepeatSkill()
{
}

bool RepeatSkill::SetLevel(int level)
{
    return Super::SetLevel(level);
}

bool RepeatSkill::init()
{
    if (!Super::init())
        return false;


    return true;
}

void RepeatSkill::ActivateSkill()
{
    if (skillAction != nullptr)
    {
        _owner->stopAction(skillAction);
    }

    auto action = Sequence::create(
        CallFunc::create(CC_CALLBACK_0(RepeatSkill::StartSkillAction, this)),
        DelayTime::create(skillStatData.cooltime),
        nullptr
    );

    skillAction = RepeatForever::create(action);

    _owner->runAction(skillAction);
}

void RepeatSkill::StartSkillAction()
{
    DoSkillJob();
}
