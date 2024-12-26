#pragma once
#include "Stat.h"

class PlayerStat : public Stat
{
	using Super = Stat;
public:
	PlayerStat(Creature* owner);
	PlayerStat(Creature* owner, int id);
	virtual ~PlayerStat();

	virtual bool LoadStatData(int id) override;


	virtual void SetLevel(int val) override;

	float GetCurStemina();
	float GetMaxStemina();

	void SetCurStemina(float val);
	void SetMaxStemina(float val);

	int GetExp();
	int GetMaxExp();

	void SetExp(int val);
	void SetMaxExp(int val);

	virtual void Clear() override;

public:
	DelegateAction<int, int> expDelegate;

protected:
	float curStemina;
	float maxStemina;

	int exp;
	int maxExp;
};