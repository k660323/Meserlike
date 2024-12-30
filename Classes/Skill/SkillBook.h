#pragma once
#include <type_traits>
#include "SkillBase.h"
#include "SequenceSkill.h"
#include "PassiveSkill.h"
#include "Managers.h"

namespace cocos2d
{
	class Vec2;
	class Node;
}
class Creature;

class SkillBook
{
public:
	SkillBook(Creature* owner);
	virtual ~SkillBook();

	void AddSkillById(SkillId skillId, cocos2d::Vec2 position, Creature* parent, int level = 1);

	//template <typename T>
	//typename std::enable_if<std::is_base_of<SkillBase, T>::value, T*>::type 
	//	AddSkill(cocos2d::Vec2 position, Creature* parent, int level = 1);

	void StartNextSequenceSkill();

	void OnFinishedSequenceSkill();

	void StopSkills();

	SkillBase* GetSkill(SkillId skillId);

protected:
	int _sequenceIndex;
	bool _stopped;
	Creature* _owner;

public:
	std::vector<SkillBase*> Skills;
	
	std::map<SkillId, SkillBase*> RepeatedSkills;
	std::vector<SequenceSkill*> SequenceSkills;
	std::map<SkillId, PassiveSkill*> buffSkills;
};

//template<typename T>
//inline typename std::enable_if<std::is_base_of<SkillBase, T>::value, T*>::type SkillBook::AddSkill(cocos2d::Vec2 position, Creature* parent, int level)
//{
//	std::string objType = typeid(T).name();
//
//	SkillBase* skillBase;
//
//	if (objType == "class SpinningAX")
//		skillBase = SpinningAX::create(parent, level);
//	else if (objType == "class EnemyRangeBullet")
//		skillBase = EnemyRangeBullet::create(parent, level);
//	else if (objType == "class RepeatSpeedBuff")
//		skillBase = RepeatSpeedBuff::create(parent, level);
//	else if (objType == "class MultiShot")
//		skillBase = MultiShot::create(parent, level);
//
//	if (skillBase)
//	{
//		Skills.push_back(skillBase);
//		RepeatedSkills.push_back(skillBase);
//		parent->addChild(skillBase);
//	}
//
//	return dynamic_cast<T*>(skillBase);
//}
