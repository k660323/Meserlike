#include "BaseController.h"
#include "Creature.h"
#include "cocos2d.h"
USING_NS_CC;

BaseController::BaseController(Creature* owner) : _owner(owner)
{

	// state = State::Idle;
	if (owner)
		owner->schedule([this](float dt) { this->Update(Director::getInstance()->getDeltaTime()); }, "ControllerUpdate");
}

BaseController::~BaseController()
{
	if (_owner)
	{
		_owner->unschedule("ControllerUpdate");
		_owner = nullptr;
	}
}

Creature* BaseController::GetOwner()
{
	return _owner;
}

State BaseController::GetStat()
{
	return state;
}

void BaseController::Update(float deltaTime)
{
	// float frameRate = cocos2d::Director::getInstance()->getFrameRate();
	log("%f", Director::getInstance()->getDeltaTime());
}
