#include "GameScene.h"
#include "Manager/Contents/MapManager.h"
#include "Manager/Contents/GameManager.h"
#include "Manager/Core/UIManager.h"
#include "Manager/Core/SoundManager.h"
#include "UI/Popup/UI_Popup.h"
#include "Contents/Creature/Creature.h"
#include "Contents/Creature/Player.h"
#include "Contents/Creature/Monster.h"
#include "Contents/SpawningPool/SpawningPool.h"
#include "Contents/KeyBoardInput.h"
#include "Contents/WorldItem/HpPortionItem.h"
USING_NS_CC;

GameScene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if (!Super::init())
        return false;

    // 물리 시뮬레이션 기반의 초기화를 진행한다.
    if (Super::initWithPhysics())
        createMyPhysicsWorld();
    else
        return false;

    spawningPool = std::make_shared<SpawningPool>();

    return true;
}

void GameScene::onEnter()
{
    Super::onEnter();
    Managers::Scene()->SetCurrentSceneType(SceneType::Game);

    Managers::Map()->LoadMap("TileMaps/Field.tmx", object_Layer);

    Vec2 scenePos = Managers::Map()->GetObjectPos("PlayerSpawnPoint");
    if (Managers::Map()->IsValidMap())
        scenePos = Managers::Map()->GetViewpointCenter(scenePos);
    object_Layer->setPosition(scenePos);

    auto delayStart = Sequence::create(DelayTime::create(1.0f),
        CallFunc::create([this]() { GameStart(); }),
        nullptr);
    
    this->runAction(delayStart);
}

void GameScene::update(float dt)
{
    Super::update(dt);

}

void GameScene::onExit()
{
    Super::onExit();

}

void GameScene::GameStart()
{
    // 플레이어 생성
    auto player = Managers::Game()->SpawnPlayer(1);
    // 위치 수정 예정
    Vec2 spawnPos = Managers::Map()->GetObjectPos("PlayerSpawnPoint");
    player->setPosition(spawnPos);
    AddObjectLayer(player);

    SpawnHpPortion();

    // UI생성
    auto sceneUI = Managers::UI()->ShowSceneUI(SceneType::Game);
    AddUILayer(sceneUI);

    Managers::Sound()->PlaySound2D("Sound/BGM/RestNPeace.mp3", SoundType::BGM);

    // keyInput 생성
    keyInput = KeyBoardInput::create();
    AddObjectLayer(keyInput);

    Managers::Game()->SetRound(0);
    spawningPool->TrySpawn(Managers::Game()->GetRound());
}

void GameScene::GameEnd()
{
    auto action = Sequence::create(
        DelayTime::create(3.0f), // 3 초 대기
        CallFunc::create([this]() 
            { 
                Managers::UI()->ShowPopupUI(PopupType::UI_ResultWindow);
            }), // 결과창 띄움
        nullptr
    );

    this->runAction(action);
}

void GameScene::SpawnHpPortion()
{
    auto portionItem = HpPortionItem::create();
    Vec2 spawnPos = Managers::Map()->GetObjectPos("PlayerSpawnPoint");
    portionItem->setPosition(spawnPos);
    Managers::Scene()->GetCurrentScene()->AddObjectLayer(portionItem);
}

void GameScene::createMyPhysicsWorld()
{
    // 스크린 바운더리(Screen Boundary)를 설정한다.

     // 물리 전용 벡터
    // 중력을 설정 않을 경우 기본값은 Vec(0.0f, -98.0f)
    // Vect gravity = Vect(0.0f, -128.0f);
    Vect gravity = Vect(0.0f, 0.0f);

    // 현재 Scene의 PhysicsWorld 정보를 받아온다.
    m_world = this->getPhysicsWorld();

    // setDebugDrawMash() : 스프라이트의 판정 박스를 가시화한다.
    // m_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    //setGravity() : 중력의 방향과 세기를 결정
    m_world->setGravity(gravity);

    // setSpeed() : 낙하에 따른 중력 가속도를 설정 (기본값 : 1.0)
    m_world->setSpeed(1.0f);

    // setSubsteps() : 프레임 간에 실시하는 물리 연산의 횟수를 조정한다.
    m_world->setSubsteps(1);
    
    // m_world->setFixedUpdateRate(0.5f);

}