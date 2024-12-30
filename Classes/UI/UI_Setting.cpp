#include "UI_Setting.h"
#include "Utils.h"
#include "SceneEx.h"
#include "ui/CocosGUI.h"
#include "SoundManager.h"

USING_NS_CC;
using namespace ui;

UI_Setting::UI_Setting()
{
}

UI_Setting::~UI_Setting()
{
}

bool UI_Setting::init()
{
	if (!Super::init())
		return false;

    // 뒷 배경
	ImageView* background = ImageView::create("UI/Button_Normal.png");
	background->setScale9Enabled(true);
	background->setContentSize(Utils::GetVisibleSize());
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
	background->setColor(Color3B::BLACK);
	background->setOpacity(220);
	background->setTouchEnabled(true);
	background->setPosition(Utils::GetScreenPos(PivotPoint::Center));
	this->addChild(background);

    // UI 배경
    ImageView* background2 = ImageView::create("UI/MapleStyle.backgrnd1.png");
    background2->setAnchorPoint(Vec2(0.5f, 0.5f));
    background2->setPosition(Utils::GetScreenPos(PivotPoint::Center));
    background2->setTouchEnabled(true);
    this->addChild(background2);

    // 타이틀
    TTFConfig ttfConfig = TTFConfig("fonts/MaplestoryBold.ttf", 50);
    Label* title = Label::createWithTTF(ttfConfig, "옵션");
    title->setAnchorPoint(Vec2(0.5f, 1.0f));
    background2->addChild(title);
    title->setPosition(Utils::GetRelativeNodePosFromParent(PivotPoint::Top, title, 0.0f, -0.07f));

    // 나가기 버튼
    Button* exitButton = Button::create(
        "UI/BtCancel.normal.0.png",
        "UI/BtCancel.pressed.0.png",
        "UI/BtCancel.disabled.0.png");

    exitButton->setScale9Enabled(true);
    exitButton->setAnchorPoint(Vec2(1, 1));
    background2->addChild(exitButton);
    exitButton->setPosition(Utils::GetRelativeNodePosFromParent(PivotPoint::RightTop, exitButton));

    // 이벤트 리스너
    exitButton->addTouchEventListener([&](Ref* pSender,
        Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                Managers::Sound()->PlaySound2D("Sound/MenuDown.mp3");
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                Managers::Sound()->SaveSoundData();
                ClosePopupUI();
                break;
            }
        });
   
    // Sound Text
    {
        // 폰트
        TTFConfig ttfConfig = TTFConfig("fonts/MaplestoryBold.ttf", 30);
        Label* SoundLabel = Label::createWithTTF(ttfConfig, "사운드");
        SoundLabel->setTextColor(Color4B::WHITE);
        SoundLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
        background2->addChild(SoundLabel);
        SoundLabel->setPosition(Utils::GetRelativeNodePosFromParent(PivotPoint::Center, SoundLabel, -0.37f, 0.06f));
        
    }

    // Sound cocos2d::ui::Slider
    {
        auto soundSlider = Slider::create();

        // 슬라이더 트랙 이미지
        soundSlider->loadBarTexture("UI/Slider_Back.png");
        // 슬라이더 조절 포인터 이미지
        soundSlider->loadSlidBallTextures("UI/SliderNode_Normal.png",
            "UI/SliderNode_Press.png", "UI/SliderNode_Disable.png");
        // 슬라이더 액티브 이미지
        soundSlider->loadProgressBarTexture("UI/Slider_PressBar.png");

        // 터치 이벤트 리스너
        soundSlider->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type)
            {
                switch (type)
                {
                case cocos2d::ui::Widget::TouchEventType::BEGAN:
                    break;
                case cocos2d::ui::Widget::TouchEventType::MOVED:
                    
                    break;
                case cocos2d::ui::Widget::TouchEventType::ENDED:
                    break;
                case cocos2d::ui::Widget::TouchEventType::CANCELED:
                    break;
                default:
                    break;
                }
            });

        // 값 초기화
        soundSlider->setPercent(Managers::Sound()->GetVolume() * 100);

        // 상태 이벤트 리스너
        soundSlider->addEventListener([&](Ref* pSender, ui::Slider::EventType type)
            {
                // 퍼센티지 가져오기
                auto slider = dynamic_cast<Slider*>(pSender);
                int percent = slider->getPercent();

                switch (type)
                {
                case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
                    Managers::Sound()->SetVolume(percent * 0.01f);
                    break;
                case cocos2d::ui::Slider::EventType::ON_SLIDEBALL_DOWN:
                    break;
                case cocos2d::ui::Slider::EventType::ON_SLIDEBALL_UP:
                    break;
                case cocos2d::ui::Slider::EventType::ON_SLIDEBALL_CANCEL:
                    break;
                default:
                    break;
                }
            });
        this->addChild(soundSlider);
        soundSlider->setPosition(Utils::GetRelativeNodePosFromParent(PivotPoint::Center, soundSlider, 0.05f, 0.05f));
    }

    // BGM Text
    {
        // 폰트
        TTFConfig ttfConfig = TTFConfig("fonts/MaplestoryBold.ttf", 30);
        Label* BgmLabel = Label::createWithTTF(ttfConfig, "배경 음악");
        BgmLabel->setTextColor(Color4B::WHITE);
        BgmLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
        background2->addChild(BgmLabel);
        BgmLabel->setPosition(Utils::GetRelativeNodePosFromParent(PivotPoint::Center, BgmLabel, -0.4f, -0.06f));
    }

    // BGM cocos2d::ui::Slider
    {
        auto bgmSlider = Slider::create();

        // 슬라이더 트랙 이미지
        bgmSlider->loadBarTexture("UI/Slider_Back.png");
        // 슬라이더 조절 포인터 이미지
        bgmSlider->loadSlidBallTextures("UI/SliderNode_Normal.png",
            "UI/SliderNode_Press.png", "UI/SliderNode_Disable.png");
        // 슬라이더 액티브 이미지
        bgmSlider->loadProgressBarTexture("UI/Slider_PressBar.png");

        // 터치 이벤트 리스너
        bgmSlider->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type)
            {
                switch (type)
                {
                case cocos2d::ui::Widget::TouchEventType::BEGAN:
                    break;
                case cocos2d::ui::Widget::TouchEventType::MOVED:

                    break;
                case cocos2d::ui::Widget::TouchEventType::ENDED:
                    break;
                case cocos2d::ui::Widget::TouchEventType::CANCELED:
                    break;
                default:
                    break;
                }
            });

        // 값 초기화
        bgmSlider->setPercent(Managers::Sound()->GetVolume(SoundType::BGM) * 100);

        // 상태 이벤트 리스너
        bgmSlider->addEventListener([&](Ref* pSender, ui::Slider::EventType type)
            {
                // 퍼센티지 가져오기
                auto slider = dynamic_cast<Slider*>(pSender);
                int percent = slider->getPercent();

                switch (type)
                {
                case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
                    Managers::Sound()->SetVolume(percent * 0.01f, SoundType::BGM);
                    break;
                case cocos2d::ui::Slider::EventType::ON_SLIDEBALL_DOWN:
                    break;
                case cocos2d::ui::Slider::EventType::ON_SLIDEBALL_UP:
                    break;
                case cocos2d::ui::Slider::EventType::ON_SLIDEBALL_CANCEL:
                    break;
                default:
                    break;
                }
            });
        this->addChild(bgmSlider);
        bgmSlider->setPosition(Utils::GetRelativeNodePosFromParent(PivotPoint::Center, bgmSlider, 0.05f, -0.05f));
    }

	return true;
}
