#pragma once
#include "memory"
#include "DelegateAction.h"
class Creature;

class Stat
{
public:
	Stat(Creature* owner);
	virtual ~Stat();

	virtual bool LoadStatData(int id) = 0;

	Creature* GetOwner();

	int GetLevel();
	float GetCurHp();
	
	float GetMaxHp();
	float GetExtraMaxHp();
	float GetTotalMaxHp();

	float GetAtk();
	float GetExtraAtk();
	float GetTotalExtraAtk();

	float GetSpecialAtk();
	float GetExtraSpecialAtk();
	float GetTotalSpecialAtk();

	float GetDefense();
	float GetExtraDefense();
	float GetTotalDefense();

	float GetMoveSpeed();
	float GetExtraMoveSpeed();
	float GetTotalMoveSpeed();

	virtual void SetLevel(int val);
	void SetCurHp(float val);

	void SetMaxHp(float val);
	void SetExtraMaxHp(float val);

	void SetAtk(float val);
	void SetExtraAtk(float val);

	void SetSpecialAtk(float val);
	void SetExtraSpecialAtk(float val);

	void SetDefense(float val);
	void SetExtraDefense(float val);

	void SetMoveSpeed(float val);
	void SetExtraMoveSpeed(float val);

	virtual void Clear();
public:
	DelegateAction<int> levelDelegate;
	DelegateAction<float, float> curHpDelegate;
	DelegateAction<float, float> maxHpDelegate;

protected:
	int level;
	float curHp;
	float maxHp;
	float extraMaxHp;
	float atk;
	float extraAtk;
	float specialAtk;
	float extraSpecialAtk;
	float defense;
	float extraDefense;
	float moveSpeed;
	float extraMoveSpeed;


	Creature* _owner;
};