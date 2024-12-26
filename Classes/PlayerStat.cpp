#include "PlayerStat.h"
#include "Managers.h"
#include "DataManager.h"
#include "Creature.h"
#include "SoundManager.h"
#include "Player.h"
#include "UIManager.h"
USING_NS_CC;

PlayerStat::PlayerStat(Creature* owner) : Super(owner)
{
	curStemina = 0;
	maxStemina = 0;
	exp = 0;
	maxExp = 0;
}

PlayerStat::PlayerStat(Creature* owner, int id) : Super(owner)
{
	LoadStatData(id);
}

PlayerStat::~PlayerStat()
{
}

bool PlayerStat::LoadStatData(int id)
{
	// 데이터 매니저에서 해당 Json 데이터 가져오기
	PlayerStatData pStatData = Managers::Data()->GetPlayerStatData(id);

	if (pStatData.level > 0)
	{
		SetLevel(pStatData.level);
		SetMaxHp(pStatData.maxHp);
		if (level <= 1)
			SetCurHp(pStatData.maxHp);
		atk = pStatData.atk;
		specialAtk = pStatData.specialAtk;
		defense = pStatData.defense;
		moveSpeed = pStatData.moveSpeed;
		SetMaxExp(pStatData.maxExp);
		exp = 0;
		return true;
	}
	else
	{
		SetLevel(level);
	}

	return false;
}

void PlayerStat::SetLevel(int val)
{
	Super::SetLevel(val);
	Managers::Sound()->PlaySound2D("Sound/LevelUp.mp3");
	Player* player = dynamic_cast<Player*>(_owner);
	player->CreateLevelUpEffect();
	
	auto action = Sequence::create(DelayTime::create(2.0f),
		CallFunc::create([this]() {
			Managers::UI()->ShowPopupUI(PopupType::UI_SkillSelect);
			}),
			nullptr);

	_owner->runAction(action);
	
}

float PlayerStat::GetCurStemina()
{
	return curStemina;
}

float PlayerStat::GetMaxStemina()
{
	return maxStemina;
}

void PlayerStat::SetCurStemina(float val)
{
	curStemina = val;
}

void PlayerStat::SetMaxStemina(float val)
{
	maxStemina = val;
}

int PlayerStat::GetExp()
{
	return exp;
}

int PlayerStat::GetMaxExp()
{
	return maxExp;
}

void PlayerStat::SetExp(int val)
{
	exp = val;

	if (exp >= maxExp)
	{
		int gap = exp - maxExp;
		while(gap >= 0)
		{
			bool result = LoadStatData(level + 1);

			if (result == false)
			{
				gap = 0;
				break;
			}
			
			gap -= maxExp;
		};

		exp = std::max(0, gap);
	}

	expDelegate.invoke(exp, maxExp);
}

void PlayerStat::SetMaxExp(int val)
{
	maxExp = val;
	expDelegate.invoke(exp, maxExp);
}

void PlayerStat::Clear()
{
	Super::Clear();
	expDelegate.removeAllCallback();
}
