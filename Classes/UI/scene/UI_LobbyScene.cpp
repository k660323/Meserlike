#include "UI_LobbyScene.h"
#include "Manager/Managers.h"
#include "Utils.h"
#include "Manager/Core/SceneManager.h"
#include "ui/CocosGUI.h"
#include "Manager/Core/UIManager.h"
#include "UI/Popup/UI_Popup.h"
#include "Scene/SceneEx.h"
#include "Manager/Core/SoundManager.h"

USING_NS_CC;
using namespace ui;

UI_LobbyScene::UI_LobbyScene()
{

}

UI_LobbyScene::~UI_LobbyScene()
{

}

bool UI_LobbyScene::init()
{
	if (!Super::init())
		return false;

    // 현재 실행 중인 게임 화면의 크기를 가져온다.
    auto visibleSize = Utils::GetVisibleSize();

    // 배경 이미지 생성
    cocos2d::Sprite*  background = Sprite::create("UI/Background/LobbyBackground.png");
    background->setAnchorPoint(Vec2(0.5f, 0.5f));
    background->setPosition(Utils::GetScreenPos(PivotPoint::Center));
    background->setContentSize(visibleSize);
    background->setLocalZOrder(-1);

    Bind<Sprite>(background, Sprites::background0);
    this->addChild(background);
    // 폰트
    ttfConfig = TTFConfig("fonts/MaplestoryBold.ttf", 60);
    
    // 제목
    Label*  titleLabel = Label::createWithTTF(ttfConfig, "메서라이크");
    titleLabel->setAnchorPoint(Vec2(0.5f, 1.0f));
    titleLabel->setPosition(Utils::GetScreenPos(PivotPoint::Top, 0.0f, -0.2f));
    titleLabel->setTextColor(Color4B::BLACK);
    Bind<Label>(titleLabel, Labels::titleLabel0);
    this->addChild(titleLabel);
    // 버튼

    // 시작 버튼
    {
        startBtn = Button::create(
            "UI/Button_Normal.png",
            "UI/Button_Press.png",
            "UI/Button_Disable.png");
        startBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
        startBtn->setScale9Enabled(true);
        startBtn->setTitleFontName("fonts/MaplestoryBold.ttf");
        startBtn->setTitleFontSize(35.0f);
        startBtn->setSize(Size(250, 75));
        // 버튼에 붙일 텍스트
        startBtn->setTitleText("시작 하기");
        startBtn->setTitleColor(Color3B::BLACK);
        // 이벤트 리스너
        startBtn->addTouchEventListener([&](Ref* pSender,
            Widget::TouchEventType type)
            {
                switch (type)
                {
                case cocos2d::ui::Widget::TouchEventType::BEGAN:
                    Managers::Sound()->PlaySound2D("Sound/BtMouseClick.mp3");
                    startBtn->setEnabled(false);
                    settingBtn->setEnabled(false);
                    exitBtn->setEnabled(false);
                    break;
                case cocos2d::ui::Widget::TouchEventType::ENDED:
                {
                    Managers::Sound()->PlaySound2D("Sound/GameIn.mp3");
                    auto action = Sequence::create(DelayTime::create(1.0f),
                        CallFunc::create([this]() {
                            Managers::Scene()->PushScene(SceneType::Game, 8);
                            }), nullptr);
                    this->runAction(action);
                }
                    break;
                default:
                    break;
                }
            });

        startBtn->setPosition(Utils::GetScreenPos(PivotPoint::CenterBottom, 0.0f, 0.4f));
        
        Bind<Button>(startBtn, Buttons::startBtn0);
        this->addChild(startBtn);
    }

    // 세팅 버튼
    {
        settingBtn = Button::create(
            "UI/Button_Normal.png",
            "UI/Button_Press.png",
            "UI/Button_Disable.png");

        settingBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
        settingBtn->setScale9Enabled(true);
        settingBtn->setTitleFontName("fonts/MaplestoryBold.ttf");
        settingBtn->setTitleFontSize(35.0f);
        settingBtn->setSize(Size(250, 75));
        // 버튼에 붙일 텍스트
        settingBtn->setTitleText("설정");
        settingBtn->setTitleColor(Color3B::BLACK);

        // 이벤트 리스너
        settingBtn->addTouchEventListener([&](Ref* pSender,
            Widget::TouchEventType type)
            {
                switch (type)
                {
                case cocos2d::ui::Widget::TouchEventType::BEGAN:
                    Managers::Sound()->PlaySound2D("Sound/BtMouseClick.mp3");
                    break;
                case cocos2d::ui::Widget::TouchEventType::ENDED:
                    auto popup = Managers::UI()->ShowPopupUI(PopupType::UI_Setting);
                    break;
                }
            });

        settingBtn->setPosition(Utils::GetScreenPos(PivotPoint::CenterBottom, 0.0f, 0.25f));
        Bind<Button>(settingBtn, Buttons::settingBtn1);
        this->addChild(settingBtn);
    }

    // 종료 버튼
    {
        exitBtn = Button::create(
            "UI/Button_Normal.png",
            "UI/Button_Press.png",
            "UI/Button_Disable.png");

        exitBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
        exitBtn->setScale9Enabled(true);
        exitBtn->setTitleFontName("fonts/MaplestoryBold.ttf");
        exitBtn->setTitleFontSize(35.0f);
        exitBtn->setSize(Size(250, 75));
        // 버튼에 붙일 텍스트
        exitBtn->setTitleText("종료");
        exitBtn->setTitleColor(Color3B::BLACK);
        // 이벤트 리스너
        exitBtn->addTouchEventListener([&](Ref* pSender,
            Widget::TouchEventType type)
            {
                switch (type)
                {
                case cocos2d::ui::Widget::TouchEventType::BEGAN:
                    Managers::Sound()->PlaySound2D("Sound/BtMouseClick.mp3");
                    break;
                case cocos2d::ui::Widget::TouchEventType::ENDED:
                    Director::getInstance()->end();
                    break;
                }
            });

        exitBtn->setPosition(Utils::GetScreenPos(PivotPoint::CenterBottom, 0.0f, 0.1f));
        Bind<Button>(exitBtn, Buttons::exitBtn2);
        this->addChild(exitBtn);
    }

	return true;
}

void UI_LobbyScene::onEnter()
{
    Super::onEnter();

    startBtn->setEnabled(true);
    settingBtn->setEnabled(true);
    exitBtn->setEnabled(true);

}
