#include "BowSkill.h"
#include "Contents/Creature/Creature.h"
#include "Contents/Weapon/Range/Range.h"
#include "Contents/Weapon/Range/Bow.h"

BowSkill::BowSkill(Creature* parent, int level) : Super(parent, level)
{
    range = nullptr;
    _skillId = SkillId::Bow;
    SetLevel(level);
}

BowSkill::~BowSkill()
{
}

bool BowSkill::SetLevel(int level)
{
    bool result = Super::SetLevel(level);

    if (result)
    {
        ActivateSkill();
        if (level == 4)
            range->Ultimate();
    }

    return result;
}

bool BowSkill::init()
{
    if (!Super::init())
        return false;

    range = Bow::create(_owner, this);
    this->addChild(range);

    return true;
}


void BowSkill::DoSkillJob()
{
    range->Fire();
}
