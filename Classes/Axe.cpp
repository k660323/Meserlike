#include "Axe.h"
#include "Bitmask.h"
#include "IHitable.h"
#include "Creature.h"
#include "SkillBase.h"
#include "Data.h"
#include "Stat.h"
USING_NS_CC;

Axe::Axe(Creature* parent, SkillBase* skillBase) : Super(parent, skillBase)
{
    maxHitCount = 5;
}

Axe::~Axe()
{
}

bool Axe::init()
{
	if (!Super::init())
		return false;

	axeSprite = Sprite::create("Weapon/AranPolearm.png");
    axeSprite->setRotation(axeSprite->getRotation() + 45.0f);
    this->addChild(axeSprite);


    {
        auto material = PhysicsMaterial(0.0f, 0.0f, 0.0f);
        auto body = PhysicsBody::createBox(axeSprite->getContentSize() * 0.75f, material);

        // 강체의 질량 설정
        body->setMass(0.0f);
        // 동적 또는 정적 상태를 설정한다
        body->setDynamic(false);
        // setCategoryBitmask(int) : 충돌을 위한 카테고리를 설정한다. 
        body->setCategoryBitmask(Bitmask::SkillObj);

        // 물리 처리할 비트마스크
        body->setCollisionBitmask(Bitmask::Ignore);

        // setContactTestBitmask(int) : 어떤 카테고리와 충돌 트리거 처리
        body->setContactTestBitmask(Bitmask::All_InvEx);

        body->setEnabled(true);

        // 스프라이트에 강체 설정
        this->setPhysicsBody(body);
    }

    auto countAction = Sequence::create(DelayTime::create(1.0f),
        CallFunc::create([this]() {curHitCount = 0; }),
        nullptr);

    auto countRepeatAction = RepeatForever::create(countAction);
    this->runAction(countRepeatAction);

	return true;
}

bool Axe::onContactEnter(cocos2d::PhysicsContact& contact)
{
    if (curHitCount >= maxHitCount)
        return false;

    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA != this && nodeB != this)
        return false;

    auto other = (nodeA == this) ? nodeB : nodeA;

   if (other == _owner)
        return false;

    auto hitable = dynamic_cast<IHitable*>(other);
    if (hitable)
    {
        float atk = _skillBase->GetSkillStatData().atk + _owner->GetStat()->GetTotalExtraAtk();

        hitable->OnAttacked(atk);

        curHitCount++;
    }
    else
    {
        return false;
    }

    return true;
}

void Axe::onContactExit(cocos2d::PhysicsContact& contact)
{

}
