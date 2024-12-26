#include "FullCircleShot.h"
#include "Creature.h"
#include "Managers.h"
#include "Data.h"
#include "DataManager.h"
#include "Bullet.h"
#include "Managers.h"
#include "SceneEx.h"
#include "Utils.h"

FullCircleShot::FullCircleShot(Creature* parent, int level) : Super(parent, level)
{
    _skillId = SkillId::FullCircleShot;
    fireAdd = 30.0f;
    fireDelay = 0.2f;
    SetLevel(level);
}

FullCircleShot::~FullCircleShot()
{
}

bool FullCircleShot::init()
{
    if (!Super::init())
        return false;

    return true;
}

void FullCircleShot::DoSkill(DelegateAction<> callback)
{
    Super::DoSkill(callback);

    fireAngle = 0.0f;
    _owner->schedule(CC_CALLBACK_1(FullCircleShot::DoFullCircleShot, this), "DoSkill");
}

void FullCircleShot::DoFullCircleShot(float deltaTime)
{
    elapsed += deltaTime;

    if (fireAngle > 360.0f)
    {
        if (elapsed >= 2.0f)
        {
            _owner->unschedule("DoSkill");
            this->callback.invoke();
        }
        return;
    }

    if (elapsed >= fireDelay)
    {
        elapsed = 0.0f;
        auto bullet = Bullet::create(_owner, this);
        bullet->setPosition(_owner->getPosition());
        cocos2d::Vec2 dir = Utils::RotateVec2(Vec2(1, 0), fireAngle);
        bullet->SetLifeTime(5.0f);
        bullet->Fire(dir);
        Managers::Scene()->GetCurrentScene()->AddObjectLayer(bullet);
        fireAngle += fireAdd;
    }

}

bool FullCircleShot::SetLevel(int level)
{
    bool result = Super::SetLevel(level);

    if (result)
    {
        fireDelay = skillStatData.cooltime;
    }

    return result;
}
