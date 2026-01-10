#include "Player.h"
#include "Utils.h"
#include "Contents/Ex/AnimateEx.h"
#include "Contents/Stat/PlayerStat.h"
#include "Contents/Controllers/PlayerController.h"
#include "Bitmask.h"
#include "Contents/Skills/SkillBook.h"
#include "Contents/Skills/Repeat/Melee/SpinningAX.h"
#include "Manager/Managers.h"
#include "Manager/Core/DataManager.h"
#include "Manager/Core/SceneManager.h"
#include "Scene/SceneEx.h"
#include "Scene/GameScene.h"
#include "Tags.h"
#include "Manager/Core/InputManager.h"
#include "Manager/Core/SoundManager.h"
#include "Data/Data.h"
USING_NS_CC;

Player::Player(int level) : Super()
{
    _creatureType = CreatureType::Player;
    // stat 클래스 생성 및 초기화
    stat = std::make_shared<PlayerStat>(this, level);
    controller = std::make_shared<PlayerController>(this);


    auto data = Managers::Data()->GetPlayerInfoData();
    
    // 스프라이트
    cSprite = Utils::SetDefaultSprite(data.spriteId);
    cSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->addChild(cSprite);

    auto arr = Utils::CreateAllAnimation(data.spriteId);

    for (auto it : arr)
    {
        if (it.first != "Idle")
            animateEx->RegisterAnimation(it.first, it.second.second, it.second.first.isLoop);
        else
            animateEx->Init(cSprite, it.first, it.second.second, true, false);
    }

    setTag(Tags::Player);

    dashDuration = 0.3f;
    dashCooltime = 5.0f;
    curDashCooltime = 0.0f;
    isDash = false;
}

Player::~Player()
{
    
}

bool Player::init()
{
    if (!Super::init())
        return false;

    {
        //  auto material1 = PhysicsMaterial(0.0f, 0.0f, 0.0f);
        auto material = PhysicsMaterial(0.0f, 0.0f, 0.0f);
        auto body = PhysicsBody::createBox(cSprite->getContentSize(), material);

        // 강체의 질량 설정
        body->setMass(50);
        // 동적 또는 정적 상태를 설정한다
        body->setDynamic(true);
        body->setRotationEnable(false);
        // setCategoryBitmask(int) : 충돌을 위한 카테고리를 설정한다. 
        // 지정한 값을 기준으로 구분. 
        body->setCategoryBitmask(Bitmask::Player);

        // 물리 처리할 비트마스크
        body->setCollisionBitmask(Bitmask::Ground);

        body->setContactTestBitmask(Bitmask::All_InvEx);

        body->setEnabled(true);
        // 스프라이트에 강체 설정
        this->setPhysicsBody(body);
    }

    {
        // skillBook->AddSkillById(SkillId::SpinningAX, getPosition(), this, 3);
        // skillBook->AddSkillById(SkillId::Gun, getPosition(), this, 3);
        // skillBook->AddSkillById(SkillId::Bow, getPosition(), this, 1);
        // skillBook->AddSkillById(SkillId::Fan, getPosition(), this, 3);
        // skillBook->AddSkillById(SkillId::ProjectileSheid, getPosition(), this, 1);
        // skillBook->AddSkillById(SkillId::SpeedUp, getPosition(), this, 1);
    }

    return true;
}

void Player::onEnter()
{
    Super::onEnter();

    // 업데이트 함수 갱신
    this->scheduleUpdate();
}

void Player::onExit()
{
    Super::onExit();

}

PlayerStat* Player::GetPlayerStat()
{
    return dynamic_cast<PlayerStat*>(stat.get());
}

PlayerController* Player::GetPlayerController()
{
    return dynamic_cast<PlayerController*>(controller.get());
}

void Player::OnAttacked(float damage)
{
    auto pc = controller.get();
    if (pc->GetStat() == State::Dead || getPhysicsBody()->getCategoryBitmask() == Bitmask::Invincibility)
        return;

    auto stat = GetStat();
    float defense = stat->GetDefense();
    float totalDamage = std::max(0.0f, damage - defense);
    if (totalDamage == 0.0f)
        totalDamage = 0.5f;


    stat->SetCurHp(stat->GetCurHp() - totalDamage);

    // 무적
    if (stat->GetCurHp() > 0)
    {
        getPhysicsBody()->setCategoryBitmask(Bitmask::Invincibility);
        invincibilityAction = Sequence::create(
            DelayTime::create(3.0f),
            CallFunc::create([this]() { getPhysicsBody()->setEnabled(false); getPhysicsBody()->setCategoryBitmask(Bitmask::Player); getPhysicsBody()->setEnabled(true); }),
            nullptr
        );

        this->runAction(invincibilityAction);
    }
    // 사망
    else
    {
        // 상태 변환
        pc->SetState(State::Dead);

        CreatureInfoData data = Managers::Data()->GetPlayerInfoData();
        CreatureSoundInfo soundData = Managers::Data()->GetCreatureSoundInfoData(data.soundId);
        Managers::Sound()->PlaySound2D(soundData.Die);
        GameScene* gs = dynamic_cast<GameScene*>(Managers::Scene()->GetCurrentScene());
        if (gs)
            gs->GameEnd();
    }
}

void Player::OnAttacked(cocos2d::Node* other, float damage)
{

}

void Player::update(float deltaTime)
{
    Super::update(deltaTime);

    if (curDashCooltime > 0.0f)
        curDashCooltime -= deltaTime;
}

void Player::Dash()
{
    if (!isDash && curDashCooltime <= 0.0f)
    {
        StopHitAction();

        getPhysicsBody()->setCategoryBitmask(Bitmask::Invincibility);
        auto dashSequence = Sequence::create(
            CallFunc::create([this]() {
                Vec2 dir = Managers::Input()->GetMoveInput();
                if (dir == Vec2::ZERO)
                {
                    auto lookDir = GetDir();
                    dir = (lookDir == Dir::Left) ? Vec2(-1, 0) : Vec2(1, 0);
                }

                    getPhysicsBody()->applyImpulse(dir * 45000);
                }),
            DelayTime::create(dashDuration),
            CallFunc::create([this]() {
                    getPhysicsBody()->setVelocity(Vec2(0, 0));
                isDash = false;
                }),
            DelayTime::create(0.5f),
            CallFunc::create([this]() 
                { getPhysicsBody()->setEnabled(false); getPhysicsBody()->setCategoryBitmask(Bitmask::Player); getPhysicsBody()->setEnabled(true); }),
            nullptr
        );

        this->runAction(dashSequence);

        curDashCooltime = dashCooltime;
        isDash = true;
        dashStartDelegate.invoke(dashCooltime);
        Managers::Sound()->PlaySound2D("Sound/Skill/DashSound.mp3");
    }
}

void Player::SetCurDashCoolTime(float val)
{
    curDashCooltime = val;

    curDashDelegate.invoke(val, dashCooltime);
}

float Player::GetCurDashCoolTime()
{
    return curDashCooltime;
}

void Player::SetDashCoolTime(float val)
{
    dashCooltime = val;

    dashDelegate.invoke(curDashCooltime, val);
}

float Player::GetDashCoolTime()
{
    return dashCooltime;
}

void Player::CreateLevelUpEffect()
{
    auto data = Managers::Data()->GetSpriteData("LevelUp");

    Sprite* levelSprite = Sprite::create(data.dspriteData.path);
    levelSprite->setPosition(Vec2(0, 200));
    this->addChild(levelSprite);

    auto animData = data.animData["Idle"];
    auto animation = Utils::SimpleCreateAnimation(animData);
    Animate* animate = Animate::create(animation);
    auto animAction = Repeat::create(animate, 1);

    levelSprite->runAction(animAction);

    auto removeAction = Sequence::create(
        DelayTime::create(2.0f),
        CallFunc::create([this, levelSprite]() {
            levelSprite->removeFromParent();
        }), nullptr);

    this->runAction(removeAction);
}
