#include "InputManager.h"
#include "cocos2d.h"

InputManager::InputManager()
{
    moveInput = cocos2d::Point::ZERO;
}

InputManager::~InputManager()
{
}

void InputManager::SetMoveInput(cocos2d::Point input)
{
    moveInput = input;
}

cocos2d::Point InputManager::GetMoveInput()
{
    return moveInput;
}

void InputManager::Clear()
{
    moveInput = cocos2d::Point::ZERO;
}
