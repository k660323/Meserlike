#include "Shield.h"
#include "Bitmask.h"
#include "Contents/Weapon/Projectile/Projectile.h"
#include "Manager/Managers.h"
#include "Manager/Core/SoundManager.h"
USING_NS_CC;

Shield::Shield(Creature* parent, SkillBase* skillBase) : Super(parent, skillBase)
{
}

Shield::~Shield()
{
}

bool Shield::init()
{
    if (!Super::init())
        return false;

    shieldSprite = Sprite::create("Weapon/Shield.png");
    // shieldSprite->setRotation(axeSprite->getRotation() + 45.0f);
    this->addChild(shieldSprite);

    {
        auto material = PhysicsMaterial(0.0f, 0.0f, 0.0f);
        auto body = PhysicsBody::createBox(shieldSprite->getContentSize(), material);

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

    return true;
}

bool Shield::onContactEnter(cocos2d::PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA != this && nodeB != this)
        return false;

    auto other = (nodeA == this) ? nodeB : nodeA;

    if (other == _owner)
        return false;

    auto projectile = dynamic_cast<Projectile*>(other);
    if (projectile)
    {
        if (projectile->GetOwner() != _owner)
        {
            Managers::Sound()->PlaySound2D("Sound/Skill/ShieldDamage.mp3");
            projectile->removeFromParent();
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

void Shield::onContactExit(cocos2d::PhysicsContact& contact)
{
}
