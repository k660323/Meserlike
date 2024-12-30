#pragma once
#include "Define.h"

class Creature;

class BaseController
{
public:
	BaseController(Creature* owner);
	virtual ~BaseController();

	Creature* GetOwner();

	virtual void SetState(State s) = 0;
	virtual State GetStat();

	virtual void Update(float deltaTime);

protected:
	Creature* _owner;
	State state;
};