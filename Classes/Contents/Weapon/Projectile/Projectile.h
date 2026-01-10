#pragma once
#include "cocos2d.h"
#include "Define.h"
#include "Data/Data.h"

class Creature;
class SkillBase;

class Projectile : public cocos2d::Node
{
	using Super = cocos2d::Node;
public:
	Projectile(Creature* parent, SkillBase* skillBase, float scale, std::string path);
	virtual ~Projectile();

	virtual bool init() override;

	virtual void Fire(cocos2d::Vec2 dir);
	virtual void SetLifeTime(float lt);

	Creature* GetOwner();

	CREATE_FUNC_PROJECTILE(Projectile);

protected:
	virtual bool onContactEnter(cocos2d::PhysicsContact& contact);
	virtual void onContactExit(cocos2d::PhysicsContact& contact);

protected:
	Creature* _owner;
	SkillBase* _skillBase;
	SkillStatData skillStatData;

	cocos2d::Vec2 _dir;
	float moveSpeed;
	float lifeTime;
	float totalDamage;

	cocos2d::Action* fireAction;
	cocos2d::Action* lifeTimeAction;

	float bulletScale;
	cocos2d::Sprite* bulletSprite;
protected:
	// 충돌 이벤트
	cocos2d::EventListenerPhysicsContact* contact;
};