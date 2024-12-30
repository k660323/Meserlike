#include "SkillBook.h"
#include "cocos2d.h"
#include "Creature.h"
#include "SkillDefine.h"
#include "DelegateAction.h"

SkillBook::SkillBook(Creature* owner) : _owner(owner), _sequenceIndex(0), _stopped(false)
{

}

SkillBook::~SkillBook()
{
	_owner = nullptr;
}

void SkillBook::AddSkillById(SkillId skillId, cocos2d::Vec2 position, Creature* parent, int level)
{
	SkillBase* skillBase = SkillDefine::AddSkill(skillId, parent, level);

	if (skillBase)
	{
		Skills.push_back(skillBase);

		if (skillBase->GetSkillType() == SkillType::Repeat)
			RepeatedSkills.insert({ skillId,skillBase });
		else if (skillBase->GetSkillType() == SkillType::Sequence)
			SequenceSkills.push_back(dynamic_cast<SequenceSkill*>(skillBase));
		else if (skillBase->GetSkillType() == SkillType::Buff)
			buffSkills.insert({ skillId, dynamic_cast<PassiveSkill*>(skillBase) });


		parent->addChild(skillBase);
	}

}

void SkillBook::StartNextSequenceSkill()
{
	if (_stopped)
		return;
	if (SequenceSkills.size() == 0)
		return;

	DelegateAction<> tmp;
	tmp.addCallback([this]() { OnFinishedSequenceSkill();  });
	 
	SequenceSkills[_sequenceIndex]->DoSkill(tmp);
}

void SkillBook::OnFinishedSequenceSkill()
{
	_sequenceIndex = (_sequenceIndex + 1) % SequenceSkills.size();
	StartNextSequenceSkill();
}

void SkillBook::StopSkills()
{
	_stopped = true;

	for(auto skill : RepeatedSkills)
	{
		skill.second->stopAllActions();
	}

}

SkillBase* SkillBook::GetSkill(SkillId skillId)
{
	int id = (int)skillId;
	if (0 <= id  && id < 1000)
	{
		if (RepeatedSkills.find(skillId) != RepeatedSkills.end())
			return RepeatedSkills[skillId];
	}
	else if (1000 <= id && id < 2000)
	{
		if (buffSkills.find(skillId) != buffSkills.end())
			return buffSkills[skillId];
	}

	return nullptr;
}
