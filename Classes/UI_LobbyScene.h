#pragma once
#include "UI_Scene.h"

class UI_LobbyScene : public UI_Scene
{
	using Super = UI_Scene;

	enum Sprites
	{
		background0
	};

	enum Buttons
	{
		startBtn0,
		settingBtn1,
		exitBtn2
	};

	enum TTFConfigs
	{
		ttfConfigs
	};

	enum Labels
	{
		titleLabel0,
		startLabel1
	};

	enum Layers
	{
		backgroundLayer0
	};

public:
	UI_LobbyScene();
	virtual ~UI_LobbyScene();

	virtual bool init() override;

	virtual void onEnter() override;

	CREATE_FUNC(UI_LobbyScene);

private:
	// ÆùÆ®
	cocos2d::TTFConfig ttfConfig;

	cocos2d::ui::Button* startBtn;
	cocos2d::ui::Button* settingBtn;
	cocos2d::ui::Button* exitBtn;
};