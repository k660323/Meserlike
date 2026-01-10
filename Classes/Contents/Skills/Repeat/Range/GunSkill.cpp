#include "GunSkill.h"
#include "Contents/Weapon/Range/Gun.h"

GunSkill::GunSkill(Creature* parent, int level) : Super(parent, level)
{
    range = nullptr;
    _skillId = SkillId::Gun;  
    SetLevel(level);
}

GunSkill::~GunSkill()
{
}

bool GunSkill::SetLevel(int level)
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

bool GunSkill::init()
{
    if (!Super::init())
        return false;

    range = Gun::create(_owner, this);
    this->addChild(range);

    SetLevel(_level);

    return true;
}

void GunSkill::DoSkillJob()
{
    // น฿ป็
    range->Fire();
}
