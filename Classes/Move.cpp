#include "Move.h"
#include "cocos2d.h"
#include "Managers.h"
#include "GameManager.h"
#include "Player.h"
#include "DataManager.h"
#include "Data.h"
#include "Utils.h"
#include "Stat.h"
USING_NS_CC;

Move::Move(Creature* parent, int level) : Super(parent, level)
{
    _skillId = SkillId::Move;
    SetLevel(level);
}

Move::~Move()
{

}

bool Move::init()
{
    if (!Super::init())
        return false;

    return true;
}

void Move::DoSkill(DelegateAction<> callback)
{
    Super::DoSkill(callback);

    _owner->schedule(CC_CALLBACK_1(Move::DoMove, this), "DoSkill");
}

void Move::DoMove(float deltaTime)
{
    elapsed += deltaTime;

    if (elapsed > 5.0f)
    {
        _owner->unschedule("DoSkill");
        this->callback.invoke();
        return;
    }

    Vec2 dir = (Managers::Game()->GetPlayer()->getPosition() - _owner->getPosition()).getNormalized();
    _owner->SetDir(Utils::XDir(dir.x));
    Vec2 targetPosition = (Managers::Game()->GetPlayer()->getPosition() + dir * random(1, 4));


    if (_owner->getPosition().distance(targetPosition) <= 0.2f)
    {
        _owner->unschedule("DoSkill");
        this->callback.invoke();
        return;
    }

    Vec2 dirVec = targetPosition - _owner->getPosition();
    float moveSpeed = _owner->GetStat()->GetTotalMoveSpeed();
    Vec2 nextVec = dirVec.getNormalized() * moveSpeed * deltaTime;

    _owner->setPosition(_owner->getPosition() + nextVec);

}

bool Move::SetLevel(int level)
{
    bool result = Super::SetLevel(level);

    return result;
}
