#include "Gun.h"
#include "cocos2d.h"
#include "Utils.h"
#include "Contents/Weapon/Projectile/Bullet.h"
#include "Contents/Weapon/SpawnWeapon/BulletParty.h"
#include "Manager/Managers.h"
#include "Manager/Core/SoundManager.h"
USING_NS_CC;

Gun::Gun(Creature* parent, SkillBase* skillBase) : Super(parent, skillBase)
{
    spawnDistance = 75;
    detectRange = Vec2(900, 600);
}

Gun::~Gun()
{
}

bool Gun::init()
{
    if (!Super::init())
        return false;

    rangeSprite = Sprite::create("Weapon/Gun.png");
    rangeSprite->setPosition(spawnDistance * Vec2(1, 0));
    rangeSprite->setScale(1.5f);
    this->addChild(rangeSprite);

    return true;
}

void Gun::Fire()
{
    if (_owner == nullptr)
        return;

    closestBody = nullptr; // 가장 가까운 오브젝트
    closestDistance = std::numeric_limits<float>::max(); // 최소 거리

    // _owner의 위치를 월드 좌표로 변환
    Vec2 ownerWorldPos = _owner->getParent()->convertToWorldSpace(_owner->getPosition());

    // 사각형 영역에서 queryRect 수행
    Managers::Scene()->GetCurrentScene()->getPhysicsWorld()->queryRect(CC_CALLBACK_3(Gun::DetectedNearObject, this), cocos2d::Rect(ownerWorldPos.x - (detectRange.x / 2) , ownerWorldPos.y - (detectRange.y / 2), detectRange.x, detectRange.y), nullptr);

    firePosition = _owner->getPosition() + rangeSprite->getPosition();
    Vec2 targetPos = firePosition + dir * 300.0f;

    // 가장 가까운 오브젝트 처리
    if (closestBody != nullptr)
    {
        targetPos = closestBody->getNode()->getPosition();

        dir = (targetPos - firePosition).getNormalized();

        float angle = -Utils::GetDirAngle(Vec2(-1, 0), dir);
        rangeSprite->setRotation(angle);

        rangeSprite->setPosition(dir * spawnDistance);
    }


    Bullet* bullet = Bullet::create(_owner, _skillBase, 1.0f, "Projectile/GunBullet.png");
    bullet->setPosition(firePosition);
    float angle = -Utils::GetDirAngle(Vec2(-1, 0), dir);
    bullet->setRotation(angle);
    Managers::Scene()->GetCurrentScene()->AddObjectLayer(bullet);
    bullet->Fire(dir);

    Managers::Sound()->PlaySound2D("Sound/Skill/GunHit.mp3");
}

void Gun::Ultimate()
{
    if (ultimateAction != nullptr)
        return;

    auto action = Sequence::create(CallFunc::create([this]() {
        Vec2 firePos = _owner->getPosition() + rangeSprite->getPosition();
        Vec2 pos = firePos + dir * 300.0f;

        BulletParty* bulletParty = BulletParty::create(_owner, _skillBase);
        bulletParty->setPosition(pos);
        Managers::Scene()->GetCurrentScene()->AddObjectLayer(bulletParty);
        bulletParty->Attack();
        }), 
    DelayTime::create(10.0f)
    , nullptr);

    ultimateAction = RepeatForever::create(action);

    this->runAction(ultimateAction);
}

