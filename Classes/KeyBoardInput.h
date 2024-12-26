#pragma once
#include "cocos2d.h"

class KeyBoardInput : public cocos2d::Node
{
	using Super = cocos2d::Node;

public:
	KeyBoardInput();
	virtual ~KeyBoardInput();

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode,
		cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode,
		cocos2d::Event* event);

	void update(float dt) override;

	CREATE_FUNC(KeyBoardInput);

protected:
	bool input;
	cocos2d::EventListenerKeyboard* _listener;
	int _inputKeyCode;
};