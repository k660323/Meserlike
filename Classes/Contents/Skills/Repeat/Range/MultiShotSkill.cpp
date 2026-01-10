#include "MultiShotSkill.h"
#include "Contents/Weapon/Projectile/Bullet.h"
#include "Manager/Managers.h"
#include "Manager/Contents/GameManager.h"
#include "Contents/Creature/Player.h"
#include "Scene/SceneEx.h"
#include "Utils.h"
USING_NS_CC;

MultiShotSkill::MultiShotSkill(Creature* parent, int level) : Super(parent, level)
{
    _skillId = SkillId::MultiShot;
    SetLevel(level);
}

MultiShotSkill::~MultiShotSkill()
{
}

bool MultiShotSkill::SetLevel(int level)
{
    bool result = Super::SetLevel(level);

    if (result)
    {
        ActivateSkill();
    }

    return result;
}


bool MultiShotSkill::init()
{
    if (!Super::init())
        return false;

    return true;
}

void MultiShotSkill::StartSkillAction()
{
    DoSkillJob();
}

void MultiShotSkill::DoSkillJob()
{
    // ÃÑ¾Ë »ý¼º
   Vec2 dir = (Managers::Game()->GetPlayer()->getPosition() - _owner->getPosition()).getNormalized();
   dir = Utils::RotateVec2(dir, -45);
   

    for (int i = 0; i < 3; i++)
    {
        auto bullet = Bullet::create(_owner, this);
        bullet->setPosition(_owner->getPosition());
        Managers::Scene()->GetCurrentScene()->AddObjectLayer(bullet);
        bullet->SetLifeTime(3.0f);
        bullet->Fire(dir);

        dir = Utils::RotateVec2(dir, 45);
    }
}
