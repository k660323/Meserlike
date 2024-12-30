#pragma once
#include "cocos2d.h"
#include "Define.h"
#include "DelegateAction.h"
#include "Data.h"

class Creature;
class Monster;
class Player;
class SkillBase;

class GameManager
{
public:
	GameManager();
	virtual ~GameManager();

	Monster* SpawnMonster(MonsterType type);
	Player* SpawnPlayer(int level);

	void DeSpawnCreature(Creature* creature);

	Player* GetPlayer();

	void Clear();

	int GetScore();
	void SetScore(int value);

	int GetRound();
	void SetRound(int value);

	DelegateAction<int> roundDelegate;

	std::vector<std::pair<int, SkillId>> GetRandomSkillId(int size = 3);
	void SelectSkill(int index, SkillId skillId, SkillInfo skillInfo, SkillBase* skillBase);
private:
	bool isGetFirstSkillId;

	std::vector<int> firstSkillVec;
	std::vector<std::pair<SkillId, int>> playerUseAbleSkill;
	std::set<Creature*> creatureSet;
	Player* player;

	int score;
	int round;
};