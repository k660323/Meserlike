#include "UI_Button.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"


UI_Button::UI_Button()
{

}

UI_Button::~UI_Button()
{
}

bool UI_Button::init()
{
    if (!Super::init())
        return false;

    auto visibleSize = _director->getVisibleSize();
    auto btnDimension = Rect(0, 0, 64, 64);
    auto btnPos = Vec2(visibleSize.width * 0.8f, visibleSize.height * 0.25f);

    this->scheduleUpdate();

    // 버튼 베이스 인스턴스
    pBtnBase = new SneakyButtonSkinnedBase();
    pBtnBase->init();
    pBtnBase->autorelease();
    pBtnBase->setPosition(btnPos);
    pBtnBase->setScale(2.0f);

    //---------

    // 버튼에 사용할 이미지 설정 (4개를 모두 한꺼번에 설정해야 안 터짐)
    pBtnBase->setDefaultSprite(Sprite::create("UI/Button_Disable.png"));
    pBtnBase->setPressSprite(Sprite::create("UI/Button_Press.png"));
    pBtnBase->setActivatedSprite(Sprite::create("UI/Button_Normal.png"));
    pBtnBase->setDisabledSprite(Sprite::create("UI/Button_Disable.png"));

    //---------

    // 인스턴스 생성
    pBtn = new SneakyButton();
    pBtn->initWithRect(btnDimension);
    pBtn->autorelease();
    pBtnBase->setButton(pBtn);

    pBtn->setIsHoldable(true);
    // pBtn->setIsActive(true);
    // pBtn->setIsToggleable(true);

    this->addChild(pBtnBase);

    //---------

    return true;
}
