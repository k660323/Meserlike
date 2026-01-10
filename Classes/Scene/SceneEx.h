#pragma once
#include "cocos2d.h"
#include "Define.h"
#include "ui/CocosGUI.h"
#include "Manager/Managers.h"
#include "Manager/Core/SceneManager.h"

class UI_Base;

namespace cocos2d
{
	class Node;
}

class SceneEx : public cocos2d::Scene
{
	using Super = cocos2d::Scene;
public:
	virtual bool init() override;

	// 현재 Scene으로 진입할 때 자동으로 호출되는 함수
	virtual void onEnter();

	virtual void update(float dt) override;

	// 현재 Scene을 빠져나갈 때 자동으로 호출되는 함수
	virtual void onExit();

	cocos2d::Vec2 GetObjectLayerPos();
	cocos2d::Layer* GetObjectLayer();
	void AddObjectLayer(cocos2d::Node* object, int layer = 0);
	void AddUILayer(UI_Base* ui);

	CREATE_FUNC(SceneEx);

protected:
	cocos2d::Layer* object_Layer;
	cocos2d::Layer* ui_Layer;
};