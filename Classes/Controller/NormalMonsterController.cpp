#include "NormalMonsterController.h"
#include "NormalMonster.h"
#include "Creature.h"
#include "AnimateEx.h"
#include "Managers.h"
#include "GameManager.h"
#include "Player.h"
#include "Utils.h"
#include "MonsterStat.h"
USING_NS_CC;

NormalMonsterController::NormalMonsterController(Creature* owner) : Super(owner)
{
	SetState(State::Idle);

}

NormalMonsterController::~NormalMonsterController()
{
}

NormalMonster* NormalMonsterController::GetNormalMonsterOwner()
{
	return dynamic_cast<NormalMonster*>(_owner);
}

void NormalMonsterController::SetState(State s)
{
	if (_owner == false)
		return;

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
		break;
	default:
		break;
	}

	state = s;
}

void NormalMonsterController::Update(float deltaTime)
{
	switch (state)
	{
	case State::None:
		break;
	case State::Idle:
		UpdateIdle();
		break;
	case State::Move:
		UpdateMove();
		break;
	case State::Dead:
		break;
	default:
		break;
	}
}

void NormalMonsterController::UpdateIdle()
{
	auto target = Managers::Game()->GetPlayer();
	if (target != nullptr)
	{
		SetState(State::Move);
		return;
	}

}

void NormalMonsterController::UpdateMove()
{
	auto target = Managers::Game()->GetPlayer();
	if (target == nullptr)
	{
		SetState(State::Idle);
		return;
	}
	else if (target->GetBaseController()->GetStat() == State::Dead)
	{
		SetState(State::Idle);
		return;
	}

	Vec2 dir = (target->getPosition() - _owner->getPosition()).getNormalized();
	_owner->SetDir(Utils::XDir(dir.x));
	float moveSpeed = GetMonsterOwner()->GetMonsterStat()->GetTotalMoveSpeed();
	Vec2 nextPos = _owner->getPosition() + dir * moveSpeed * Director::getInstance()->getDeltaTime();
	_owner->setPosition(nextPos);
}