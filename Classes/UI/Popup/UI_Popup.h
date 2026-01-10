#pragma once
#include "UI/UI_Base.h"

class UI_Popup : public UI_Base
{
	using Super = UI_Base;
public:
	UI_Popup();
	virtual ~UI_Popup();

	virtual bool init() override;

	virtual void ClosePopupUI();

	virtual void ClosePopupAllUI();

	CREATE_FUNC(UI_Popup);
};