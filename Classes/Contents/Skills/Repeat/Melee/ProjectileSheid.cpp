#include "ProjectileSheid.h"
#include "Contents/Weapon/Melee/Shield.h"
#include "Manager/Managers.h"
#include "Manager/Core/SoundManager.h"
USING_NS_CC;

ProjectileSheid::ProjectileSheid(Creature* parent, int level) : Super(parent, level)
{
    _skillId = SkillId::ProjectileSheid;
}

ProjectileSheid::~ProjectileSheid()
{

}

bool ProjectileSheid::SetLevel(int level)
{
    bool result = Super::SetLevel(level);

    if (result)
    {

        ActivateSkill();
    }

    return result;
}

bool ProjectileSheid::init()
{
    if (!Super::init())
        return false;

    SetLevel(_level);

    auto shield = Shield::create(_owner, this);
    shield->setPosition(Vec2(250.0f, 0.0f));
    this->addChild(shield);

    Managers::Sound()->PlaySound2D("Sound/Skill/ShieldUse.mp3");
    return true;
}

void ProjectileSheid::DoSkillJob()
{
    // µµ³¢ È¸Àü
    float z = getRotation();
    float nextZ = z + 1 * Director::getInstance()->getDeltaTime() * skillStatData.speed;
    setRotation(nextZ);
}
