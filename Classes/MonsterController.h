#pragma once
#include "BaseController.h"

class Monster;

class MonsterController : public BaseController
{
	using Super = BaseController;

public:
	MonsterController(Creature* owner);
	virtual ~MonsterController();

	Monster* GetMonsterOwner();

	void SetTarget(Creature* target);

	virtual void SetState(State s) = 0;
	virtual void Update(float deltaTime) = 0;

protected:
	Creature* _target;
};