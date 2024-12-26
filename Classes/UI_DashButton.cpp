#include "UI_DashButton.h"
#include "Managers.h"
#include "GameManager.h"
#include "Player.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"
#include "InputManager.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

UI_DashButton::UI_DashButton()
{

}

UI_DashButton::~UI_DashButton()
{
}

bool UI_DashButton::init()
{
    if (!Super::init())
        return false;

 
    // cooltimeBar->setPosition(pBtnBase->getPosition());

    auto player = Managers::Game()->GetPlayer();
    if (player)
    {
        player->dashStartDelegate.addCallback([this](float max)
            {
                Sprite* cooltimeBar = Sprite::create("UI/Button_Normal.png");
                cooltimeBar->setAnchorPoint(Vec2(0.5f, 0.5f));
                cooltimeBar->setColor(Color3B::YELLOW);

                // ProgressTo ¾×¼Ç
                auto to = ProgressTo::create(max, 100.0f);

                pTimer = ProgressTimer::create(cooltimeBar);
                pTimer->setType(ProgressTimer::Type::BAR);
                pTimer->setPosition(pBtnBase->getPosition() - Vec2(27.7, 23.5));
                pTimer->setScale(2.0f);
                this->addChild(pTimer);

                pTimer->runAction(to);

                auto action = Sequence::create(
                    DelayTime::create(max),
                    CallFunc::create([this]() { 
                        if (this == nullptr)
                            return;
                        if (pTimer)
                            pTimer->removeFromParent();
                        }),
                    nullptr);

                this->runAction(action);
            });

    }

    return true;
}

void UI_DashButton::onEnter()
{
    Super::onEnter();

}

void UI_DashButton::onExit()
{
    Super::onExit();
}

void UI_DashButton::update(float dt)
{
    auto btn = pBtn->getValue();

    if (btn)
    {
        auto player = Managers::Game()->GetPlayer();
        if (player)
            player->Dash();
    }
}
