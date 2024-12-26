#pragma once
#include "UI_Base.h"

class SneakyJoystickSkinnedBase;
class SneakyJoystick;


class UI_JoyStick : public UI_Base
{
	using Super = UI_Base;
public:
	UI_JoyStick();
	virtual ~UI_JoyStick();

	virtual bool init() override;

	CREATE_FUNC(UI_JoyStick);

private:
	SneakyJoystickSkinnedBase* pJoystickBase;
	SneakyJoystick* pJoystick;
};