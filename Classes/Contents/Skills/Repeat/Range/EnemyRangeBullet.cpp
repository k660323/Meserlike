#include "EnemyRangeBullet.h"
#include "Contents/Weapon/Projectile/Bullet.h"
#include "Manager/Managers.h"
#include "Manager/Core/DataManager.h"
#include "Manager/Contents/GameManager.h"
#include "Contents/Creature/Player.h"
#include "Scene/SceneEx.h"

EnemyRangeBullet::EnemyRangeBullet(Creature* parent, int level) : Super(parent, level)
{
    _skillId = SkillId::EnemyRangeBullet;
    SetLevel(level);
}

EnemyRangeBullet::~EnemyRangeBullet()
{

}

bool EnemyRangeBullet::SetLevel(int level)
{
    bool result = Super::SetLevel(level);

    if (result)
    {
        ActivateSkill();
    }

    return result;
}


bool EnemyRangeBullet::init()
{
    if (!Super::init())
        return false;


    return true;
}

void EnemyRangeBullet::StartSkillAction()
{
    DoSkillJob();
}

void EnemyRangeBullet::DoSkillJob()
{
    // ÃÑ¾Ë »ý¼º
    auto* bullet = Bullet::create(_owner, this);
    bullet->setPosition(_owner->getPosition());
    Managers::Scene()->GetCurrentScene()->AddObjectLayer(bullet);
    
    cocos2d::Vec2 dir = (Managers::Game()->GetPlayer()->getPosition() - _owner->getPosition()).getNormalized();
    bullet->SetLifeTime(3.0f);
    bullet->Fire(dir);

}
