#include "BulletParty.h"
#include "cocos2d.h"
#include "Manager/Managers.h"
#include "Manager/Core/SceneManager.h"
#include "Scene/SceneEx.h"
#include "Contents/Creature/Creature.h"
#include "Interface/IHitable.h"
#include "Contents/Stat/Stat.h"
#include "Contents/Skills/SkillBase.h"
#include "Utils.h"
#include "Manager/Core/SoundManager.h"
USING_NS_CC;

BulletParty::BulletParty(Creature* parent, SkillBase* skillBase) : Super(parent, skillBase)
{
    damage = (_owner->GetStat()->GetTotalSpecialAtk() + _skillBase->GetSkillStatData().specialAtk) * 0.5f;
}

BulletParty::~BulletParty()
{

}

bool BulletParty::init()
{
    if (!Super::init())
        return false;

    Managers::Sound()->PlaySound2D("Sound/Skill/BulletPartyPre.mp3");

    auto sprite = Sprite::create("UI/Box.png");
    sprite->setScale(0.5f);
    this->addChild(sprite);

    auto animation = Utils::SimpleCreateAnimation("Skill/BulletParty.png", 1000, 1310, 0, 1, 0, 12, 0.1f);
    Animate* animate = Animate::create(animation);
    auto animAction = RepeatForever::create(animate);
    
    sprite->runAction(animAction);

    return true;
}

bool BulletParty::Attack()
{
    // 공격 주기
    auto action = Sequence::create(
        CallFunc::create([this]() {
            // 사각형 영역에서 queryRect 수행
            Vec2 detectRange(500, 300);
            // _owner의 위치를 월드 좌표로 변환
            Vec2 ownerWorldPos = this->getParent()->convertToWorldSpace(getPosition());

            Managers::Scene()->GetCurrentScene()->getPhysicsWorld()->queryRect(CC_CALLBACK_3(BulletParty::DetectedNearObject, this), cocos2d::Rect(ownerWorldPos.x - (detectRange.x / 2), ownerWorldPos.y - (detectRange.y / 2), detectRange.x, detectRange.y), nullptr);
            }),
        DelayTime::create(0.35f)
        , nullptr);

    auto repeatAction = RepeatForever::create(action);
    this->runAction(repeatAction);

    auto lifeTimeAction = Sequence::create(DelayTime::create(5.0f),
        CallFunc::create([this]() { 
            Managers::Sound()->StopVolume(soundId);
            Managers::Sound()->PlaySound2D("Sound/Skill/BulletPartyEnd.mp3");

            this->removeFromParent(); 
            }),
        nullptr);
    this->runAction(lifeTimeAction);

    //// 디버그
    //{
    //    Vec2 ownerWorldPos = this->getParent()->convertToWorldSpace(getPosition());
    //    Vec2 detectRange(500, 300);
    //    // queryRect의 범위를 설정 (월드 좌표계에서)
    //    cocos2d::Rect queryArea(ownerWorldPos.x - (detectRange.x / 2), ownerWorldPos.y - (detectRange.y / 2), detectRange.x, detectRange.y);
    //    // 디버그용 사각형 그리기
    //    DrawNode* debugRect = DrawNode::create();
    //    Vec2 origin(queryArea.getMinX(), queryArea.getMinY());
    //    Vec2 destination(queryArea.getMaxX(), queryArea.getMaxY());

    //    // 사각형 그리기 (파란색)
    //    debugRect->drawRect(origin, destination, Color4F::BLUE);

    //    Managers::Scene()->GetCurrentScene()->addChild(debugRect); // 부모에 추가하여 화면에 표시
    //}

    soundId = Managers::Sound()->PlaySound2D("Sound/Skill/BulletPartyLoop.mp3", SoundType::Sound, true);

    return true;
}

bool BulletParty::DetectedNearObject(cocos2d::PhysicsWorld& world, cocos2d::PhysicsShape& shape, void* userData)
{
    // 오브젝트의 바디를 가져옴
    PhysicsBody* body = shape.getBody();
    Vec2 objectPosition = body->getPosition();

    if (body->getNode() == _owner)
        return true;

    Creature* target = dynamic_cast<Creature*>(body->getNode());
    if (target == nullptr)
        return true;

    // 피격
    IHitable* hitable = dynamic_cast<IHitable*>(target);
    if (hitable)
    {
        hitable->OnAttacked(damage);
    }

    // true를 반환하면 계속 검색, false를 반환하면 중단
    return true;
}
