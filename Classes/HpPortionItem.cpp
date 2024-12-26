#include "HpPortionItem.h"
#include "Player.h"
#include "PlayerStat.h"
#include "PlayerController.h"
#include "Managers.h"
#include "SoundManager.h"
USING_NS_CC;

HpPortionItem::HpPortionItem()
{
    val = 50;
}

HpPortionItem::~HpPortionItem()
{
}

bool HpPortionItem::init()
{
    if (!Super::init())
        return false;

    this->setAnchorPoint(Vec2(0.5f, 0.0f));

    itemSprite = Sprite::create("WorldItem/RedPostion.png");
    itemSprite->setAnchorPoint(Vec2(0.5f, 0.5f));

    this->addChild(itemSprite);

    {
        auto material = PhysicsMaterial(0.0f, 0.0f, 0.0f);
        auto body = PhysicsBody::createBox(itemSprite->getContentSize(), material);

        // 강체의 질량 설정
        body->setMass(0.0f);
        // 동적 또는 정적 상태를 설정한다
        body->setDynamic(false);
        body->setRotationEnable(false);

        // setCategoryBitmask(int) : 충돌을 위한 카테고리를 설정한다. 
        body->setCategoryBitmask(Bitmask::WorldItem);

        // 물리 처리할 비트마스크
        body->setCollisionBitmask(Bitmask::Ignore);

        // setContactTestBitmask(int) : 어떤 카테고리와 충돌 트리거 처리
        body->setContactTestBitmask(Bitmask::Player);

        body->setEnabled(true);
        // 스프라이트에 강체 설정
        this->setPhysicsBody(body);
    }

    return true;
}

bool HpPortionItem::onContactEnter(cocos2d::PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA != this && nodeB != this)
        return false;

    auto other = (nodeA == this) ? nodeB : nodeA;
    if (other == nullptr)
        return false;

    auto player = dynamic_cast<Player*>(other);
    
    if (player == nullptr)
        return false;

    auto controller = player->GetPlayerController();
    if (controller->GetStat() == State::Dead)
        return false;

    auto stat = player->GetStat();

    if (stat->GetCurHp() >= stat->GetMaxHp())
        return false;

    stat->SetCurHp(stat->GetCurHp() + val);

    Managers::Sound()->PlaySound2D("Sound/Use.mp3");

    this->removeFromParent();

    return true;
}

void HpPortionItem::onContactExit(cocos2d::PhysicsContact& contact)
{
}
