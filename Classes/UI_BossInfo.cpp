#include "UI_BossInfo.h"
#include "ui/CocosGUI.h"
#include "Managers.h"
#include "DataManager.h"
#include "Data.h"
#include "Utils.h"
#include "BossMonster.h"
#include "Stat.h"
USING_NS_CC;
using namespace ui;

UI_BossInfo::UI_BossInfo()
{
    _owner = nullptr;
}

UI_BossInfo::~UI_BossInfo()
{
}

bool UI_BossInfo::init()
{
    if (!Super::init())
        return false;

    bossHpBarBackground = Sprite::create("UI/gauge.hpFlash.1.png");
    bossHpBarBackground->setAnchorPoint(Vec2(0.5f, 0.5f));
    bossHpBarBackground->setPosition(Utils::GetScreenPos(PivotPoint::Top, 0.0f, -0.13f));
    bossHpBarBackground->setScale(2.0f);
    this->addChild(bossHpBarBackground);

    bossHpBar = LoadingBar::create("UI/Box.png");
    bossHpBar->setAnchorPoint(Vec2(0.5f, 0.5f));
    bossHpBar->setPosition(Utils::GetScreenPos(PivotPoint::Top, 0.0f, -0.13f));
    bossHpBar->setScale(4.3f, 0.65f);
    bossHpBar->setScale9Enabled(true);
    bossHpBar->setDirection(LoadingBarType::LEFT);
    bossHpBar->setColor(Color3B::RED);
    bossHpBar->setPercent(100.0f);
    
    this->addChild(bossHpBar);

    TTFConfig ttfConfig("fonts/MaplestoryBold.ttf", 20);
    bossHpText = Label::createWithTTF(ttfConfig, "0 / 0");
    bossHpText->setAnchorPoint(Vec2(0.5f, 0.5f));
    bossHpText->enableShadow(Color4B::BLACK, Size(2, -2));
    bossHpText->setPosition(Utils::GetRelativeNodePos(PivotPoint::Center, bossHpBarBackground));
    bossHpText->setTextColor(Color4B::WHITE);
    this->addChild(bossHpText);

    bossImage = Sprite::create("UI/Box.png");
    bossImage->setAnchorPoint(Vec2(0.5f, 0.5f));
    bossImage->setPosition(Utils::GetRelativeNodePos(PivotPoint::Left, bossHpBarBackground, -0.6f, 0.0f));

    this->addChild(bossImage);

    return true;
}

void UI_BossInfo::SetInit(BossMonster* bossMonster)
{
    _owner = bossMonster;
    auto data = Managers::Data()->GetMonsterInfoData(bossMonster->GetMonsterType());
    auto spriteData = Managers::Data()->GetSpriteData(data.spriteId);
    bossImage->setTexture(spriteData.uiImagePath);

    auto stat = bossMonster->GetStat();

    stat->curHpDelegate.addCallback([this](float curHp, float maxHp) {
        std::string str = std::to_string(curHp) + " / " + std::to_string(maxHp);
        bossHpBar->setPercent((curHp / maxHp) * 100);
        });

    stat->curHpDelegate.addCallback([this](float curHp, float maxHp) {
        std::string str = std::to_string((int)curHp) + " / " + std::to_string((int)maxHp);
        bossHpText->setString(str);
        });

    stat->maxHpDelegate.addCallback([this](float curHp, float maxHp) {
        std::string str = std::to_string(curHp) + " / " + std::to_string(maxHp);
        bossHpBar->setPercent((curHp / maxHp) * 100);
        });

    stat->maxHpDelegate.addCallback([this](float curHp, float maxHp){
        std::string str = std::to_string((int)curHp) + " / " + std::to_string((int)maxHp);
        bossHpText->setString(str);
    });

  
    stat->maxHpDelegate.invoke(stat->GetCurHp(), stat->GetTotalMaxHp());
}
