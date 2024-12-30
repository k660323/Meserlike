#pragma once
#include "UI_Popup.h"

class UI_ResultWindow : public UI_Popup
{
	using Super = UI_Popup;
public:
	UI_ResultWindow();
	virtual ~UI_ResultWindow();

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;

	CREATE_FUNC(UI_ResultWindow);

protected:
	// 뒷 배경
	cocos2d::ui::ImageView* background;

	// 현재 라운드
	cocos2d::Label* roundLabel;

	// 총합 점수
	cocos2d::Label* totalLabel;

	// 생존 텍스트
	cocos2d::Label* aliveLabel;

	// 배경
	cocos2d::Sprite* mainBackground;

	// 메인 화면으로
	cocos2d::ui::Button* mainButton;
};