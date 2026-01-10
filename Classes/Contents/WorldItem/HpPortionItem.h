#pragma once
#include "WorldItem.h"

class HpPortionItem : public WorldItem
{
	using Super = WorldItem;
public:
	HpPortionItem();
	virtual ~HpPortionItem();

	virtual bool init() override;

	virtual bool onContactEnter(cocos2d::PhysicsContact& contact) override;
	virtual void onContactExit(cocos2d::PhysicsContact& contact) override;

	CREATE_FUNC(HpPortionItem);

protected:
	float val;
};