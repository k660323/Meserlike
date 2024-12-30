#include "Fan.h"
#include "Utils.h"
#include "Bullet.h"
#include "Managers.h"
#include "SoundManager.h"
USING_NS_CC;

Fan::Fan(Creature* parent, SkillBase* skillBase): Super(parent, skillBase)
{
    spawnDistance = 75;
    detectRange = Vec2(1000, 700);
    dir = Vec2(1, 0);
}

Fan::~Fan()
{
}

bool Fan::init()
{
    if (!Super::init())
        return false;

    rangeSprite = Sprite::create("Weapon/Fan.png");
    rangeSprite->setPosition(spawnDistance * Vec2(1, 0));
    this->addChild(rangeSprite);

    return true;
}

void Fan::Fire()
{
    if (_owner == nullptr)
        return;

    closestBody = nullptr; // 가장 가까운 오브젝트
    closestDistance = std::numeric_limits<float>::max(); // 최소 거리

    // _owner의 위치를 월드 좌표로 변환
    Vec2 ownerWorldPos = _owner->getParent()->convertToWorldSpace(_owner->getPosition());

    // 사각형 영역에서 queryRect 수행
    Managers::Scene()->GetCurrentScene()->getPhysicsWorld()->queryRect(CC_CALLBACK_3(Super::DetectedNearObject, this), cocos2d::Rect(ownerWorldPos.x - (detectRange.x / 2), ownerWorldPos.y - (detectRange.y / 2), detectRange.x, detectRange.y), nullptr);

    int _level = _skillBase->GetLevel();

    firePosition = _owner->getPosition() + rangeSprite->getPosition();
    Vec2 targetPos = firePosition + dir * 300.0f;

    if (closestBody != nullptr)
    {
        // 가장 가까운 오브젝트 처리
        targetPos = closestBody->getNode()->getPosition();    

        dir = (targetPos - firePosition).getNormalized();

        float angle = -Utils::GetDirAngle(Vec2(1, 0), dir);
        rangeSprite->setRotation(angle);

        rangeSprite->setPosition(dir * spawnDistance);
    }

    // 총알 생성
    int maxCount = 6;
    int startAngle = -90;
    int addAngle = 30;
    switch (_level)
    {
    case 1:
        maxCount = 6;
        addAngle = 30;
        break;
    case 2:
        maxCount = 9;
        addAngle = 20;
        break;
    default:
        maxCount = 12;
        addAngle = 15;
        break;
    }


    Vec2 firDir = Utils::RotateVec2(dir, startAngle);

    for (int i = 0; i < maxCount; i++)
    {
        auto bullet = Bullet::create(_owner, _skillBase, 0.5f, "Projectile/FanBullet.png");
        bullet->setPosition(firePosition);
        Managers::Scene()->GetCurrentScene()->AddObjectLayer(bullet);
        bullet->Fire(firDir);

        firDir = Utils::RotateVec2(firDir, addAngle);
    }

    Managers::Sound()->PlaySound2D("Sound/Skill/FanUse.mp3");
}
