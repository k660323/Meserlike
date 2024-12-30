#pragma once
#include "Projectile.h"
#include "cocos2d.h"

class Bullet : public Projectile
{
	using Super = Projectile;
public:
	Bullet(Creature* parent, SkillBase* skillbase,float scale, std::string path);
	virtual ~Bullet();

	virtual bool init() override;

	CREATE_FUNC_PROJECTILE(Bullet);

protected:
	virtual bool onContactEnter(cocos2d::PhysicsContact& contact) override;
	virtual void onContactExit(cocos2d::PhysicsContact& contact) override;

protected:
};