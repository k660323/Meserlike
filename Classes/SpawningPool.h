#pragma once
#include "Data.h"
#include "cocos2d.h"

class SpawningPool
{
public:
	SpawningPool();
	virtual ~SpawningPool();

	void TrySpawn(int round);

	cocos2d::Action* spawnAction;

	void FindSpawnData();
	void WaveSpawnMonster();
	void SpawnMonster();
	void CheckNextRoundSpawn();
protected:
	int maxRepeatIndex;
	int waveIndex;
	int maxWaveIndex;

	float spawnInterval;
	float spawnWaveInterval;
	SpawnArrayData spawnArrData;
	std::vector<SpawnWaveArrayData> spawnWaveDatas;

	std::vector<cocos2d::Vec2> spawnVec;
	int monsterId;

	int maxSpawnCnt;
	int curSpawnCnt;

	int _callbackCnt;
	// 해당 라운드에 소환된 몹 수
	int _maxSpawnCount;
	// 몹 생성중인지
	bool _isSpawn;

private:
	// 스폰 데이터 (만들 예정)
	// 각 라운드마다 소환할 목록 배열
	// 라운드 배열
	// [0]
	//		- 스폰 주기
	//		- 스폰 배열
	//			[0]
	//			- 스폰할 몬스터 ID
	//			- 스폰할 카운터
	//			[1]
	//			- 스폰할 몬스터 ID
	//			- 스폰할 카운터
	// [1]
	//		- 스폰 주기
	//		- 스폰 배열
	//			[0]
	//			- 스폰할 몬스터 ID
	//			- 스폰할 카운터
	//			[1]
	//			- 스폰할 몬스터 ID
	//			- 스폰할 카운터




};