#include "Bullet.h"
#include "IHitable.h"
#include "Bitmask.h"
#include "SkillBase.h"
#include "Creature.h"
#include "Stat.h"
#include "Player.h"
USING_NS_CC;

Bullet::Bullet(Creature* parent, SkillBase* skillBase,float scale, std::string path)
	: Super(parent, skillBase, scale, path)
{
	lifeTime = 1.0f;
}

Bullet::~Bullet()
{
}

bool Bullet::init()
{
	if (!Super::init())
		return false;

	moveSpeed = skillStatData.speed;
	totalDamage = skillStatData.specialAtk + _owner->GetStat()->GetTotalSpecialAtk();
	
	bulletSprite->setScale(bulletScale);

	this->addChild(bulletSprite);

	{
		auto material = PhysicsMaterial(0.0f, 0.0f, 0.0f);
		auto body = PhysicsBody::createBox(bulletSprite->getContentSize() * 0.5f, material);

		// 강체의 질량 설정
		body->setMass(0.0f);
		// 동적 또는 정적 상태를 설정한다
		body->setDynamic(false);
		// setCategoryBitmask(int) : 충돌을 위한 카테고리를 설정한다. 
		body->setCategoryBitmask(Bitmask::SkillObj);

		// 물리 처리할 비트마스크
		body->setCollisionBitmask(Bitmask::Ignore);

		// setContactTestBitmask(int) : 어떤 카테고리와 충돌 트리거 처리
		body->setContactTestBitmask(Bitmask::All_InvEx ^ _owner->getPhysicsBody()->getCategoryBitmask());
		
		body->setEnabled(true);

		// 스프라이트에 강체 설정
		this->setPhysicsBody(body);
	}

	return true;
}

bool Bullet::onContactEnter(cocos2d::PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA != this && nodeB != this)
		return false;

	auto other = (nodeA == this) ? nodeB : nodeA;

	if (other == _owner)
		return false;

	auto hitable = dynamic_cast<IHitable*>(other);
	if (hitable)
	{
		float atk = totalDamage;
		hitable->OnAttacked(atk);

		this->removeFromParent();
	}
	else
	{
		return false;
	}

	return true;
}

void Bullet::onContactExit(cocos2d::PhysicsContact& contact)
{
}
