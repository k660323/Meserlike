#pragma once
#include"Define.h"

namespace cocos2d
{
	class TransitionScene;
}

class SceneEx;

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	void PushScene(SceneType type, int transitionIndex);
	void PopScene();

	void SetCurrentScene(SceneEx* scene);
	SceneEx* GetCurrentScene();

	void SetCurrentSceneType(SceneType type);
	SceneType GetCurrentSceneType();

	cocos2d::TransitionScene* createTransition(int index, float t, SceneEx* s);

	void Clear();

private:
	SceneType sceneType;
	SceneEx* currentScene;
};