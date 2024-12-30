#include "LobbyScene.h"
#include "UI_LobbyScene.h"
#include "Define.h"
#include "UIManager.h"
#include "SoundManager.h"
USING_NS_CC;


LobbyScene* LobbyScene::createScene()
{
    return LobbyScene::create();
}

bool LobbyScene::init()
{
    if (!Super::init())
        return false;

    return true;
}

void LobbyScene::onEnter()
{
    Super::onEnter();
    Managers::Scene()->SetCurrentSceneType(SceneType::Lobby);
    auto scene = Managers::UI()->ShowSceneUI(SceneType::Lobby);
    AddUILayer(scene);

    Managers::Sound()->PlaySound2D("Sound/BGM/Title.mp3", SoundType::BGM);
}

void LobbyScene::onExit()
{

    Super::onExit();
}