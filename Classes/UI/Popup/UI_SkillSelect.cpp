#include "UI_SkillSelect.h"
#include "Utils.h"
#include "ui/CocosGUI.h"
#include "Manager/Managers.h"
#include "Manager/Core/SoundManager.h"
#include "Manager/Core/UIManager.h"
#include "Manager/Contents/GameManager.h"
#include "UI/Etc/UI_SkillSlotBtn.h"

USING_NS_CC;
using namespace ui;

UI_SkillSelect::UI_SkillSelect()
{
}

UI_SkillSelect::~UI_SkillSelect()
{
}

bool UI_SkillSelect::init()
{
    if (!Super::init())
        return false;

    // 뒷 배경
    background = ImageView::create("UI/Button_Normal.png");
    background->setScale9Enabled(true);
    background->setContentSize(Utils::GetVisibleSize());
    background->setAnchorPoint(Vec2(0.5f, 0.5f));
    background->setColor(Color3B::BLACK);
    background->setOpacity(220);
    background->setTouchEnabled(true);
    background->setPosition(Utils::GetScreenPos(PivotPoint::Center));
    this->addChild(background);

    mainBackground = Sprite::create("UI/AllianceUI.backgrnd.png");
    mainBackground->setAnchorPoint(Vec2(0.5f, 0.5f));
    mainBackground->setPosition(Utils::GetScreenPos(PivotPoint::Center));
    this->addChild(mainBackground);

    //closeButton = Button::create("UI/BtCancel.normal.0.png", "UI/BtCancel.pressed.0.png", "UI/BtCancel.disabled.0.png");
    //closeButton->setAnchorPoint(Vec2(1.0f, 1.0f));
    //closeButton->setPosition(Utils::GetRelativeNodePos(PivotPoint::RightTop, mainBackground));
    //// 이벤트 리스너
    //closeButton->addTouchEventListener([&](Ref* pSender,
    //    Widget::TouchEventType type)
    //    {
    //        switch (type)
    //        {
    //        case cocos2d::ui::Widget::TouchEventType::BEGAN:
    //            Managers::Sound()->PlaySound2D("Sound/MenuDown.mp3");
    //            break;
    //        case cocos2d::ui::Widget::TouchEventType::ENDED:
    //            Managers::UI()->ClosePopupUI();
    //            break;
    //        }
    //    });
   //  this->addChild(closeButton);

    // 스킬 슬롯 생성
    CreateSkillSlotBnt();

    return true;
}

void UI_SkillSelect::onEnter()
{
    Super::onEnter();
    _director->pause();
}

void UI_SkillSelect::onExit()
{
    _director->resume();
    Super::onExit();
}

void UI_SkillSelect::CreateSkillSlotBnt()
{
    auto vec = Managers::Game()->GetRandomSkillId();

    if (vec.size() == 0)
    {
        Managers::UI()->ClosePopupUI();
        return;
    }

    for (int i = 0; i < vec.size(); i++)
    {
        UI_SkillSlotBtn* skillSlotBnt = UI_SkillSlotBtn::create();

        // 랜덤으로 배정 예정
        skillSlotBnt->SetSkillData(vec[i].first, vec[i].second);

        skillSlotBnt->setAnchorPoint(Vec2(0.5f, 0.5f));
        this->addChild(skillSlotBnt);
        skillSlotBnt->setPosition(Utils::GetRelativeNodePosFromParent(PivotPoint::Center, skillSlotBnt, -0.168f, -0.08f) + Size(215 * i, 0));
    
    }
}
