#pragma once
#include "UI_Base.h"

class SneakyButtonSkinnedBase;
class SneakyButton;

class UI_Button : public UI_Base
{
	using Super = UI_Base;

public:
	UI_Button();
	virtual ~UI_Button();

	virtual bool init() override;

	CREATE_FUNC(UI_Button);

protected:
	SneakyButtonSkinnedBase* pBtnBase;
	SneakyButton* pBtn;
};