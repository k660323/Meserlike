#include "GameManager.h"
#include "Contents/Creature/Creature.h"
#include "Contents/Creature/Monster.h"
#include "Contents/Creature/NormalMonster.h"
#include "Contents/Creature/BossMonster.h"
#include "Contents/Creature/Player.h"
#include "Manager/Managers.h"
#include "Manager/Core/DataManager.h"
#include "Data/Data.h"
#include "Manager/Core/UIManager.h"
#include "Contents/Skills/SkillBook.h"
#include <algorithm>

GameManager::GameManager()
{
    player = nullptr;
    score = 0;
    round = 0;
    isGetFirstSkillId = false;
}

GameManager::~GameManager()
{
    player = nullptr;
    creatureSet.clear();
}

Player* GameManager::GetPlayer()
{
    return player;
}

void GameManager::Clear()
{
    if (player)
    {
        // player->removeFromParent();
        player = nullptr;
    }
    
    if (creatureSet.size() > 0)
    {
        //for (auto c : creatureSet)
        //    c->removeFromParent();
        creatureSet.clear();
    }

    roundDelegate.removeAllCallback();

    score = 0;

    playerUseAbleSkill.clear();
    firstSkillVec.clear();

    auto data = Managers::Data()->GetPlayerUseAbleSkillData();
    auto firstSkillSet = Managers::Data()->GetFirstSkillSet();
   
    for (auto it : data)
    {
        if (firstSkillSet.find(it.first) != firstSkillSet.end())
        {
            int index = playerUseAbleSkill.size();
            firstSkillVec.push_back(index);
        }
        playerUseAbleSkill.push_back(it);
    }

    isGetFirstSkillId = false;
}

int GameManager::GetScore()
{
    return score;
}

void GameManager::SetScore(int value)
{
    score = value;
}

int GameManager::GetRound()
{
    return round;
}

void GameManager::SetRound(int value)
{
    round = value;

    roundDelegate.invoke(value);
}

std::vector<std::pair<int, SkillId>> GameManager::GetRandomSkillId(int size)
{
    std::vector<std::pair<int, SkillId>> skillId;
    std::set<int> SkillIdSet;

    if (isGetFirstSkillId == false)
    {
        isGetFirstSkillId = true;
        
        if ((int)playerUseAbleSkill.size() <= size)
        {
            for (int i = 0; i < (int)firstSkillVec.size(); i++)
                skillId.push_back({ i, (SkillId)firstSkillVec[i] });
        }
        else
        {
            while (SkillIdSet.size() < size)
            {
                int index = cocos2d::random(0, (int)firstSkillVec.size() - 1);

                if (SkillIdSet.find(index) != SkillIdSet.end())
                    continue;

                SkillIdSet.insert(index);

                skillId.push_back({ index, (SkillId)firstSkillVec[index] });
            }

        }
    }
    else
    {
        if ((int)playerUseAbleSkill.size() <= size)
        {
            for (int i = 0; i < (int)playerUseAbleSkill.size(); i++)
                skillId.push_back({ i, playerUseAbleSkill[i].first });
        }
        else
        {
            while (SkillIdSet.size() < size)
            {
                int index = cocos2d::random(0, (int)playerUseAbleSkill.size() - 1);

                if (SkillIdSet.find(index) != SkillIdSet.end())
                    continue;

                SkillIdSet.insert(index);

                skillId.push_back({ index, playerUseAbleSkill[index].first });
            }
        }
    }
   
    return skillId;
}

void GameManager::SelectSkill(int index, SkillId skillId, SkillInfo skillInfo, SkillBase* skillBase)
{
    if (skillInfo.skillId == -1)
    {
        playerUseAbleSkill.erase(playerUseAbleSkill.begin() + index);
        return;
    }

    int level = -1;
    if (skillBase == nullptr)
    {
        auto player = Managers::Game()->GetPlayer();
        auto skillBook = player->GetSkillBook();
        skillBook->AddSkillById(skillId, player->getPosition(), player);
        level = 1;
    }
    else
    {
        skillBase->SetLevel(skillBase->GetLevel() + 1);
        level = skillBase->GetLevel();
        cocos2d::log("%d", level);
    }

    auto skillData = Managers::Data()->GetSkillInfoData(skillId);
    int skillMaxLevel = skillData.skillDatas.size();
    if (skillMaxLevel == level)
    {
        playerUseAbleSkill.erase(playerUseAbleSkill.begin() + index);
    }

}

Monster* GameManager::SpawnMonster(MonsterType type)
{
    auto data = Managers::Data()->GetMonsterInfoData(type);
    if (!data.isBoss)
    {
        auto normalMonster = NormalMonster::create(type);
        creatureSet.insert(normalMonster);
        return normalMonster;
    }
    else
    {
        auto bossMonster = BossMonster::create(type);
        creatureSet.insert(bossMonster);
        Managers::UI()->GetUIScene()->ActiveBossInfo(bossMonster);
        return bossMonster;
    }
}

Player* GameManager::SpawnPlayer(int level)
{
    player = Player::create(level);
    return player;
}

void GameManager::DeSpawnCreature(Creature* creature)
{
    if (dynamic_cast<Player*>(creature))
    {
        player = nullptr;
    }
    else if (dynamic_cast<Monster*>(creature))
    {
        if (creatureSet.find(creature) != creatureSet.end())
            creatureSet.erase(creature);
    }
    else
    {
        cocos2d::log("error despawnCreature");
    }

   
    creature->unscheduleAllCallbacks();
    creature->stopAllActions();

    // creature->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(0.00f), cocos2d::RemoveSelf::create(), nullptr));
    creature->removeFromParent();
}
