#include "UI_Scene.h"
#include "Utils.h"
#include "Managers.h"
#include "UIManager.h"
#include "BossMonster.h"
#include "UI_BossInfo.h"
USING_NS_CC;

UI_Scene::UI_Scene()
{
}

UI_Scene::~UI_Scene()
{
}

bool UI_Scene::init()
{
	if (!Super::init())
		return false;

	setAnchorPoint(Vec2(0.5f, 0.5f));
	setPosition(Utils::GetScreenPos(PivotPoint::LeftBottom));
	Managers::UI()->SetCanvas(this, false);

	return true;
}

void UI_Scene::ActiveBossInfo(BossMonster* bossMonster)
{
    bossMonster->bossInfo = UI_BossInfo::create();
    bossMonster->bossInfo->SetInit(bossMonster);

    bossInfos.insert(bossMonster->bossInfo);

    if (bossMonster)
    {
        bossMonster->deadAction.addCallback([this, bossMonster]() {
            bossInfos.erase(bossMonster->bossInfo);
            bossMonster->bossInfo->removeFromParent();
            });
    }

    this->addChild(bossMonster->bossInfo);

}


