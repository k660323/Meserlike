#pragma once
#include "MonsterController.h"

class NormalMonster;

class NormalMonsterController : public MonsterController
{
	using Super = MonsterController;

public:
	NormalMonsterController(Creature* owner);
	virtual ~NormalMonsterController();

	NormalMonster* GetNormalMonsterOwner();

	virtual void SetState(State s) override;
	virtual void Update(float deltaTime) override;

protected:
	void UpdateIdle();
	void UpdateMove();
};