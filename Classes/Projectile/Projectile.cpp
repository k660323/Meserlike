#include "Projectile.h"
#include "SkillBase.h"
USING_NS_CC;

Projectile::Projectile(Creature* parent, SkillBase* skillBase,float scale, std::string path) : _owner(parent), _skillBase(skillBase)
{
    bulletSprite = Sprite::create(path);
    skillStatData = skillBase->GetSkillStatData();
    totalDamage = 0;
    bulletScale = scale;
}

Projectile::~Projectile()
{
    _owner = nullptr;
}

bool Projectile::init()
{
	if (!Super::init())
		return false;

    contact = EventListenerPhysicsContact::create();

    // 충돌 이벤트 함수
    contact->onContactBegin = CC_CALLBACK_1(Projectile::onContactEnter, this);
    contact->onContactSeparate = CC_CALLBACK_1(Projectile::onContactExit, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(contact, this);


	return true;
}

void Projectile::Fire(Vec2 dir)
{
	_dir = dir;

    auto action = Sequence::create(
        CallFunc::create([this](){
            cocos2d::Vec2 nextPos = getPosition() + moveSpeed * _dir * Director::getInstance()->getDeltaTime();
            setPosition(nextPos);
            }),
        nullptr
    );

    fireAction = RepeatForever::create(action);
    this->runAction(fireAction);

    lifeTimeAction = Sequence::create(DelayTime::create(lifeTime),
        CallFunc::create([this]() { this->removeFromParent(); }),
        nullptr);

    this->runAction(lifeTimeAction);
}

void Projectile::SetLifeTime(float lt)
{
    lifeTime = lt;
}

Creature* Projectile::GetOwner()
{
    return _owner;
}

bool Projectile::onContactEnter(cocos2d::PhysicsContact& contact)
{
    return false;
}

void Projectile::onContactExit(cocos2d::PhysicsContact& contact)
{
}
