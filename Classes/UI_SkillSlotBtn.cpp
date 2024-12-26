#include "UI_SkillSlotBtn.h"
#include "ui/CocosGUI.h"
#include "Utils.h"
#include "Managers.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "Player.h"
#include "SkillBook.h"
#include "SkillBase.h"
#include "DataManager.h"
#include "UIManager.h"
USING_NS_CC;
using namespace ui;

UI_SkillSlotBtn::UI_SkillSlotBtn()
{
}

UI_SkillSlotBtn::~UI_SkillSlotBtn()
{
}

bool UI_SkillSlotBtn::init()
{
    if (!Super::init())
        return false;

    backGroundButton = Button::create("UI/UserList.Popup.FriendInfo.backgrnd1.png", "UI/UserList.Popup.FriendInfo.backgrnd1.png", "UI/UserList.Popup.FriendInfo.backgrnd1.png");
    backGroundButton->setScale9Enabled(true);
    backGroundButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    backGroundButton->setSize(Size(215, 372.5));
    this->addChild(backGroundButton);

    // 이벤트 리스너
    backGroundButton->addTouchEventListener([&](Ref* pSender,
        Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                Managers::Sound()->PlaySound2D("Sound/MenuDown.mp3");
                // 스킬 적용
                RegisterOrUpgradeSkill();
                Managers::UI()->ClosePopupUI();
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                
                break;
            }
        });

    skillImage = Sprite::create("UI/Box.png");
    skillImage->setAnchorPoint(Vec2(0.5f, 0.5f));
    backGroundButton->addChild(skillImage);
    skillImage->setPosition(Utils::GetRelativeNodePosFromParent(PivotPoint::Top, skillImage, 0.0f, -0.15f));
    
    TTFConfig ttfConfig = TTFConfig("fonts/MaplestoryBold.ttf", 20);
    skillName = Label::createWithTTF(ttfConfig, "스킬 이름 : 테스트");
    skillName->setAnchorPoint(Vec2(0.5f, 0.5f));
    skillName->setAlignment(TextHAlignment::CENTER);
    backGroundButton->addChild(skillName);
    skillName->setPosition(Utils::GetRelativeNodePosFromParent(PivotPoint::Top, skillImage, 0.0f, -0.3f));
    
    TTFConfig ttfConfig2 = TTFConfig("fonts/MaplestoryBold.ttf", 20);
    skillLevel = Label::createWithTTF(ttfConfig2, "Lv : 0");
    skillLevel->setAnchorPoint(Vec2(0.5f, 0.5f));
    skillLevel->setAlignment(TextHAlignment::CENTER);
    backGroundButton->addChild(skillLevel);
    skillLevel->setPosition(Utils::GetRelativeNodePosFromParent(PivotPoint::Top, skillImage, 0.0f, -0.4f));

    TTFConfig ttfConfig3 = TTFConfig("fonts/MaplestoryBold.ttf", 20);
    skillCommand = Label::createWithTTF(ttfConfig3, "스킬 설명창");
    skillCommand->setAnchorPoint(Vec2(0.5f, 0.5f));
    skillCommand->setWidth(200);
    skillCommand->setAlignment(TextHAlignment::CENTER);
    backGroundButton->addChild(skillCommand);
    skillCommand->setPosition(Utils::GetRelativeNodePosFromParent(PivotPoint::Top, skillImage, 0.0f, -0.5f));

    return true;
}

void UI_SkillSlotBtn::SetSkillData(int index, SkillId skillId)
{
    _index = index;
    _skillId = skillId;

    _skillInfo = Managers::Data()->GetSkillInfoData(skillId);
    skillImage->setTexture(_skillInfo.skillSpritePath);
    skillName->setString(_skillInfo.skillName);

    auto player = Managers::Game()->GetPlayer();
    auto skillBook = player->GetSkillBook();
    _skillBase = skillBook->GetSkill(skillId);

    if (_skillBase)
    {
        int nextLevel = _skillBase->GetLevel() + 1;

        if (_skillInfo.skillDatas.find(nextLevel) != _skillInfo.skillDatas.end())
        {
            skillLevel->setString("Lv : " + std::to_string(_skillInfo.skillDatas[nextLevel].level));
            skillCommand->setString(_skillInfo.skillDatas[nextLevel].command);
        }
    }
    else
    {
        if (_skillInfo.skillDatas.find(1) != _skillInfo.skillDatas.end())
        {
            skillLevel->setString("Lv : 1");
            skillCommand->setString(_skillInfo.skillDatas[1].command);
        }
    }
}

void UI_SkillSlotBtn::RegisterOrUpgradeSkill()
{
    Managers::Game()->SelectSkill(_index, _skillId, _skillInfo, _skillBase);
}
