#pragma once
#include "UI_Base.h"
#include "UI_BossInfo.h"
#include "set"

class UI_BossInfo;
class BossMonster;

class UI_Scene : public UI_Base
{
	using Super = UI_Base;
public:
	UI_Scene();
	virtual ~UI_Scene();

	virtual bool init() override;

	CREATE_FUNC(UI_Scene);

	void ActiveBossInfo(BossMonster* bossMonster);
protected:
	std::set<UI_BossInfo*> bossInfos;
};