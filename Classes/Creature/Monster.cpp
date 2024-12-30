#include "Monster.h"
#include "MonsterStat.h"
#include "MonsterController.h"
#include "Tags.h"
USING_NS_CC;

Monster::Monster(MonsterType monsterType) : Super()
{
    _creatureType = CreatureType::Monster;
    _monsterType = monsterType;
    // stat 클래스 생성 및 초기화
    stat = std::make_shared<MonsterStat>(this, (int)monsterType);

    setTag(Tags::Monster);
}

Monster::~Monster()
{

}

bool Monster::init()
{
    if (!Super::init())
        return false;

  

    return true;
}

void Monster::onEnter()
{
    Super::onEnter();

}

void Monster::onExit()
{
    Super::onExit();
}

MonsterType Monster::GetMonsterType()
{
    return _monsterType;
}

MonsterStat* Monster::GetMonsterStat()
{
    return dynamic_cast<MonsterStat*>(stat.get());
}

MonsterController* Monster::GetMonsterController()
{
    return dynamic_cast<MonsterController*>(controller.get());
}
