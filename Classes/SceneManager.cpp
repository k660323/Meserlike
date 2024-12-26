#include "SceneManager.h"
#include "LobbyScene.h"
#include "GameScene.h"
#include "SceneEx.h"
#include "cocos2d.h"

USING_NS_CC;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}



void SceneManager::PushScene(SceneType type, int transitionIndex)
{
    // ÀÌµ¿ÇÒ Scene
    SceneEx* scene;
    switch (type)
    {
    case SceneType::Lobby:
        scene = LobbyScene::createScene();
        break;
    case SceneType::Game:
        scene = GameScene::createScene();
        break;
    default:
        break;
    }

    Director::getInstance()->pushScene(createTransition(transitionIndex, 1.0f, scene));
}

void SceneManager::PopScene()
{
    Director::getInstance()->popScene();
}

void SceneManager::SetCurrentScene(SceneEx* scene)
{
    currentScene = scene;
}

SceneEx* SceneManager::GetCurrentScene()
{
    return currentScene;
}

void SceneManager::SetCurrentSceneType(SceneType type)
{
    sceneType = type;
}

SceneType SceneManager::GetCurrentSceneType()
{
    return sceneType;
}

cocos2d::TransitionScene* SceneManager::createTransition(int index, float t, SceneEx* s)
{
    Director::getInstance()->setDepthTest(false);

    switch (index)
    {
    case 0:
        return TransitionProgressRadialCCW::create(t, s);
    case 1:
        return TransitionProgressRadialCW::create(t, s);
    case 2:
        return TransitionProgressHorizontal::create(t, s);
    case 3:
        return TransitionProgressVertical::create(t, s);
    case 4:
        return TransitionFade::create(t, s);
    case 5:
        return TransitionFadeUp::create(t, s);
    case 6:
        return TransitionProgressOutIn::create(t, s);
    case 7:
        return TransitionProgressInOut::create(t, s);
    case 8:
        return TransitionFadeBL::create(t, s);
    default:
        return nullptr;
    }
}

void SceneManager::Clear()
{
    sceneType = SceneType::None;
}
