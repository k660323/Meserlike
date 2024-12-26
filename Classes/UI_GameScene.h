#pragma once
#include "UI_Scene.h"

class BossMonster;

class UI_GameScene : public UI_Scene
{
	using Super = UI_Scene;
public:
	UI_GameScene();
	virtual ~UI_GameScene();

	virtual bool init() override;

	CREATE_FUNC(UI_GameScene);

private:
	cocos2d::Label* levelText;

	cocos2d::ui::LoadingBar* expBar;

	cocos2d::Label* expText;

	cocos2d::Label* roundText;

	cocos2d::ui::LoadingBar* hpBar;
	cocos2d::Label* hpText;
};