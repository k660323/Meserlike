#include "BossMonster.h"
#include "Managers.h"
#include "GameManager.h"
#include "Utils.h"
#include "AnimateEx.h"
#include "SkillBook.h"
#include "Bitmask.h"
#include "Tags.h"
#include "Player.h"
#include "MonsterStat.h"
#include "PlayerStat.h"
#include "BossMonsterController.h"
#include "SoundManager.h"
#include "UI_BossInfo.h"
USING_NS_CC;

BossMonster::BossMonster(MonsterType monsterType) : Super(monsterType)
{
    // controller
    controller = std::make_shared<BossMonsterController>(this);

    auto data = Managers::Data()->GetMonsterInfoData(monsterType);

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

    auto skillVector = data.skillIds;

    for (auto v : skillVector)
    {
        skillBook->AddSkillById(static_cast<SkillId>(v), getPosition(), this);
    }

    skillBook->StartNextSequenceSkill();
}

BossMonster::~BossMonster()
{
}

bool BossMonster::init()
{
    if (!Super::init())
        return false;

    {
        auto material = PhysicsMaterial(0.0f, 0.0f, 0.0f);
        auto body = PhysicsBody::createBox(cSprite->getContentSize(), material);

        // 강체의 질량 설정
        body->setMass(0.0f);
        // 동적 또는 정적 상태를 설정한다
        body->setDynamic(false);

        // setCategoryBitmask(int) : 충돌을 위한 카테고리를 설정한다. 
        body->setCategoryBitmask(Bitmask::Monster);

        // 물리 처리할 비트마스크
        body->setCollisionBitmask(Bitmask::Ignore);

        // setContactTestBitmask(int) : 어떤 카테고리와 충돌 트리거 처리
        body->setContactTestBitmask(Bitmask::All_InvEx ^ Bitmask::Monster);

        body->setEnabled(true);
        // 스프라이트에 강체 설정
        this->setPhysicsBody(body);
    }

    // 충돌 이벤트 리스너
    contact = EventListenerPhysicsContact::create();

    // 충돌 이벤트 함수
    contact->onContactBegin = CC_CALLBACK_1(BossMonster::onContactEnter, this);
    contact->onContactSeparate = CC_CALLBACK_1(BossMonster::onContactExit, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(contact, this);


    return true;
}

void BossMonster::onEnter()
{
    Super::onEnter();

}

void BossMonster::onExit()
{

    Super::onExit();
}

bool BossMonster::onContactEnter(cocos2d::PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA != this && nodeB != this)
        return false;

    auto other = (nodeA == this) ? nodeB : nodeA;

    if (other == nullptr)
        return false;

    if (other->getTag() != Tags::Player)
        return false;

    auto hitable = dynamic_cast<IHitable*>(other);
    if (hitable)
    {
        float atk = GetStat()->GetTotalExtraAtk();
        hitable->OnAttacked(atk);
    }
    else
    {
        return false;
    }

    return true;
}

void BossMonster::onContactExit(cocos2d::PhysicsContact& contact)
{
}

void BossMonster::OnAttacked(float damage)
{
    auto bc = controller.get();
    if (bc->GetStat() == State::Dead || getPhysicsBody()->getCategoryBitmask() == Bitmask::Invincibility)
        return;

    auto stat = GetMonsterStat();
    float defense = stat->GetTotalDefense();
    float totalDamage = std::max(0.0f, damage - defense);
    if (totalDamage == 0.0f)
        totalDamage = 0.5f;

    stat->SetCurHp(stat->GetCurHp() - totalDamage);

    MonsterInfoData data = Managers::Data()->GetMonsterInfoData(GetMonsterType());
    CreatureSoundInfo soundData = Managers::Data()->GetCreatureSoundInfoData(data.soundId);

    // 사망
    if (stat->GetCurHp() <= 0)
    {
        // 상태 변환
        bc->SetState(State::Dead);

        // 콜백 함수
        deadAction.invoke();

        // 스코어 갱신
        Managers::Game()->SetScore(Managers::Game()->GetScore() + stat->GetScore());

        // 경험치 드랍
        auto playerStat = Managers::Game()->GetPlayer()->GetPlayerStat();
        playerStat->SetExp(playerStat->GetExp() + stat->GetDropExp());

        auto action = Sequence::create(
            CallFunc::create([this]() { getPhysicsBody()->setEnabled(false); }),
            DelayTime::create(2.0f),
            CallFunc::create([this]() { Managers::Game()->DeSpawnCreature(this); }),
            nullptr
        );

        this->runAction(action);

        Managers::Sound()->PlaySound2D(soundData.Die);
    }
    else
    {
        Managers::Sound()->PlaySound2D(soundData.Damaged);
    }
}

void BossMonster::OnAttacked(cocos2d::Node* other, float damage)
{
}

BossMonsterController* BossMonster::GetBossMonsterController()
{
    return dynamic_cast<BossMonsterController*>(controller.get());
}
