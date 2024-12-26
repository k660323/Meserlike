#include "UIManager.h"
#include "Define.h"
#include "UI_LobbyScene.h"
#include "UI_Popup.h"
#include "Managers.h"
#include "SceneManager.h"
#include "UI_Setting.h"
#include "UI_GameScene.h"
#include "SceneEx.h"
#include "UI_PauseMenuWindow.h"
#include "UI_ResultWindow.h"
#include "UI_SkillSelect.h"

UIManager::UIManager()
{
	currentUIScene = nullptr;
	ui_Root = nullptr;
}

UIManager::~UIManager()
{
}

void UIManager::Clear()
{
	if (currentUIScene)
		currentUIScene = nullptr;
	if (ui_Root)
	{
		ui_Root->release();
		ui_Root = nullptr;
	}
}

void UIManager::SetCanvas(cocos2d::Node* node, bool sort)
{

	if (sort)
	{
		node->setZOrder(_order++);
	}
	else
	{
		node->setZOrder(0);
	}
}

SceneType UIManager::GetUIType()
{
	return sceneUIType;
}

UI_Scene* UIManager::ShowSceneUI(SceneType type)
{
	switch (type)
	{
	case SceneType::Lobby:
		sceneUIType = SceneType::Lobby;
		currentUIScene = UI_LobbyScene::create();
		break;
	case SceneType::Game:
		sceneUIType = SceneType::Game;
		currentUIScene = UI_GameScene::create();
		break;
	default:
		break;
	}

	return currentUIScene;
}

UI_Scene* UIManager::GetUIScene()
{
	return currentUIScene;
}

UI_Popup* UIManager::ShowPopupUI(PopupType type)
{
	UI_Popup* popup;
	switch (type)
	{
	case PopupType::None:
		break;
	case PopupType::UI_Setting:
		popup = UI_Setting::create();
		break;
	case PopupType::UI_PauseMenuWindow:
		popup = UI_PauseMenuWindow::create();
		break;
	case PopupType::UI_ResultWindow:
		popup = UI_ResultWindow::create();
		break;
	case PopupType::UI_SkillSelect:
		popup = UI_SkillSelect::create();
		break;
	}

	if (popup)
	{
		_popupStack.push(popup);
		// Managers::Scene()->GetCurrentScene()->addChild(popup);
	}

	return popup;
}

void UIManager::ClosePopupUI()
{
	if (_popupStack.size() == 0)
		return;

	UI_Popup* popup = _popupStack.top();
	_popupStack.pop();

	_order--;

	if (popup)
		popup->removeFromParent();
}

void UIManager::ClosePopupUI(UI_Popup* popup)
{
	if (_popupStack.size() == 0)
		return;

	if (_popupStack.top() != popup)
		return;

	ClosePopupUI();
}

void UIManager::ClosePopupUIAll()
{
	for (int i = 0; i < PopupCount(); i++)
		ClosePopupUI();
}

int UIManager::PopupCount()
{
	return _popupStack.size();
}

void UIManager::AddChild(UI_Base* ui)
{
	Managers::Scene()->GetCurrentScene()->AddUILayer(ui);
}
