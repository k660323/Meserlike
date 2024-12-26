#include "SpawningPool.h"
#include "Managers.h"
#include "DataManager.h"
#include "Data.h"
#include "GameManager.h"
#include "Monster.h"
#include "MapManager.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "HpPortionItem.h"

USING_NS_CC;

SpawningPool::SpawningPool()
{
    _isSpawn = false;
    curSpawnCnt = 0;
    waveIndex = 0;
    spawnInterval = 0;
    spawnWaveInterval = 0;
    _callbackCnt = 0;
    _maxSpawnCount = 0;
}

SpawningPool::~SpawningPool()
{
	// delete spawnAction;
	spawnAction = nullptr;
}

void SpawningPool::TrySpawn(int round)
{
	if (_isSpawn)
		return;
    if (round >= Managers::Data()->GetMaxRound())
    {
        // 게임 종료
        GameScene* gs = dynamic_cast<GameScene*>(Managers::Scene()->GetCurrentScene());
        if (gs)
            gs->GameEnd();
        return;
    }

    // 해당 라운드에 스폰할 몹 데이터
    auto roundData = Managers::Data()->GetRoundSpawnData(round);

    log("round ID : %d", roundData.roundId);

    // 스폰 후 다음 스폰 시간
    spawnInterval = roundData.spawnInvertal;

    // 해당 라운드에 스폰할 스폰 리스트
    spawnArrData = roundData.spawnData;

    // 인덱스 초기화
    curSpawnCnt = 0;
    waveIndex = 0;
    _callbackCnt = 0;
    _maxSpawnCount = 0;

    // 총 스폰할 몹수
    int size = spawnArrData.spawnWaveData.size();
    for (int i = 0; i < size; i++)
    {
        _maxSpawnCount += spawnArrData.spawnWaveData[i].spawnCount;
    }

    // 해당 라운드 스폰할 리스트 실행
    auto spawnSequence = Sequence::create(
        DelayTime::create(3.0f),
        CallFunc::create(CC_CALLBACK_0(SpawningPool::FindSpawnData, this)),
        nullptr
    );

    // 실행
    Managers::Scene()->GetCurrentScene()->runAction(spawnSequence);

    // 스폰
    _isSpawn = true;

    /*
    for (auto data : spawnArrData)
    {
        auto spawnWaveDatas = data.spawnWaveData;

        // 스폰 웨이브 갯수
        int spawnCnt = spawnWaveDatas.size();

        

        auto spawnAction = Sequence::create(
            DelayTime::create(interval), // 생성 주기
            CallFunc::create([this]()
                {
                    for (int i = 0; i < spawnDatas.size(); i++)
                    {
                        int cnt = spawnDatas[i].spawnCount;

                        // MobSpawnPos0 ~ 7
                        // BossSpawnPos
                        std::string spawnStr = "MobSpawnPos" + std::to_string(random(0, 8));
                        Vec2 spawnPos = Managers::Map()->GetObjectPos(spawnStr);

                        for (int j = 0; j < cnt; j++)
                        {
                            auto monster = Managers::Game()->SpawnMonster(static_cast<MonsterType>(spawnDatas[i].monsterId));
                            monster->setPosition(spawnPos);
                            Managers::Scene()->GetCurrentScene()->AddObjectLayer(monster);
                        }
                    }
                }), 
            nullptr);


       

        auto repeatSpawnAction = Repeat::create(spawnAction, spawnCnt);
    }
    */
}

void SpawningPool::FindSpawnData()
{
    // 스폰 웨이브 갯수
    int waveSize = spawnArrData.spawnWaveData.size();

    spawnWaveInterval = spawnArrData.spawnWaveInterval;

    spawnWaveDatas = spawnArrData.spawnWaveData;

    waveIndex = 0;
    maxWaveIndex = spawnWaveDatas.size();

    // 웨이브에 있는 몬스터 모두 소환
    auto waveSequence = Sequence::create(
        CallFunc::create(CC_CALLBACK_0(SpawningPool::WaveSpawnMonster, this)),
        nullptr
    );

    // 실행
    Managers::Scene()->GetCurrentScene()->runAction(waveSequence);
}

void SpawningPool::WaveSpawnMonster()
{
    monsterId = spawnWaveDatas[waveIndex].monsterId;
    maxSpawnCnt = spawnWaveDatas[waveIndex].spawnCount;

    log("wave %d", waveIndex);

    curSpawnCnt = 0;
    // MobSpawnPos0 ~ 7
    // BossSpawnPos

    int spawnIndex = random(0, 8);
    int leftSpawnIndex = ((spawnIndex == 0) ? 7 : spawnIndex -1) ;
    int rightSpawnIndex = (spawnIndex + 1) % 8;

    spawnVec.clear();
    std::string spawnStr = ("MobSpawnPos" + std::to_string(spawnIndex));
    spawnVec.push_back(Managers::Map()->GetObjectPos(spawnStr));
    spawnStr = ("MobSpawnPos" + std::to_string(leftSpawnIndex));
    spawnVec.push_back(Managers::Map()->GetObjectPos(spawnStr));
    spawnStr = ("MobSpawnPos" + std::to_string(rightSpawnIndex));
    spawnVec.push_back(Managers::Map()->GetObjectPos(spawnStr));


    // 해당 웨이브의 해당 몬스터 딜레이 반복 소환
    {
        auto spawnSequence = Sequence::create(
            DelayTime::create(spawnInterval),
            CallFunc::create(CC_CALLBACK_0(SpawningPool::SpawnMonster, this)),
            nullptr
        );

        // TODO 반복 소환
        auto spawnRepeat = Repeat::create(spawnSequence, maxSpawnCnt);
        // 실행
        Managers::Scene()->GetCurrentScene()->runAction(spawnRepeat);
        log("Repeat Spawn : %d", maxSpawnCnt);
    }

    waveIndex++;
}

void SpawningPool::SpawnMonster()
{
    auto monster = Managers::Game()->SpawnMonster(static_cast<MonsterType>(monsterId));
    monster->deadAction.addCallback(CC_CALLBACK_0(SpawningPool::CheckNextRoundSpawn, this));
    monster->setPosition(spawnVec[random(0, (int)spawnVec.size() - 1)]);
    Managers::Scene()->GetCurrentScene()->AddObjectLayer(monster);

    curSpawnCnt++;

    if (curSpawnCnt == maxSpawnCnt)
    {
        if (waveIndex == maxWaveIndex)
        {
            _isSpawn = false;
        }
        else
        {
            // 웨이브에 있는 몬스터 모두 소환
            auto waveSequence = Sequence::create(
                DelayTime::create(spawnWaveInterval),
                CallFunc::create(CC_CALLBACK_0(SpawningPool::WaveSpawnMonster, this)),
                nullptr
            );

            // 실행
            Managers::Scene()->GetCurrentScene()->runAction(waveSequence);
        }
    }
}

void SpawningPool::CheckNextRoundSpawn()
{
    _callbackCnt++;

    if (_callbackCnt == _maxSpawnCount)
    {
        GameScene* gameScene = dynamic_cast<GameScene*>(Managers::Scene()->GetCurrentScene());
        if (gameScene)
            gameScene->SpawnHpPortion();

        auto nextSpawnSequence = Sequence::create(
            DelayTime::create(3.0f),
            CallFunc::create([this]() { 
                int curRound = Managers::Game()->GetRound();
                Managers::Game()->SetRound(curRound + 1);
                TrySpawn(Managers::Game()->GetRound());
            }),
            nullptr
        );
       
        // 실행
        Managers::Scene()->GetCurrentScene()->runAction(nextSpawnSequence);
    }
}
