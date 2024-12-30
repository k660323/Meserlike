#pragma once
#include "SceneEx.h"

class SpawningPool;
class KeyBoardInput;

class GameScene : public SceneEx
{
	using Super = SceneEx;
public:
	static GameScene* createScene();
	virtual bool init();

	// 현재 Scene으로 진입할 때 자동으로 호출되는 함수
	virtual void onEnter() override;

	virtual void update(float dt) override;

	// 현재 Scene을 빠져나갈 때 자동으로 호출되는 함수
	virtual void onExit() override;

	virtual void GameStart();
	virtual void GameEnd();

	void SpawnHpPortion();

	CREATE_FUNC(GameScene);

protected:
	void createMyPhysicsWorld();

private:
	cocos2d::PhysicsWorld* m_world;
	std::shared_ptr<SpawningPool> spawningPool;

	KeyBoardInput* keyInput;
};