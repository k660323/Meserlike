#include "SequenceSkill.h"

SequenceSkill::SequenceSkill(Creature* parent, int level) : Super(SkillType::Sequence, parent)
{
}

SequenceSkill::~SequenceSkill()
{
}

bool SequenceSkill::init()
{
    if (!Super::init())
        return false;


    return true;
}

void SequenceSkill::DoSkill(DelegateAction<> callback)
{
    this->callback = callback;

    elapsed = 0.0f;

}
