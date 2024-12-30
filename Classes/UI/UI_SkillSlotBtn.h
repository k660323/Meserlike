#pragma once
#include "UI_Base.h"
#include "Define.h"
#include "Data.h"

class SkillBase;

class UI_SkillSlotBtn : public UI_Base
{
	using Super = UI_Base;

public:
	UI_SkillSlotBtn();
	virtual ~UI_SkillSlotBtn();

	virtual bool init() override;

	void SetSkillData(int index, SkillId skillId);
	void RegisterOrUpgradeSkill();

	CREATE_FUNC(UI_SkillSlotBtn);

private:
	int _index;

	SkillId _skillId;

	SkillInfo _skillInfo;

	SkillBase* _skillBase;

	// 버튼
	cocos2d::ui::Button* backGroundButton;
	
	// 스킬 이미지
	cocos2d::Sprite* skillImage;

	// 스킬 이름
	cocos2d::Label* skillName;

	// 스킬 레벨
	cocos2d::Label* skillLevel;

	// 스킬 설명
	cocos2d::Label* skillCommand;
};