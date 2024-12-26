#pragma once
#include "cocos2d.h"

class InputManager
{
public:
	InputManager();
	virtual ~InputManager();

	void SetMoveInput(cocos2d::Point input);
	cocos2d::Point GetMoveInput();

	void Clear();
private:
	cocos2d::Point moveInput;
};