#include "NormalMonster.h"
#include "Contents/Controllers/NormalMonsterController.h"
#include "Utils.h"
#include "Contents/Ex/AnimateEx.h"
#include "Contents/Stat/MonsterStat.h"
#include "Bitmask.h"
#include "Manager/Managers.h"
#include "Manager/Contents/GameManager.h"
#include "Tags.h"
#include "Player.h"
#include "Contents/Stat/PlayerStat.h"
#include "Contents/Skills/SkillBook.h"
#include "Manager/Core/SoundManager.h"
USING_NS_CC;

NormalMonster::NormalMonster(MonsterType monsterType) : Super(monsterType)
{

    controller = std::make_shared<NormalMonsterController>(this);

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
}

NormalMonster::~NormalMonster()
{
    
}

bool NormalMonster::init()
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
    contact->onContactBegin = CC_CALLBACK_1(NormalMonster::onContactEnter, this);
    contact->onContactSeparate = CC_CALLBACK_1(NormalMonster::onContactExit, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contact, this);

   
    return true;
}

void NormalMonster::onEnter()
{
    Super::onEnter();

}

void NormalMonster::onExit()
{

    Super::onExit();
}

bool NormalMonster::onContactEnter(PhysicsContact& contact)
{
    // Sprite 클래스가 아닌 Node 클래스를 가져오기
   /*
               contact : 충돌 정보를 관리하는 PhysicsContact 인스턴스
               getShapeA&getShapeB : 충돌한 PhysicsShape(물리적인 형상 오브젝트) 가져오기
               getBody : PhysiccsShape 에서 PhysicsBody 가져오기
               getNode : PhyscisBody에서 이 강체가 접목된 Node를 가져오기
   */
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

void NormalMonster::onContactExit(PhysicsContact& contact)
{
    
}

void NormalMonster::OnAttacked(float damage)
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

      getPhysicsBody()->setEnabled(false);

        auto action = Sequence::create(
            DelayTime::create(3.0f),
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

void NormalMonster::OnAttacked(cocos2d::Node* other, float damage)
{
}

NormalMonsterController* NormalMonster::GetNormalMonsterController()
{
    return dynamic_cast<NormalMonsterController*>(controller.get());
}
