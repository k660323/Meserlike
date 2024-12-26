#pragma once
#include "UI_Popup.h"

class UI_Setting : public UI_Popup
{
	using Super = UI_Popup;
public:
	UI_Setting();
	virtual ~UI_Setting();
	
	virtual bool init() override;

	CREATE_FUNC(UI_Setting);

public:
	cocos2d::Sprite* background;

};