#pragma once
#include "UI_Button.h"

class UI_DashButton : public UI_Button
{
	using Super = UI_Button;

public:
	UI_DashButton();
	virtual ~UI_DashButton();

	virtual bool init() override;

	virtual void onEnter() override;
	virtual void onExit() override;

	void update(float dt) override;

	CREATE_FUNC(UI_DashButton);

protected:
	cocos2d::ProgressTimer* pTimer;
};