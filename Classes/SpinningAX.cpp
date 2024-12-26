#include "SpinningAX.h"
#include "Bitmask.h"
#include "IHitable.h"
#include "Creature.h"
#include "Tags.h"
#include "Axe.h"
#include "Managers.h"
#include "DataManager.h"
#include "Utils.h"
USING_NS_CC;

SpinningAX::SpinningAX(Creature* parent, int level) : Super(parent, level)
{
    _skillId = SkillId::SpinningAX;
}

SpinningAX::~SpinningAX()
{
}

bool SpinningAX::SetLevel(int level)
{
    bool result = Super::SetLevel(level);

    if (result)
    {
        for (auto axe : axes)
        {
            axe->removeFromParent();
        }
        axes.clear();

        switch (level)
        {
        case 1:
        {
            auto axe = Axe::create(_owner, this);
            axe->setPosition(Vec2(200.0f, 0.0f));
            axes.push_back(axe);
            this->addChild(axe);
        }
        break;
        case 2:
        {
            auto dir = Utils::RotateVec2(Vec2(0.0f, 1.0f), 0.0f);

            auto axe = Axe::create(_owner, this);
            axe->setPosition(dir * 200);
            axe->setRotation(Utils::GetDirAngle(dir, Vec2(1.0f, 0.0f)));
            axes.push_back(axe);
            this->addChild(axe);

            dir = Utils::RotateVec2(dir, 180.0f);
            auto axe2 = Axe::create(_owner, this);
            axe2->setPosition(dir * 200);
            axe2->setRotation(Utils::GetDirAngle(dir, Vec2(1.0f, 0.0f)));
            axes.push_back(axe2);
            this->addChild(axe2);
        }
        break;
        default:
        {
            auto dir = Utils::RotateVec2(Vec2(0.0f, 1.0f), 0.0f);

            auto axe = Axe::create(_owner, this);
            axe->setPosition(dir * 200);
            axe->setRotation(Utils::GetDirAngle(dir, Vec2(1.0f, 0.0f)));
            axes.push_back(axe);
            this->addChild(axe);

            dir = Utils::RotateVec2(dir, 120.0f);
            auto axe2 = Axe::create(_owner, this);
            axe2->setPosition(dir * 200);
            axe2->setRotation(Utils::GetDirAngle(dir, Vec2(1.0f, 0.0f)));
            axes.push_back(axe2);
            this->addChild(axe2);

            dir = Utils::RotateVec2(dir, 120.0f);
            auto axe3 = Axe::create(_owner, this);
            axe3->setPosition(dir * 200);
            axe3->setRotation(Utils::GetDirAngle(dir, Vec2(1.0f, 0.0f)));
            axes.push_back(axe3);
            this->addChild(axe3);
        }
        break;
        }


        ActivateSkill();
    }

    return result;
}

bool SpinningAX::init()
{
    if (!Super::init())
        return false;

    SetLevel(_level);

    return true;
}

void SpinningAX::DoSkillJob()
{
    // µµ³¢ È¸Àü
    float z = getRotation();
    float nextZ = z + 1 * Director::getInstance()->getDeltaTime() * skillStatData.speed;
    setRotation(nextZ);

}