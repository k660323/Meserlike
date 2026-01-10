#include "UI_ResultWindow.h"
#include "ui/CocosGUI.h"
#include "Utils.h"
#include "Manager/Managers.h"
#include "Manager/Core/SoundManager.h"
#include "Manager/Core/SceneManager.h"
#include "Manager/Contents/GameManager.h"
#include "Contents/Creature/Player.h"
#include "Contents/Creature/Monster.h"
#include "Contents/Controllers/BaseController.h"
USING_NS_CC;

using namespace ui;

UI_ResultWindow::UI_ResultWindow()
{
}

UI_ResultWindow::~UI_ResultWindow()
{
}

bool UI_ResultWindow::init()
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

	// 메인 배경
	mainBackground = Sprite::create("UI/UserList.backgrnd1.png");
	mainBackground->setAnchorPoint(Vec2(0.5f, 0.5f));
	mainBackground->setPosition(Utils::GetScreenPos(PivotPoint::Center));
	this->addChild(mainBackground);
	
	// 폰트
	TTFConfig ttfConfig = TTFConfig("fonts/MaplestoryBold.ttf", 30);

	// 현재 라운드
	roundLabel = Label::createWithTTF(ttfConfig, "현재 라운드 : " + std::to_string(std::min(Managers::Game()->GetRound(), Managers::Data()->GetMaxRound() - 1)));
	roundLabel->setTextColor(Color4B::WHITE);
	roundLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	mainBackground->addChild(roundLabel);
	roundLabel->setPosition(Utils::GetRelativeNodePosFromParent(PivotPoint::Center, roundLabel, 0.0f, 0.3f));
	// 총합 점수
	std::string totalScore = "총 점수 : " + std::to_string(Managers::Game()->GetScore());
	totalLabel = Label::createWithTTF(ttfConfig, totalScore);
	totalLabel->setTextColor(Color4B::WHITE);
	totalLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	mainBackground->addChild(totalLabel);
	totalLabel->setPosition(Utils::GetRelativeNodePosFromParent(PivotPoint::Center, totalLabel, 0.0f, 0.15f));

	// 생존 여부
	std::string aliveStr =  (Managers::Game()->GetPlayer()->GetBaseController()->GetStat() == State::Dead) ? "생존 여부 : 사망" : "생존 여부 : 생존";
	aliveLabel = Label::createWithTTF(ttfConfig, aliveStr);
	aliveLabel->setTextColor(Color4B::WHITE);
	aliveLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	mainBackground->addChild(aliveLabel);
	aliveLabel->setPosition(Utils::GetRelativeNodePosFromParent(PivotPoint::Center, aliveLabel, 0.0f, 0.0f));

	// 메인 화면으로
	mainButton = Button::create("UI/Button_Normal.png", "UI/Button_Press.png", "UI/Button_Disable.png");
	mainButton->setAnchorPoint(Vec2(0.5f, 0.5f));
	mainButton->setPosition(Utils::GetRelativeNodePos(PivotPoint::Center, mainBackground, 0.0f, -0.3f));
	mainButton->setScale9Enabled(true);
	mainButton->setTitleFontName("fonts/MaplestoryBold.ttf");
	mainButton->setTitleFontSize(35.0f);
	mainButton->setSize(Size(250, 75));
	mainButton->setTitleText("메인 화면");
	mainButton->setTitleColor(Color3B::BLACK);
	// 이벤트 리스너
	mainButton->addTouchEventListener([&](Ref* pSender,
		Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				Managers::Sound()->PlaySound2D("Sound/BtMouseClick.mp3");
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				Managers::Scene()->PopScene();
				break;
			}
		});
	this->addChild(mainButton);

	return true;
}

void UI_ResultWindow::onEnter()
{
	Super::onEnter();
	_director->pause();
}

void UI_ResultWindow::onExit()
{
	_director->resume();
	Super::onExit();
}
