#include "SceneEx.h"
#include "Manager/Managers.h"
#include "Manager/Core/SceneManager.h"
#include "Manager/Contents/MapManager.h"
#include "Manager/Contents/GameManager.h"
#include "Contents/Creature/Player.h"
#include "UI/UI_Base.h"
USING_NS_CC;

bool SceneEx::init()
{
    if (!Super::init())
        return false;

	

    return true;
}

void SceneEx::onEnter()
{
	Super::onEnter();

	Managers::Scene()->SetCurrentScene(this);

	_eventDispatcher->removeAllEventListeners();
	Managers::GetInstance().Clear();
	
	this->scheduleUpdate();

	object_Layer = Layer::create();
	object_Layer->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(object_Layer);

	ui_Layer = Layer::create();
	ui_Layer->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(ui_Layer);
}

void SceneEx::update(float dt)
{
	if (Managers::Game()->GetPlayer() == false)
		return;
	
	Vec2 scenePos = Managers::Game()->GetPlayer()->getPosition();
	if (Managers::Map()->IsValidMap())
		scenePos = Managers::Map()->GetViewpointCenter(scenePos);
	object_Layer->setPosition(scenePos);

}

void SceneEx::onExit()
{
	this->unscheduleUpdate();
	Super::onExit();
}

cocos2d::Vec2 SceneEx::GetObjectLayerPos()
{
	return object_Layer->getPosition();
}

cocos2d::Layer* SceneEx::GetObjectLayer()
{
	return object_Layer;
}

void SceneEx::AddObjectLayer(cocos2d::Node* object, int layer)
{
	object_Layer->addChild(object, layer);
}

void SceneEx::AddUILayer(UI_Base* ui)
{
	ui_Layer->addChild(ui);
}

