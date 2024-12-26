#include "EnemyRangeBullet.h"
#include "Bullet.h"
#include "Managers.h"
#include "GameManager.h"
#include "Player.h"
#include "SceneEx.h"
#include "DataManager.h"

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
