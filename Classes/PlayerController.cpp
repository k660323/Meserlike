#include "PlayerController.h"
#include "Managers.h"
#include "InputManager.h"
#include "Player.h"
#include "PlayerStat.h"
#include "AnimateEx.h"
#include "Utils.h"
#include "SceneManager.h"
#include "SceneEx.h"

USING_NS_CC;

PlayerController::PlayerController(Creature* owner) : Super(owner)
{
	SetState(State::Idle);
}

PlayerController::~PlayerController()
{
}

Player* PlayerController::GetPlayerOwner()
{
	return dynamic_cast<Player*>(_owner);
}

void PlayerController::SetState(State s)
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

void PlayerController::Update(float deltaTime)
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

void PlayerController::UpdateIdle()
{
	if (Managers::Input()->GetMoveInput() != Vec2::ZERO)
	{
		SetState(State::Move);
		return;
	}
}

void PlayerController::UpdateMove()
{
	if (Managers::Input()->GetMoveInput() == Vec2::ZERO)
	{
		SetState(State::Idle);
		return;
	}

	Vec2 dir = Managers::Input()->GetMoveInput().getNormalized();
	_owner->SetDir(Utils::XDir(dir.x));
	float moveSpeed = GetPlayerOwner()->GetPlayerStat()->GetTotalMoveSpeed();
	Vec2 nextPos = _owner->getPosition() + dir * moveSpeed * Director::getInstance()->getDeltaTime();
	_owner->setPosition(nextPos);

	// Managers::Scene()->GetCurrentScene()->CameraPosUpdate();
	// Camera::getDefaultCamera()->setPosition(_owner->getPosition());

}
