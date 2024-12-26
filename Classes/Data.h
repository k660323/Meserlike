#pragma once
#include "vector"
#include "map"
#include "string"

struct StatData
{
	int id = 0;
	int level = 0;
	float maxHp = 0;
	float atk = 0;
	float specialAtk = 0;
	float defense = 0;
	float moveSpeed = 0;
};

struct PlayerStatData : StatData
{
	int maxExp = 0;
	int maxStemina = 0;
};

struct MonsterStatData : StatData
{
	int score = 0;
	int dropExp = 0;
};

struct SpawnWaveArrayData
{
	int monsterId = 0;
	int spawnCount = 0;
};

struct SpawnArrayData
{
	float spawnWaveInterval = 0;
	std::vector<SpawnWaveArrayData> spawnWaveData;

};

struct RoundSpawnData
{
	int roundId = 0;
	float spawnInvertal = 0;
	SpawnArrayData spawnData;
};

struct DefaultSpriteData
{
	std::string path = "";
	float sizeY = 0;
	float sizeX = 0;
	int rowMinY = 0;
	int rowMaxY = 0;
	int colMinX = 0;
	int colMaxX = 0;
	float animSpeed = 0;
};

struct AnimationData : DefaultSpriteData
{
	std::string state = "";
	bool isLoop = false;
};

struct SpriteData
{
	std::string spriteId = "";
	std::string uiImagePath = "";
	DefaultSpriteData dspriteData;
	std::map<std::string, AnimationData> animData;
};

struct CreatureInfoData
{
	int id = 0;
	std::string spriteId = "";
	std::string soundId = "";
	std::vector<int> skillIds;
};

struct MonsterInfoData : CreatureInfoData
{
	bool isBoss = false;
};

struct SkillStatData
{
	// 장비 스텟
	int level = 0;
	float cooltime = 0;
	float atk = 0;
	float specialAtk = 0;
	float speed = 0;
	float value = 0;
	std::string command = "";

	// 플레이어 능력치
	float extraMaxHp = 0;
	float extraAtk = 0;
	float extraSpecialAtk = 0;
	float extraDefense = 0;
	float extraMoveSpeed = 0;
};

struct SkillInfo
{
	int skillId = -1;
	std::string skillName = "";
	std::string skillSpritePath = "";
	std::map<int, SkillStatData> skillDatas;
};

struct CreatureSoundInfo
{
	std::string id = "";
	std::string Damaged = "";
	std::string Die = "";
};