#include "KeyBoardInput.h"
#include "Managers.h"
#include "InputManager.h"
#include "GameManager.h"
#include "Player.h"
USING_NS_CC;

KeyBoardInput::KeyBoardInput()
{
}

KeyBoardInput::~KeyBoardInput()
{
}

bool KeyBoardInput::init()
{
    if (!Super::init())
        return false;

    // 업데이트 함수 갱신
    this->scheduleUpdate();

    return true;
}

void KeyBoardInput::onEnter()
{
    Super::onEnter();
    input = false;
    _inputKeyCode = 0;
    _listener = EventListenerKeyboard::create();
    _listener->onKeyPressed = CC_CALLBACK_2
    (KeyBoardInput::onKeyPressed, this);
    _listener->onKeyReleased = CC_CALLBACK_2
    (KeyBoardInput::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}

void KeyBoardInput::onExit()
{
    _eventDispatcher->removeEventListener(_listener);


    Super::onExit();
}

void KeyBoardInput::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        _inputKeyCode |= 1;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        _inputKeyCode |= 2;
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _inputKeyCode |= 4;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        _inputKeyCode |= 8;
        break;
    case EventKeyboard::KeyCode::KEY_W:
        _inputKeyCode |= 1;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        _inputKeyCode |= 2;
        break;
    case EventKeyboard::KeyCode::KEY_A:
        _inputKeyCode |= 4;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        _inputKeyCode |= 8;
        break;
    case EventKeyboard::KeyCode::KEY_SPACE:
        auto p = Managers::Game()->GetPlayer();
        if (p)
            p->Dash();
        break;
    }

    if (_inputKeyCode != 0)
        input = true;
}

void KeyBoardInput::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    int tmp = _inputKeyCode;

    // 키 입력을 해제하기 위해서는 XOR 연산자를 사용하면 된다.
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        _inputKeyCode ^= 1;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        _inputKeyCode ^= 2;
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _inputKeyCode ^= 4;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        _inputKeyCode ^= 8;
        break;
    case EventKeyboard::KeyCode::KEY_W:
        _inputKeyCode ^= 1;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        _inputKeyCode ^= 2;
        break;
    case EventKeyboard::KeyCode::KEY_A:
        _inputKeyCode ^= 4;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        _inputKeyCode ^= 8;
        break;
    }

    if (_inputKeyCode == 0)
    {
        input = false;
        if (tmp != 0)
        {
            Managers::Input()->SetMoveInput(Vec2::ZERO);
        }
    }
}

void KeyBoardInput::update(float dt)
{
    Super::update(dt);
    if (input)
    {
        Vec2 dir = Vec2(0, 0);

        if (_inputKeyCode & 1)
            dir += Vec2(0, 1);
        if (_inputKeyCode & 2)
            dir += Vec2(0, -1);
        if (_inputKeyCode & 4)
            dir += Vec2(-1, 0);
        if (_inputKeyCode & 8)
            dir += Vec2(1, 0);

        dir = dir.getNormalized();

        Managers::Input()->SetMoveInput(dir);
    }
}
