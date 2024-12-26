#include "Portion.h"

Portion::Portion(Creature* parent, SkillId skillId, int level) : Super(SkillType::Portion, parent, level)
{
    
}

Portion::~Portion()
{
}

bool Portion::SetLevel(int level)
{
    bool result = Super::SetLevel(level);

    return result;
}

bool Portion::init()
{
    if (!Super::init())
        return false;

    return true;
}
