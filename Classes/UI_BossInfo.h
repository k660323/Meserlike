#pragma once
#include "UI_Base.h"
#include "Define.h"

class BossMonster;

class UI_BossInfo : public UI_Base
{
	using Super = UI_Base;

public:
	UI_BossInfo();
	virtual ~UI_BossInfo();

	virtual bool init() override;

	void SetInit(BossMonster* bossMonster);

	CREATE_FUNC(UI_BossInfo);

private:
	cocos2d::Sprite* bossImage;
	cocos2d::Sprite* bossHpBarBackground;
	cocos2d::ui::LoadingBar* bossHpBar;
	cocos2d::Label* bossHpText;
	cocos2d::Label* bossNameText;

	BossMonster* _owner;
};