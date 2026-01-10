#include "UI_GameScene.h"
#include "UI/Scene/Sub/UI_JoyStick.h"
#include "UI/Scene/Sub/UI_DashButton.h"
#include "ui/CocosGUI.h"
#include "Utils.h"
#include "Manager/Managers.h"
#include "Manager/Core/SoundManager.h"
#include "Manager/Core/UIManager.h"
#include "Manager/Contents/GameManager.h"
#include "Contents/Creature/Player.h"
#include "Contents/Stat/PlayerStat.h"
#include "Contents/Creature/BossMonster.h"
#include "UI/Scene/Sub/UI_BossInfo.h"

USING_NS_CC;
using namespace ui;

UI_GameScene::UI_GameScene()
{
}

UI_GameScene::~UI_GameScene()
{
}

bool UI_GameScene::init()
{
    if (!Super::init())
        return false;

    auto player = Managers::Game()->GetPlayer();
    auto stat = player->GetPlayerStat();
    // 카드 선택창 오픈

    // 카드 선택후 게임 진행 (게임 관련 로직은 해당 씬에서 진행)


    // 플레이어 UI 생성(클래스 따로 제작)
    auto ui_JoyStick = UI_JoyStick::create();
    ui_JoyStick->setAnchorPoint(Vec2(0.0f, 0.0f));
    ui_JoyStick->setScale(0.75f);
    ui_JoyStick->setPosition(Utils::GetScreenPos(PivotPoint::LeftBottom, 0.2f, 0.2f));
    this->addChild(ui_JoyStick);

    auto ui_Button = UI_DashButton::create();
    this->addChild(ui_Button);


    // 경험치 바
    {
        // 경험치 배경
        auto expBarBg = Sprite::create("UI/EXPBar.1280.layerback.png");
        expBarBg->setPosition(Utils::GetScreenPos(PivotPoint::Top, 0.0f, -0.05f));
        expBarBg->setScale(0.4f, 2.5f);

        // 경험치바
        expBar = LoadingBar::create("UI/EXPBar.1280.layergauge.png");
        expBar->setAnchorPoint(Vec2(0.0f, 0.0f));
        // 로딩바의 진행 방향 설정 (LEFT로 하면 왼쪽 -> 오른쪽)
        expBar->setDirection(LoadingBarType::LEFT);
        // 진행 상황(백분율);
        expBar->setPercent(0.0f);

        stat->expDelegate.addCallback([this](int curExp, int maxExp) { expBar->setPercent(((float)curExp / maxExp) * 100.0f); });

        expBarBg->addChild(expBar);
        expBar->setPosition(expBar->getPosition() + Vec2(20.0f, 1.5f));
        this->addChild(expBarBg);
        //this->addChild(expBar);

        TTFConfig ttfConfig("fonts/MaplestoryBold.ttf", 25);
        std::string expStr = std::to_string(stat->GetExp()) + " / " + std::to_string(stat->GetMaxExp());
        expText = Label::createWithTTF(ttfConfig, expStr);
        expText->setAnchorPoint(Vec2(0.5f, 0.5f));
        expText->setPosition(Utils::GetRelativeNodePos(PivotPoint::Center, expBarBg));
        expText->enableShadow(Color4B::BLACK, Size(2, -2));
        this->addChild(expText);

        stat->expDelegate.addCallback([this](int curExp, int maxExp) {
            std::string expStr = std::to_string(curExp) + " / " + std::to_string(maxExp);
            expText->setString(expStr);
            });
    }

    // 라운드 Label
    {
        TTFConfig ttfConfig("fonts/MaplestoryBold.ttf", 50);
        roundText = Label::createWithTTF(ttfConfig, "Round : 0");
        roundText->setAnchorPoint(Vec2(0.0f, 1.0f));
        roundText->setPosition(Utils::GetScreenPos(PivotPoint::LeftTop, 0.01f, -0.01f));
        roundText->enableShadow(Color4B::BLACK, Size(2, -2));
        this->addChild(roundText);

        Managers::Game()->roundDelegate.addCallback([this](int round) {roundText->setString("Round : " + std::to_string(round)); });
    }

    // 우측 상단 옵션창 활성화
    {
        Button* optionBtn = Button::create("UI/BtMenu.normal.0.png", "UI/BtMenu.pressed.0.png", "UI/BtMenu.disabled.0.png");
        //optionBtn->setScale9Enabled(true);
        //optionBtn->setSize(Size(300, 200));
        optionBtn->setAnchorPoint(Vec2(1.0f, 1.0f));

        // 이벤트 리스너
        optionBtn->addTouchEventListener([&](Ref* pSender,
            Widget::TouchEventType type)
            {
                switch (type)
                {
                case cocos2d::ui::Widget::TouchEventType::BEGAN:
                    Managers::Sound()->PlaySound2D("Sound/BtMouseClick.mp3");
                    break;
                case cocos2d::ui::Widget::TouchEventType::ENDED:
                    Managers::UI()->ShowPopupUI(PopupType::UI_PauseMenuWindow);
                    break;
                }
            });

        optionBtn->setPosition(Utils::GetScreenPos(PivotPoint::RightTop, -0.01f, -0.03f));
        this->addChild(optionBtn);
    }
    
    // 플레이어 HP
    {
        auto* hpBackground = Sprite::create("UI/gauge.hpFlash.0.png");
        hpBackground->setAnchorPoint(Vec2(0.5f, 0.5f));
        hpBackground->setPosition(Utils::GetScreenPos(PivotPoint::CenterBottom, 0.0f, 0.05f));
        hpBackground->setScale(2.0f);
        this->addChild(hpBackground);

        hpBar = LoadingBar::create("UI/Box.png");
        hpBar->setAnchorPoint(Vec2(0.5f, 0.5f));
        hpBar->setPosition(Utils::GetScreenPos(PivotPoint::CenterBottom, 0.0f, 0.05f));
        hpBar->setScale(4.3f, 0.65f);
        hpBar->setScale9Enabled(true);
        hpBar->setDirection(LoadingBarType::LEFT);
        hpBar->setColor(Color3B::RED);
        hpBar->setPercent(100.0f);
        this->addChild(hpBar);

        stat->curHpDelegate.addCallback([this](float curHp, float maxHp) {  hpBar->setPercent((curHp / maxHp) * 100);});
        stat->maxHpDelegate.addCallback([this](float curHp, float maxHp) { hpBar->setPercent((curHp / maxHp) * 100); });

        TTFConfig ttfConfig("fonts/MaplestoryBold.ttf", 20);
        std::string str = "HP : " + std::to_string((int)stat->GetCurHp()) + " / " + std::to_string((int)stat->GetMaxHp());
        hpText = Label::createWithTTF(ttfConfig, str);
        hpText->setAnchorPoint(Vec2(0.5f, 0.5f));
        hpText->setPosition(Utils::GetRelativeNodePos(PivotPoint::Center, hpBackground));
        hpText->setTextColor(Color4B::BLACK);
        this->addChild(hpText);

        stat->curHpDelegate.addCallback([this](float curHp, float maxHp) {
            std::string str = "HP : " + std::to_string((int)curHp) + " / " + std::to_string((int)maxHp);
            hpText->setString(str);
            });

        stat->maxHpDelegate.addCallback([this](float curHp, float maxHp) {
            std::string str = "HP : " + std::to_string((int)curHp) + " / " + std::to_string((int)maxHp);
            hpText->setString(str);
            });
    }

    // 레벨 
    {
        TTFConfig ttfConfig("fonts/MaplestoryBold.ttf", 35);
        levelText = Label::createWithTTF(ttfConfig, "Lv : 1");
        levelText->setPosition(Utils::GetScreenPos(PivotPoint::CenterBottom, -0.18f, 0.05f));
        levelText->enableShadow(Color4B::BLACK, Size(2, -2));
        this->addChild(levelText);

        stat->levelDelegate.addCallback([this](int level) {
            std::string str = "Lv : " + std::to_string(level);
            levelText->setString(str);
            });
    }

    return true;
}

