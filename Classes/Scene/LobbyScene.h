#pragma once
#include "SceneEx.h"

class LobbyScene : public SceneEx
{
	using Super = SceneEx;
public:
	static LobbyScene* createScene();
	virtual bool init();

	// 현재 Scene으로 진입할 때 자동으로 호출되는 함수
	virtual void onEnter() override;

	// 현재 Scene을 빠져나갈 때 자동으로 호출되는 함수
	virtual void onExit() override;

	CREATE_FUNC(LobbyScene);
};