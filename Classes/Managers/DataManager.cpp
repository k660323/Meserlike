#include "DataManager.h"
#include "cocos2d.h"

#include "json/rapidjson.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"

using namespace rapidjson;

USING_NS_CC;


DataManager::DataManager()
{
    LoadPlayerStatData();
    LoadMonsterStatData();
    LoadRoundSpawnData();
    LoadSpriteData();
    LoadMonsterData();
    LoadPlayerData();
    LoadRepeatSkillData();
    LoadBuffSkillData();
    LoadSequenceSkillData();
    LoadPortionData();
    LoadPlayerUsealbeSkillData();
    LoadCreatureSoundData();
    LoadFirstSkillSetData();
}

DataManager::~DataManager()
{
   
}

PlayerStatData& DataManager::GetPlayerStatData(int index)
{
    return playerStatDatas[index];
}

MonsterStatData& DataManager::GetMonsterStatData(int index)
{
    return monsterStatDatas[index];
}

RoundSpawnData& DataManager::GetRoundSpawnData(int index)
{
    return roundSpawnDatas[index];
}

int DataManager::GetMaxRound()
{
    return roundSpawnDatas.size();
}

SpriteData& DataManager::GetSpriteData(std::string name)
{
    return spriteDatas[name];
}

MonsterInfoData& DataManager::GetMonsterInfoData(MonsterType monsterType)
{
    return monsterDatas[(int)monsterType];
}

CreatureInfoData& DataManager::GetPlayerInfoData()
{
    return playerDatas[0];
}

SkillInfo& DataManager::GetSkillInfoData(SkillId id)
{
    return skillDatas[(int)id];
}

std::set<SkillId> DataManager::GetFirstSkillSet()
{
    return firstSkillSet;
}

CreatureSoundInfo& DataManager::GetCreatureSoundInfoData(std::string id)
{
    return soundDatas[id];
}

std::map<SkillId, int> DataManager::GetPlayerUseAbleSkillData()
{
    return playerUseAbleSkill;
}

Document DataManager::LoadData(std::string path)
{
    // JSON 파일 경로 탐색
    std::string jsonData = FileUtils::getInstance()->getStringFromFile(path);

    // JSON 파일을 관리할 Document 객체
    Document doc;

    // JSON 파일을 불러온 다음 doc에 저장한다
    doc.Parse<0>(jsonData.c_str());

    return doc;
}

void DataManager::LoadPlayerStatData()
{
    // JSON 파일을 관리할 Document 객체
    Document doc = LoadData("data/PlayerStatData.json");

    // 오류 검사
    if (doc.HasParseError())
    {
        // 오류가 존재하는 경우 콘솔로 출력하고 프로그램 종료
        log("GetParseError : %d", doc.GetParseError());
        return;
    }
    else
    {
        // 그룹 데이터
        const rapidjson::Value& arr = doc["playerStatArray"];

        if (arr.IsArray())
        {
            for (SizeType i = 0; i < arr.Size(); i++)
            {
                PlayerStatData data;
                data.id = arr[i]["id"].GetInt();
                data.level = arr[i]["level"].GetInt();
                data.maxHp = arr[i]["maxHp"].GetFloat();
                data.atk = arr[i]["atk"].GetFloat();
                data.specialAtk = arr[i]["specialAtk"].GetFloat();
                data.defense = arr[i]["defense"].GetFloat();
                data.moveSpeed = arr[i]["moveSpeed"].GetFloat();
                data.maxStemina = arr[i]["maxStemina"].GetFloat();
                data.maxExp = arr[i]["maxExp"].GetInt();
                playerStatDatas.insert({ data.id, data });
            }
        }
    }
}

void DataManager::LoadMonsterStatData()
{
    // JSON 파일을 관리할 Document 객체
    Document doc = LoadData("data/MonsterStatData.json");

    // 오류 검사
    if (doc.HasParseError())
    {
        // 오류가 존재하는 경우 콘솔로 출력하고 프로그램 종료
        log("GetParseError : %d", doc.GetParseError());
        return;
    }
    else
    {
        // 그룹 데이터
        const rapidjson::Value& arr = doc["monsterStatArray"];

        if (arr.IsArray())
        {
            for (SizeType i = 0; i < arr.Size(); i++)
            {
                MonsterStatData data;
                data.id = arr[i]["id"].GetInt();
                data.level = arr[i]["level"].GetInt();
                data.maxHp = arr[i]["maxHp"].GetFloat();
                data.atk = arr[i]["atk"].GetFloat();
                data.specialAtk = arr[i]["specialAtk"].GetFloat();
                data.defense = arr[i]["defense"].GetFloat();
                data.moveSpeed = arr[i]["moveSpeed"].GetFloat();
                data.score = arr[i]["score"].GetInt();
                data.dropExp = arr[i]["dropExp"].GetInt();
                
                monsterStatDatas.insert({ data.id, data });
            }
        }
    }
}

void DataManager::LoadRoundSpawnData()
{
    // JSON 파일을 관리할 Document 객체
    Document doc = LoadData("data/RoundData.json");

    // 오류 검사
    if (doc.HasParseError())
    {
        // 오류가 존재하는 경우 콘솔로 출력하고 프로그램 종료
        log("GetParseError : %d", doc.GetParseError());
        return;
    }
    else
    {
        // 그룹 데이터
        const rapidjson::Value& arr = doc["RoundSpawnArray"];

        if (arr.IsArray())
        {
            for (SizeType i = 0; i < arr.Size(); i++)
            {
                RoundSpawnData data;
                data.roundId = arr[i]["round"].GetInt();
                data.spawnInvertal = arr[i]["spawnInterval"].GetFloat();
                
                SpawnArrayData data2;
                data2.spawnWaveInterval = arr[i]["spawnData"]["spawnWaveInterval"].GetFloat();

                const rapidjson::Value& arr2 = arr[i]["spawnData"]["spawnWaveArray"];
                
                if (arr2.IsArray())
                {
                    for (SizeType j = 0; j < arr2.Size(); j++)
                    {
                        SpawnWaveArrayData data3;
                        data3.monsterId = arr2[j]["monsterId"].GetInt();
                        data3.spawnCount = arr2[j]["spawnCount"].GetInt();

                        data2.spawnWaveData.push_back(data3);
                    }
                }

                data.spawnData = data2;

                roundSpawnDatas.insert({ data.roundId, data });
            }
        }
    }
}

void DataManager::LoadSpriteData()
{
    // JSON 파일을 관리할 Document 객체
    Document doc = LoadData("data/CreatureSpriteData.json");

    // 오류 검사
    if (doc.HasParseError())
    {
        // 오류가 존재하는 경우 콘솔로 출력하고 프로그램 종료
        log("GetParseError : %d", doc.GetParseError());
        return;
    }
    else
    {
        // 그룹 데이터
        const rapidjson::Value& arr = doc["CreatureSpriteData"];

        if (arr.IsArray())
        {
            for (SizeType i = 0; i < arr.Size(); i++)
            {
                SpriteData data;
                data.spriteId = arr[i]["spriteId"].GetString();
                if (arr[i].HasMember("uiImagePath"))
                    data.uiImagePath = arr[i]["uiImagePath"].GetString();
                const rapidjson::Value& arr2 = arr[i]["defaultSpriteData"];
                if (arr2.IsArray())
                {
                    for (SizeType j = 0; j < arr2.Size(); j++)
                    {
                        DefaultSpriteData data2;
                        data2.path = arr2[j]["path"].GetString();
                        data2.sizeY = arr2[j]["sizeY"].GetFloat();
                        data2.sizeX = arr2[j]["sizeX"].GetFloat();
                        data2.rowMinY = arr2[j]["rowMinY"].GetInt();
                        data2.rowMaxY = arr2[j]["rowMaxY"].GetInt();
                        data2.colMinX = arr2[j]["colMinX"].GetInt();
                        data2.colMaxX = arr2[j]["colMaxX"].GetInt();
                        data2.animSpeed = arr2[j]["animSpeed"].GetFloat();
                        
                        data.dspriteData = data2;
                    }
                }
                const rapidjson::Value& arr3 = arr[i]["animationData"];
                if (arr3.IsArray())
                {
                    for (SizeType j = 0; j < arr3.Size(); j++)
                    {
                        AnimationData data3;
                        data3.state = arr3[j]["state"].GetString();
                        data3.path = arr3[j]["path"].GetString();
                        data3.sizeY = arr3[j]["sizeY"].GetFloat();
                        data3.sizeX = arr3[j]["sizeX"].GetFloat();
                        data3.rowMinY = arr3[j]["rowMinY"].GetInt();
                        data3.rowMaxY = arr3[j]["rowMaxY"].GetInt();
                        data3.colMinX = arr3[j]["colMinX"].GetInt();
                        data3.colMaxX = arr3[j]["colMaxX"].GetInt();
                        data3.animSpeed = arr3[j]["animSpeed"].GetFloat();
                        data3.isLoop = arr3[j]["isLoop"].GetBool();
                    
                        log("%s : %d", data3.state.c_str(), data3.isLoop);

                        data.animData.insert({ data3.state, data3 });
                    }
                }

                spriteDatas.insert({ data.spriteId, data });
            }
        }
    }
}

void DataManager::LoadMonsterData()
{
    // JSON 파일을 관리할 Document 객체
    Document doc = LoadData("data/MonsterInfoData.json");

    // 오류 검사
    if (doc.HasParseError())
    {
        // 오류가 존재하는 경우 콘솔로 출력하고 프로그램 종료
        log("GetParseError : %d", doc.GetParseError());
        return;
    }
    else
    {
        // 그룹 데이터
        const rapidjson::Value& arr = doc["MonsterInfoDatas"];

        if (arr.IsArray())
        {
            for (SizeType i = 0; i < arr.Size(); i++)
            {
                MonsterInfoData data;
                data.id = arr[i]["id"].GetInt();
                data.spriteId = arr[i]["spriteId"].GetString();
                data.soundId = arr[i]["soundId"].GetString();
                data.isBoss = arr[i]["isBoss"].GetBool();

                // 그룹 데이터
                const rapidjson::Value& skillArr = arr[i]["skillIds"];
                if (skillArr.IsArray())
                {
                    for (SizeType j = 0; j < skillArr.Size(); j++)
                    {
                        data.skillIds.push_back(skillArr[j]["id"].GetInt());
                    }
                }

                monsterDatas.insert({ data.id, data });
            }
        }
    }
}

void DataManager::LoadPlayerData()
{
    // JSON 파일을 관리할 Document 객체
    Document doc = LoadData("data/PlayerInfoData.json");

    // 오류 검사
    if (doc.HasParseError())
    {
        // 오류가 존재하는 경우 콘솔로 출력하고 프로그램 종료
        log("GetParseError : %d", doc.GetParseError());
        return;
    }
    else
    {
        // 그룹 데이터
        const rapidjson::Value& arr = doc["PlayerInfoDatas"];

        if (arr.IsArray())
        {
            for (SizeType i = 0; i < arr.Size(); i++)
            {
                CreatureInfoData data;
                data.id = arr[i]["id"].GetInt();
                data.spriteId = arr[i]["spriteId"].GetString();
                data.soundId = arr[i]["soundId"].GetString();

                // 그룹 데이터
                const rapidjson::Value& skillArr = arr[i]["skillIds"];
                if (skillArr.IsArray())
                {
                    for (SizeType j = 0; j < skillArr.Size(); j++)
                    {
                        data.skillIds.push_back(skillArr[j]["id"].GetInt());
                    }
                }
                playerDatas.insert({ data.id, data });
            }
        }
    }
}

void DataManager::LoadRepeatSkillData()
{
    // JSON 파일을 관리할 Document 객체
    Document doc = LoadData("data/RepeatSkillData.json");

    // 오류 검사
    if (doc.HasParseError())
    {
        // 오류가 존재하는 경우 콘솔로 출력하고 프로그램 종료
        log("GetParseError : %d", doc.GetParseError());
        return;
    }
    else
    {
        // 그룹 데이터
        const rapidjson::Value& arr = doc["RepeatSkillDatas"];

        if (arr.IsArray())
        {
            for (SizeType i = 0; i < arr.Size(); i++)
            {
                SkillInfo data;
                data.skillId = arr[i]["skillId"].GetInt();
                data.skillName = arr[i]["skillName"].GetString();
                data.skillSpritePath = arr[i]["skillSpritePath"].GetString();

                // 그룹 데이터
                const rapidjson::Value& skillDatas = arr[i]["skillDatas"];
                if (skillDatas.IsArray())
                {
                    for (SizeType j = 0; j < skillDatas.Size(); j++)
                    {
                        SkillStatData statData;
                        statData.level = skillDatas[j]["level"].GetInt();
                        statData.cooltime = skillDatas[j]["cooltime"].GetFloat();
                        statData.atk = skillDatas[j]["atk"].GetFloat();
                        statData.specialAtk = skillDatas[j]["specialAtk"].GetFloat();
                        statData.speed = skillDatas[j]["speed"].GetFloat();
                        statData.command = skillDatas[j]["command"].GetString();
                        if (skillDatas[j].HasMember("value"))
                            statData.value = skillDatas[j]["value"].GetFloat();
                        statData.extraMaxHp = skillDatas[j]["extraMaxHp"].GetFloat();
                        statData.extraAtk = skillDatas[j]["extraAtk"].GetFloat();
                        statData.extraSpecialAtk = skillDatas[j]["extraSpecialAtk"].GetFloat();
                        statData.extraDefense = skillDatas[j]["extraDefense"].GetFloat();
                        statData.extraMoveSpeed = skillDatas[j]["extraMoveSpeed"].GetFloat();

                        data.skillDatas.insert({ statData.level, statData });
                    }
                }

                this->skillDatas.insert({ data.skillId, data });
            }
        }
    }
}

void DataManager::LoadBuffSkillData()
{
    // JSON 파일을 관리할 Document 객체
    Document doc = LoadData("data/BuffSkillData.json");

    // 오류 검사
    if (doc.HasParseError())
    {
        // 오류가 존재하는 경우 콘솔로 출력하고 프로그램 종료
        log("GetParseError : %d", doc.GetParseError());
        return;
    }
    else
    {
        // 그룹 데이터
        const rapidjson::Value& arr = doc["BuffSkillDatas"];

        if (arr.IsArray())
        {
            for (SizeType i = 0; i < arr.Size(); i++)
            {
                SkillInfo data;
                data.skillId = arr[i]["skillId"].GetInt();
                data.skillName = arr[i]["skillName"].GetString();
                data.skillSpritePath = arr[i]["skillSpritePath"].GetString();

                // 그룹 데이터
                const rapidjson::Value& skillDatas = arr[i]["skillDatas"];
                if (skillDatas.IsArray())
                {
                    for (SizeType j = 0; j < skillDatas.Size(); j++)
                    {
                        SkillStatData statData;
                        statData.level = skillDatas[j]["level"].GetInt();
                        statData.cooltime = skillDatas[j]["cooltime"].GetFloat();
                        statData.atk = skillDatas[j]["atk"].GetFloat();
                        statData.specialAtk = skillDatas[j]["specialAtk"].GetFloat();
                        statData.speed = skillDatas[j]["speed"].GetFloat();
                        statData.command = skillDatas[j]["command"].GetString();

                        statData.extraMaxHp = skillDatas[j]["extraMaxHp"].GetFloat();
                        statData.extraAtk = skillDatas[j]["extraAtk"].GetFloat();
                        statData.extraSpecialAtk = skillDatas[j]["extraSpecialAtk"].GetFloat();
                        statData.extraDefense = skillDatas[j]["extraDefense"].GetFloat();
                        statData.extraMoveSpeed = skillDatas[j]["extraMoveSpeed"].GetFloat();

                        data.skillDatas.insert({ statData.level, statData });
                    }
                }

                this->skillDatas.insert({ data.skillId, data });
            }
        }
    }
}

void DataManager::LoadSequenceSkillData()
{
    // JSON 파일을 관리할 Document 객체
    Document doc = LoadData("data/SequenceSkillData.json");

    // 오류 검사
    if (doc.HasParseError())
    {
        // 오류가 존재하는 경우 콘솔로 출력하고 프로그램 종료
        log("GetParseError : %d", doc.GetParseError());
        return;
    }
    else
    {
        // 그룹 데이터
        const rapidjson::Value& arr = doc["SequenceSkillDatas"];

        if (arr.IsArray())
        {
            for (SizeType i = 0; i < arr.Size(); i++)
            {
                SkillInfo data;
                data.skillId = arr[i]["skillId"].GetInt();
                data.skillName = arr[i]["skillName"].GetString();
                data.skillSpritePath = arr[i]["skillSpritePath"].GetString();

                // 그룹 데이터
                const rapidjson::Value& skillDatas = arr[i]["skillDatas"];
                if (skillDatas.IsArray())
                {
                    for (SizeType j = 0; j < skillDatas.Size(); j++)
                    {
                        SkillStatData statData;
                        statData.level = skillDatas[j]["level"].GetInt();
                        statData.cooltime = skillDatas[j]["cooltime"].GetFloat();
                        statData.atk = skillDatas[j]["atk"].GetFloat();
                        statData.specialAtk = skillDatas[j]["specialAtk"].GetFloat();
                        statData.speed = skillDatas[j]["speed"].GetFloat();
                        statData.command = skillDatas[j]["command"].GetString();

                        statData.extraMaxHp = skillDatas[j]["extraMaxHp"].GetFloat();
                        statData.extraAtk = skillDatas[j]["extraAtk"].GetFloat();
                        statData.extraSpecialAtk = skillDatas[j]["extraSpecialAtk"].GetFloat();
                        statData.extraDefense = skillDatas[j]["extraDefense"].GetFloat();
                        statData.extraMoveSpeed = skillDatas[j]["extraMoveSpeed"].GetFloat();

                        data.skillDatas.insert({ statData.level, statData });
                    }
                }

                this->skillDatas.insert({ data.skillId, data });
            }
        }
    }
}

void DataManager::LoadPortionData()
{
    // JSON 파일을 관리할 Document 객체
    Document doc = LoadData("data/PortionData.json");

    // 오류 검사
    if (doc.HasParseError())
    {
        // 오류가 존재하는 경우 콘솔로 출력하고 프로그램 종료
        log("GetParseError : %d", doc.GetParseError());
        return;
    }
    else
    {
        // 그룹 데이터
        const rapidjson::Value& arr = doc["PortionDatas"];

        if (arr.IsArray())
        {
            for (SizeType i = 0; i < arr.Size(); i++)
            {
                SkillInfo data;
                data.skillId = arr[i]["skillId"].GetInt();
                data.skillName = arr[i]["skillName"].GetString();
                data.skillSpritePath = arr[i]["skillSpritePath"].GetString();

                // 그룹 데이터
                const rapidjson::Value& skillDatas = arr[i]["skillDatas"];
                if (skillDatas.IsArray())
                {
                    for (SizeType j = 0; j < skillDatas.Size(); j++)
                    {
                        SkillStatData statData;
                        statData.level = skillDatas[j]["level"].GetInt();
                        statData.cooltime = skillDatas[j]["cooltime"].GetFloat();
                        statData.atk = skillDatas[j]["atk"].GetFloat();
                        statData.specialAtk = skillDatas[j]["specialAtk"].GetFloat();
                        statData.speed = skillDatas[j]["speed"].GetFloat();
                        statData.command = skillDatas[j]["command"].GetString();
                        statData.value = skillDatas[j]["value"].GetFloat();

                        statData.extraMaxHp = skillDatas[j]["extraMaxHp"].GetFloat();
                        statData.extraAtk = skillDatas[j]["extraAtk"].GetFloat();
                        statData.extraSpecialAtk = skillDatas[j]["extraSpecialAtk"].GetFloat();
                        statData.extraDefense = skillDatas[j]["extraDefense"].GetFloat();
                        statData.extraMoveSpeed = skillDatas[j]["extraMoveSpeed"].GetFloat();

                        data.skillDatas.insert({ statData.level, statData });
                    }
                }

                this->skillDatas.insert({ data.skillId, data });
            }
        }
    }
}

void DataManager::LoadPlayerUsealbeSkillData()
{
    // JSON 파일을 관리할 Document 객체
    Document doc = LoadData("data/PlayerUseAbleSkill.json");

    // 오류 검사
    if (doc.HasParseError())
    {
        // 오류가 존재하는 경우 콘솔로 출력하고 프로그램 종료
        log("GetParseError : %d", doc.GetParseError());
        return;
    }
    else
    {
        // 그룹 데이터
        const rapidjson::Value& arr = doc["Skill"];

        if (arr.IsArray())
        {
            for (SizeType i = 0; i < arr.Size(); i++)
            {
                SkillId id = static_cast<SkillId>(arr[i]["id"].GetInt());

                SkillInfo skillInfo = GetSkillInfoData(id);

                if (skillInfo.skillId != -1)
                {
                    int levelSize = skillInfo.skillDatas.size();
                    playerUseAbleSkill.insert({ id , levelSize });
                }
            }
        }
    }
}

void DataManager::LoadCreatureSoundData()
{
    // JSON 파일을 관리할 Document 객체
    Document doc = LoadData("data/CreatureSoundData.json");

    // 오류 검사
    if (doc.HasParseError())
    {
        // 오류가 존재하는 경우 콘솔로 출력하고 프로그램 종료
        log("GetParseError : %d", doc.GetParseError());
        return;
    }
    else
    {
        // 그룹 데이터
        const rapidjson::Value& arr = doc["CreatureSoundDatas"];

        if (arr.IsArray())
        {
            for (SizeType i = 0; i < arr.Size(); i++)
            {
                CreatureSoundInfo data;
                data.id = arr[i]["id"].GetString();
                data.Damaged = arr[i]["Damaged"].GetString();
                data.Die = arr[i]["Die"].GetString();

                soundDatas.insert({ data.id, data });
            }
        }
    }
}

void DataManager::LoadFirstSkillSetData()
{
    // JSON 파일을 관리할 Document 객체
    Document doc = LoadData("data/FirstSkillSetData.json");

    // 오류 검사
    if (doc.HasParseError())
    {
        // 오류가 존재하는 경우 콘솔로 출력하고 프로그램 종료
        log("GetParseError : %d", doc.GetParseError());
        return;
    }
    else
    {
        // 그룹 데이터
        const rapidjson::Value& arr = doc["FirstSkillSet"];

        if (arr.IsArray())
        {
            for (SizeType i = 0; i < arr.Size(); i++)
            {
                SkillId id;
                id = (SkillId)arr[i]["id"].GetInt();
                firstSkillSet.insert(id);
            }
        }
    }
}
