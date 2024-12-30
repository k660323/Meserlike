#include "UI_PauseMenuWindow.h"
#include "ui/CocosGUI.h"
#include "Utils.h"
#include "Managers.h"
#include "SoundManager.h"
#include "UIManager.h"
#include "SceneManager.h"

USING_NS_CC;
using namespace ui;

UI_PauseMenuWindow::UI_PauseMenuWindow()
{

}

UI_PauseMenuWindow::~UI_PauseMenuWindow()
{

}

bool UI_PauseMenuWindow::init()
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

	mainBackground = Sprite::create("UI/UserList.Popup.FriendInfo.backgrnd1.png");
	mainBackground->setAnchorPoint(Vec2(0.5f, 0.5f));
	mainBackground->setPosition(Utils::GetScreenPos(PivotPoint::Center));
	this->addChild(mainBackground);

	closeButton = Button::create("UI/BtCancel.normal.0.png", "UI/BtCancel.pressed.0.png", "UI/BtCancel.disabled.0.png");
	closeButton->setAnchorPoint(Vec2(1.0f, 1.0f));
	closeButton->setPosition(Utils::GetRelativeNodePos(PivotPoint::RightTop, mainBackground));
	// 이벤트 리스너
	closeButton->addTouchEventListener([&](Ref* pSender,
		Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				Managers::Sound()->PlaySound2D("Sound/MenuDown.mp3");
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				Managers::UI()->ClosePopupUI();
				break;
			}
		});
	this->addChild(closeButton);

	settingButton = Button::create("UI/Button_Normal.png", "UI/Button_Press.png", "UI/Button_Disable.png");
	settingButton->setAnchorPoint(Vec2(0.5f, 0.5f));
	settingButton->setPosition(Utils::GetRelativeNodePos(PivotPoint::Center, mainBackground, 0.0f, 0.3f));
	settingButton->setScale9Enabled(true);
	settingButton->setTitleFontName("fonts/MaplestoryBold.ttf");
	settingButton->setTitleFontSize(35.0f);
	settingButton->setSize(Size(250, 75));
	settingButton->setTitleText("환경 설정");
	settingButton->setTitleColor(Color3B::BLACK);
	// 이벤트 리스너
	settingButton->addTouchEventListener([&](Ref* pSender,
		Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				Managers::Sound()->PlaySound2D("Sound/BtMouseClick.mp3");
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				Managers::UI()->ShowPopupUI(PopupType::UI_Setting);
				break;
			}
		});
	this->addChild(settingButton);


	mainButton = Button::create("UI/Button_Normal.png", "UI/Button_Press.png", "UI/Button_Disable.png");
	mainButton->setAnchorPoint(Vec2(0.5f, 0.5f));
	mainButton->setPosition(Utils::GetRelativeNodePos(PivotPoint::Center, mainBackground));
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

	exitButton = Button::create("UI/Button_Normal.png", "UI/Button_Press.png", "UI/Button_Disable.png");
	exitButton->setAnchorPoint(Vec2(0.5f, 0.5f));
	exitButton->setPosition(Utils::GetRelativeNodePos(PivotPoint::Center, mainBackground, 0.0f, -0.3f));
	exitButton->setScale9Enabled(true);
	exitButton->setTitleFontName("fonts/MaplestoryBold.ttf");
	exitButton->setTitleFontSize(35.0f);
	exitButton->setSize(Size(250, 75));
	exitButton->setTitleText("게임 종료");
	exitButton->setTitleColor(Color3B::BLACK);
	// 이벤트 리스너
	exitButton->addTouchEventListener([&](Ref* pSender,
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
	this->addChild(exitButton);

	return true;
}

void UI_PauseMenuWindow::onEnter()
{
	Super::onEnter();
	_director->pause();
}

void UI_PauseMenuWindow::onExit()
{
	_director->resume();
	Super::onExit();
}
