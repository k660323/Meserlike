#include "Creature.h"
#include "Contents/Stat/Stat.h"
#include "Contents/Controllers/BaseController.h"
#include "Contents/Skills/SkillBook.h"
#include "Contents/Ex/AnimateEx.h"
USING_NS_CC;

Creature::Creature()
{
    dir = Dir::Left;
    animateEx = std::make_shared<AnimateEx>();
    skillBook = std::make_shared<SkillBook>(this);
    invincibilityAction = nullptr;
}

Creature::~Creature()
{
    // deadAction.removeAllCallback();
    // stat->Clear();
}

bool Creature::init()
{
    if (!Super::init())
        return false;

    this->setAnchorPoint(Vec2(0.5f, 0.0f));

    return true;
}

void Creature::onEnter()
{
    Super::onEnter();

}

void Creature::onExit()
{
    _eventDispatcher->removeEventListener(contact);
    skillBook->StopSkills();
    Super::onExit();
}

bool Creature::onContactEnter(PhysicsContact& contact)
{
    return false;
}

void Creature::onContactExit(PhysicsContact& contact)
{

}

Dir Creature::GetDir()
{
    return dir;
}

void Creature::SetDir(Dir dir)
{
    this->dir = dir;
    cSprite->setFlippedX((dir == Dir::Left ? false : true));
}

void Creature::FlipDir()
{
    SetDir((GetDir() == Dir::Left ? Dir::Right : Dir::Left));
}

AnimateEx* Creature::GetAnimateEx()
{
    return animateEx.get();
}

Stat* Creature::GetStat()
{
    return stat.get();
}

BaseController* Creature::GetBaseController()
{
    return controller.get();
}

SkillBook* Creature::GetSkillBook()
{
    return skillBook.get();
}

void Creature::StopHitAction()
{
    if (invincibilityAction)
    {
        this->stopAction(invincibilityAction);
        invincibilityAction = nullptr;
    }
}
