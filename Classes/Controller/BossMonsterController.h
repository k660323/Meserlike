#pragma once
#include "MonsterController.h"

class BossMonster;

class BossMonsterController : public MonsterController
{
	using Super = MonsterController;

public:
	BossMonsterController(Creature* owner);
	virtual ~BossMonsterController();

	BossMonster* GetBossMonsterOwner();

	virtual void SetState(State s) override;
	virtual void Update(float deltaTime) override;

protected:

};
