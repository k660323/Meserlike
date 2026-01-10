#include "Bow.h"
#include "Utils.h"
#include "Contents/Weapon/Projectile/Bullet.h"
#include "Manager/Managers.h"
#include "Manager/Core/SoundManager.h"
USING_NS_CC;

Bow::Bow(Creature* parent, SkillBase* skillBase) : Super(parent, skillBase)
{
    spawnDistance = 75;
    detectRange = Vec2(1000, 700);
}

Bow::~Bow()
{
}

bool Bow::init()
{
    if (!Super::init())
        return false;

    rangeSprite = Sprite::create("Weapon/Bow.png");
    rangeSprite->setPosition(spawnDistance * Vec2(1, 0));
    rangeSprite->setRotation(-90.0f);
    this->addChild(rangeSprite);

    return true;
}

void Bow::Fire()
{
    if (_owner == nullptr)
        return;

    closestBody = nullptr; // 가장 가까운 오브젝트
    closestDistance = std::numeric_limits<float>::max(); // 최소 거리

    // _owner의 위치를 월드 좌표로 변환
    Vec2 ownerWorldPos = _owner->getParent()->convertToWorldSpace(_owner->getPosition());

    // 사각형 영역에서 queryRect 수행
    Managers::Scene()->GetCurrentScene()->getPhysicsWorld()->queryRect(CC_CALLBACK_3(Super::DetectedNearObject, this), cocos2d::Rect(ownerWorldPos.x - (detectRange.x / 2), ownerWorldPos.y - (detectRange.y / 2), detectRange.x, detectRange.y), nullptr);

    if (closestBody != nullptr)
    {
        firePosition = _owner->getPosition() + rangeSprite->getPosition();
        int _level = _skillBase->GetLevel();
        Vec2 targetPos = firePosition + dir * 300.0f;

        // 가장 가까운 오브젝트 처리

        targetPos = closestBody->getNode()->getPosition();

        firePosition = _owner->getPosition() + rangeSprite->getPosition();

        dir = (targetPos - firePosition).getNormalized();

        float angle = -Utils::GetDirAngle(Vec2(-1, 0), dir);
        rangeSprite->setRotation(angle + 90.0f);

        rangeSprite->setPosition(dir * spawnDistance);

        auto fireAction = Sequence::create(
            CallFunc::create([this]() {
                Bullet* bullet = Bullet::create(_owner, _skillBase, 1.0f, "Projectile/Arrow.png");
                bullet->setPosition(firePosition);
                Managers::Scene()->GetCurrentScene()->AddObjectLayer(bullet);
                float angle = -Utils::GetDirAngle(Vec2(-1, 0), dir);
                rangeSprite->setRotation(angle + 90.0f);
                bullet->setRotation(angle);
                bullet->Fire(dir);
                }),
            DelayTime::create(0.5f),
            nullptr
        );

        auto repeatAction = Repeat::create(fireAction, 2);

        this->runAction(repeatAction);

        Managers::Sound()->PlaySound2D("Sound/Skill/BowHit.mp3");
    }
}
