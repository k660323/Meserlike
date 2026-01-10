#include "Melee.h"
#include "Contents/Creature/Creature.h"
#include "Contents/Skills/SkillBase.h"
USING_NS_CC;


Melee::Melee(Creature* parent, SkillBase* skillBase) : Super(parent, skillBase)
{
}

Melee::~Melee()
{
}

bool Melee::init()
{
    if (!Super::init())
        return false;

    // 충돌 이벤트 리스너
    contact = EventListenerPhysicsContact::create();

    // 충돌 이벤트 함수
    contact->onContactBegin = CC_CALLBACK_1(Melee::onContactEnter, this);
    contact->onContactSeparate = CC_CALLBACK_1(Melee::onContactExit, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(contact, this);

    return true;
}

bool Melee::onContactEnter(cocos2d::PhysicsContact& contact)
{
    return false;
}

void Melee::onContactExit(cocos2d::PhysicsContact& contact)
{
}
