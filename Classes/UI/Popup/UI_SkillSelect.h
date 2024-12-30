#pragma once
#include "UI_Popup.h"

class UI_SkillSelect : public UI_Popup
{
	using Super = UI_Popup;
public:
	UI_SkillSelect();
	virtual ~UI_SkillSelect();

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;

	void CreateSkillSlotBnt();

	CREATE_FUNC(UI_SkillSelect);

private:
	// µÞ ¹è°æ
	cocos2d::ui::ImageView* background;

	// ¹è°æ
	cocos2d::Sprite* mainBackground;

	// ´Ý±â
	cocos2d::ui::Button* closeButton;
};