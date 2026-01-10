#pragma once
#include "cocos2d.h"
#include "Bitmask.h"

class WorldItem : public cocos2d::Node
{
	using Super = cocos2d::Node;
public:
	WorldItem();
	virtual ~WorldItem();

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;

	virtual bool onContactEnter(cocos2d::PhysicsContact& contact);
	virtual void onContactExit(cocos2d::PhysicsContact& contact);

	CREATE_FUNC(WorldItem);

protected:
	cocos2d::EventListenerPhysicsContact* contact;
	cocos2d::Sprite* itemSprite;
};