#include "Range.h"

USING_NS_CC;

Range::Range(Creature* parent, SkillBase* skillBase) : Super(parent, skillBase)
{
    curCooltime = 0;
    closestDistance = std::numeric_limits<float>::max();
    closestBody = nullptr;
    firePosition = Vec2(0, 0);
    dir = Vec2(1, 0);
}

Range::~Range()
{
}

bool Range::init()
{
    if (!Super::init())
        return false;

    return true;
}

void Range::Fire()
{

}

bool Range::DetectedNearObject(cocos2d::PhysicsWorld& world, cocos2d::PhysicsShape& shape, void* userData)
{
    // 오브젝트의 바디를 가져옴
    PhysicsBody* body = shape.getBody();
    Vec2 objectPosition = body->getPosition();
   
    if (body->getNode() == _owner)
        return true;

    Creature* target = dynamic_cast<Creature*>(body->getNode());
    if (target == nullptr)
        return true;

    // 유저 와 오브젝트간 위치 간의 거리 계산
    float distance = _owner->getPosition().distance(objectPosition);

    // 가장 가까운 오브젝트 갱신
    if (distance < closestDistance)
    {
        closestDistance = distance;
        closestBody = body;
    }

    // true를 반환하면 계속 검색, false를 반환하면 중단
    return true;
}

