#pragma once
#include "UI_Scene.h"
#include "Define.h"

namespace cocos2d
{
	class Node;
}

class UI_Scene;
class UI_Popup;

class UIManager
{
public:
	UIManager();
	virtual ~UIManager();

	void Clear();

	void SetCanvas(cocos2d::Node* node, bool sort = true);

	SceneType GetUIType();
	UI_Scene* ShowSceneUI(SceneType type);
	UI_Scene* GetUIScene();

	UI_Popup* ShowPopupUI(PopupType type);
	void ClosePopupUI();
	void ClosePopupUI(UI_Popup* popup);
	void ClosePopupUIAll();

	int PopupCount();

	void AddChild(UI_Base* ui);

private:
	SceneType sceneUIType;
	UI_Scene* currentUIScene;

	std::stack<UI_Popup*> _popupStack;
	int _order = 10;

	cocos2d::Node* ui_Root;
};