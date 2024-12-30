#include "Dash.h"
#include "Managers.h"
#include "DataManager.h"
#include "Data.h"
#include "Creature.h"
#include "Utils.h"
#include "Stat.h"
#include "GameManager.h"
#include "Player.h"
#include "Data.h"
USING_NS_CC;

Dash::Dash(Creature* parent, int level) : Super(parent, level)
{
    _skillId = SkillId::Dash;
    SetLevel(level);
}

Dash::~Dash()
{
}

bool Dash::init()
{
    if (!Super::init())
        return false;

    return true;
}

void Dash::DoSkill(DelegateAction<> callback)
{
    Super::DoSkill(callback);
   
    _owner->GetStat()->SetExtraAtk(_owner->GetStat()->GetExtraAtk() + skillStatData.extraAtk);
    _owner->schedule(CC_CALLBACK_1(Dash::DoDash, this), "DoSkill");
}

void Dash::DoDash(float deltaTime)
{
    elapsed += deltaTime;

    if (elapsed <= 1.5f)
    {
        Vec2 dir = (Managers::Game()->GetPlayer()->getPosition() - _owner->getPosition()).getNormalized();
        _owner->SetDir(Utils::XDir(dir.x));
        targetPosition = (Managers::Game()->GetPlayer()->getPosition() + dir * random(1, 4));
        return;
    }

    float remainingDistance = _owner->getPosition().distance(targetPosition);

    if (remainingDistance <= 1.0f)
    {
        if(_owner)
            _owner->GetStat()->SetExtraAtk(_owner->GetStat()->GetExtraAtk() - skillStatData.extraAtk);
        _owner->unschedule("DoSkill");
        this->callback.invoke();
        return;
    }

    Vec2 dirVec = targetPosition - _owner->getPosition();
    float moveSpeed = _owner->GetStat()->GetTotalMoveSpeed();
    Vec2 nextVec = _owner->getPosition() + dirVec.getNormalized() * moveSpeed * skillStatData.speed * deltaTime;

    // 만약 nextVec이 targetPosition을 넘어갈 경우 targetPosition에 정확히 위치하게 설정
    if (nextVec.distance(targetPosition) > remainingDistance)
    {
        if (_owner)
            _owner->GetStat()->SetExtraAtk(_owner->GetStat()->GetExtraAtk() - skillStatData.extraAtk);
        
        nextVec = targetPosition; // 목표 위치로 바로 이동
        _owner->setPosition(nextVec);

        _owner->unschedule("DoSkill");
        this->callback.invoke();
        return;
    }

    _owner->setPosition(nextVec);
}

bool Dash::SetLevel(int level)
{
    bool result = Super::SetLevel(level);

    return result;
}
