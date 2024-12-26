#include "WorldItem.h"

USING_NS_CC;

WorldItem::WorldItem()
{
}

WorldItem::~WorldItem()
{
}

bool WorldItem::init()
{
    if (!Super::init())
        return false;

    // 충돌 이벤트 리스너
    contact = EventListenerPhysicsContact::create();

    // 충돌 이벤트 함수
    contact->onContactBegin = CC_CALLBACK_1(WorldItem::onContactEnter, this);
    contact->onContactSeparate = CC_CALLBACK_1(WorldItem::onContactExit, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(contact, this);


    return true;
}

void WorldItem::onEnter()
{
    Super::onEnter();
}

void WorldItem::onExit()
{
    _eventDispatcher->removeEventListener(contact);
    Super::onExit();
}

bool WorldItem::onContactEnter(cocos2d::PhysicsContact& contact)
{
    return false;
}

void WorldItem::onContactExit(cocos2d::PhysicsContact& contact)
{
}
