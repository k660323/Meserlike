#pragma once
#include "Creature.h"
#include "Interface/IHitable.h"

class PlayerStat;
class PlayerController;

class Player : public Creature, public IHitable
{
	using Super = Creature;
public:
	Player(int level);
	virtual ~Player();

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;

	PlayerStat* GetPlayerStat();
	PlayerController* GetPlayerController();

	virtual void OnAttacked(float damage) override;
	virtual void OnAttacked(cocos2d::Node* other, float damage) override;
	
	virtual void update(float deltaTime) override;

	void Dash();

	CREATE_FUNC_Player(Player);

	void SetCurDashCoolTime(float val);
	float GetCurDashCoolTime();

	void SetDashCoolTime(float val);
	float GetDashCoolTime();

	void CreateLevelUpEffect();

	DelegateAction<float> dashStartDelegate;
	DelegateAction<float, float> curDashDelegate;
	DelegateAction<float, float> dashDelegate;
protected:
	float dashDuration;
	float curDashCooltime;
	float dashCooltime;
	bool isDash;


};