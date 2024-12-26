#pragma once
#include "BaseController.h"

class Player;

class PlayerController : public BaseController
{
	using Super = BaseController;
public:
	PlayerController(Creature* owner);
	virtual ~PlayerController();

	Player* GetPlayerOwner();

	virtual void SetState(State s) override;

	virtual void Update(float deltaTime) override;

protected:
	void UpdateIdle();
	void UpdateMove();
};