#include "UI_JoyStick.h"
#include "UI/JoyStickAndButton/SneakyJoystick.h"
#include "UI/JoyStickAndButton/SneakyJoystickSkinnedBase.h"
#include "Utils.h"

UI_JoyStick::UI_JoyStick()
{
}

UI_JoyStick::~UI_JoyStick()
{
}

bool UI_JoyStick::init()
{
    if (!Super::init())
        return false;

    auto visibleSize = _director->getVisibleSize();
    //auto joyPos = Vec2(visibleSize) * 0.25f;
    //auto joyPos = Utils::GetScreenPos(PivotPoint::LeftBottom, 0.15f, 0.15f);
    this->scheduleUpdate();

    //---------

    // 베이스 인스턴스
    pJoystickBase = new SneakyJoystickSkinnedBase();
    pJoystickBase->init();

    // cocos2d-x 레퍼런스 카운티 시스템의 관리 하에 놓이도록 한다
    pJoystickBase->autorelease();

    // 조이스틱 위치 설정
    // pJoystickBase->setPosition(joyPos);

    // 조이스틱 백그라운드 이미지 설정
    auto bg = Sprite::create("UI/joy1.png");
    pJoystickBase->setBackgroundSprite(bg);

    // 조이스틱 이미지 설정
    auto thumb = Sprite::create("UI/joy2.png");
    pJoystickBase->setThumbSprite(thumb);

   //  pJoystickBase->setScale(0.75f);
    //---------

    // 조이스틱 인스턴스
    pJoystick = new SneakyJoystick();

    // 초기화
    pJoystick->initWithRect(Rect(0, 0, 160, 160));

    // cocos2d-x 레퍼런스 카운티 시스템의 관리 하에 놓이도록 한다
    pJoystick->autorelease();

    // 조이스틱을 얹어준다
    pJoystickBase->setJoystick(pJoystick);

    // Scene에 추가한다
    this->addChild(pJoystickBase);

 

    return true;
}
