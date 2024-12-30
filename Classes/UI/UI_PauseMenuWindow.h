#pragma once
#include "UI_Popup.h"

class UI_PauseMenuWindow : public UI_Popup
{
	using Super = UI_Popup;
public:
	UI_PauseMenuWindow();
	virtual ~UI_PauseMenuWindow();

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;

	CREATE_FUNC(UI_PauseMenuWindow);

private:
	// 뒷 배경
	cocos2d::ui::ImageView* background;
	
	// 배경
	cocos2d::Sprite* mainBackground;
	
	// 닫기
	cocos2d::ui::Button* closeButton;
	// 환경 설정 버튼
	cocos2d::ui::Button* settingButton;
	// 메인 화면 버튼
	cocos2d::ui::Button* mainButton;
	// 게임 종료 버튼
	cocos2d::ui::Button* exitButton;
};