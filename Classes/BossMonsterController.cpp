#include "BossMonsterController.h"
#include "BossMonster.h"
#include "Creature.h"
#include "AnimateEx.h"

BossMonsterController::BossMonsterController(Creature* owner) : Super(owner)
{
    SetState(State::Idle);

}

BossMonsterController::~BossMonsterController()
{
}

BossMonster* BossMonsterController::GetBossMonsterOwner()
{
    return dynamic_cast<BossMonster*>(_owner);
}

void BossMonsterController::SetState(State s)
{
	// 이전 상태 (exit)
	switch (s)
	{
	case State::None:
		break;
	case State::Idle:
		break;
	case State::Move:
		break;
	case State::Dead:
		break;
	default:
		break;
	}



	// 다음 상태 (enter)
	switch (s)
	{
	case State::None:
		break;
	case State::Idle:
		_owner->GetAnimateEx()->PlayAnimation("Idle");
		break;
	case State::Move:
		_owner->GetAnimateEx()->PlayAnimation("Move");
		break;
	case State::Dead:
		_owner->GetAnimateEx()->PlayAnimation("Dead");
		_owner->stopAllActions();
		break;
	default:
		break;
	}

	state = s;
}

void BossMonsterController::Update(float deltaTime)
{
	switch (state)
	{
	case State::None:
		break;
	case State::Idle:
		
		break;
	case State::Move:
		
		break;
	case State::Dead:
		break;
	default:
		break;
	}
}
