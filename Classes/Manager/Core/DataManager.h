#pragma once
#include "Data/Data.h"
#include "map"
#include "set"
#include "string"
#include "json/document.h"
#include "Define.h"

namespace cocos2d
{
	class Sprite;
}

class DataManager
{
public:
	DataManager();
	virtual ~DataManager();

	PlayerStatData& GetPlayerStatData(int index);
	MonsterStatData& GetMonsterStatData(int index);
	RoundSpawnData& GetRoundSpawnData(int index);
	int GetMaxRound();
	SpriteData& GetSpriteData(std::string name);
	MonsterInfoData& GetMonsterInfoData(MonsterType monsterType);
	CreatureInfoData& GetPlayerInfoData();
	SkillInfo& GetSkillInfoData(SkillId id);
	std::set<SkillId> GetFirstSkillSet();
	CreatureSoundInfo& GetCreatureSoundInfoData(std::string id);
	
	std::map<SkillId, int> GetPlayerUseAbleSkillData();
private:
	rapidjson::Document LoadData(std::string path);
	void LoadPlayerStatData();
	void LoadMonsterStatData();
	void LoadRoundSpawnData();
	void LoadSpriteData();
	void LoadMonsterData();
	void LoadPlayerData();

	void LoadRepeatSkillData();
	void LoadBuffSkillData();
	void LoadSequenceSkillData();
	void LoadPortionData();
	void LoadPlayerUsealbeSkillData();

	void LoadCreatureSoundData();

	void LoadFirstSkillSetData();
private:
	std::map<int, PlayerStatData> playerStatDatas;
	std::map<int, MonsterStatData> monsterStatDatas;
	std::map<int, RoundSpawnData> roundSpawnDatas;
	std::map<std::string, SpriteData> spriteDatas;
	
	std::map<int, MonsterInfoData> monsterDatas;
	std::map<int, CreatureInfoData> playerDatas;
	
	// 처음 사용할 스킬 목록
	std::set<SkillId> firstSkillSet;

	std::map<int, SkillInfo> skillDatas;
	std::map<SkillId, int> playerUseAbleSkill;

	std::map<std::string, CreatureSoundInfo> soundDatas;

};