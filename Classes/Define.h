#pragma once

#define CREATE_FUNC_SKILL(__TYPE__) \
static __TYPE__* create(class Creature* parent, int level = 1) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(parent, level); \
    if (pRet && pRet->init()) \
	{ \
        pRet->autorelease(); \
        return pRet; \
    } \
	else \
	{ \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

#define CREATE_FUNC_SKILL_PASSIVE(__TYPE__) \
static __TYPE__* create(class Creature* parent, SkillId skillId, int level = 1) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(parent, skillId, level); \
    if (pRet && pRet->init()) \
	{ \
        pRet->autorelease(); \
        return pRet; \
    } \
	else \
	{ \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

#define CREATE_FUNC_WEAPON(__TYPE__) \
static __TYPE__* create(class Creature* parent, class SkillBase* skillBase) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(parent, skillBase); \
    if (pRet && pRet->init()) \
	{ \
        pRet->autorelease(); \
        return pRet; \
    } \
	else \
	{ \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

#define CREATE_FUNC_PROJECTILE(__TYPE__) \
static __TYPE__* create(class Creature* parent, class SkillBase* skillBase, float scale = 0.5f, std::string path = "Projectile/Bullet.png") \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(parent, skillBase, scale, path); \
    if (pRet && pRet->init()) \
	{ \
        pRet->autorelease(); \
        return pRet; \
    } \
	else \
	{ \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

#define CREATE_FUNC_Monster(__TYPE__) \
static __TYPE__* create(MonsterType type) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(type); \
    if (pRet && pRet->init()) \
	{ \
        pRet->autorelease(); \
        return pRet; \
    } \
	else \
	{ \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

#define CREATE_FUNC_Player(__TYPE__) \
static __TYPE__* create(int level) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(level); \
    if (pRet && pRet->init()) \
	{ \
        pRet->autorelease(); \
        return pRet; \
    } \
	else \
	{ \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

enum class MonsterType
{
	None = -1,
	Snail = 0,
	BlueSnail = 1,
	RedSnail = 2,
	CokeSnail = 3,
	DeformedSnail = 4,
	ChubbySnail = 5,
	MossSnail = 6,
	BlackSnail = 7,
	DesertSnail = 8,
	FierceDesertSnail = 9,
	Mano = 10
};

enum class PivotPoint
{
	LeftTop,
	Top,
	RightTop,
	Left,
	Center,
	Right,
	LeftBottom,
	CenterBottom,
	RightBottom
};

enum class SceneType
{
	None,
	Lobby,
	Game,
	MAX
};

enum class SoundType
{
	None,
	Sound,
	BGM
};

enum class PopupType
{
	None,
	UI_Setting,
	UI_PauseMenuWindow,
	UI_ResultWindow,
	UI_SkillSelect
};

enum class Dir
{
	Left,
	Right
};

enum class State
{
	None,
	Idle,
	Move,
	Dead
};

enum class CreatureType
{
	None,
	Monster,
	Player
};

enum class SkillType
{
	None,
	Repeat,
	Sequence,
	Buff,
	Portion
};

enum class SkillId
{
	None = -1,
	// 반복 스킬 0 ~ 999
	SpinningAX = 0,
	Gun,
	Bow,
	Fan,
	ProjectileSheid,

	

	// 버프 1000 ~ 1999
	SpeedUp = 1000,
	DefenseUp,
	MaxHpUp,
	DamgeUPAndSpecialAtkDown,
	SpecialAtkAndDamgeDown,

	// 순차 스킬 2000 ~ 2999
	Move = 2000,
	Dash = 2001,
	FullCircleShot = 2002,

	// 포션 3000 ~ 3999
	HpPortion = 3000,

	// 반복 스킬 (몹 전용) 4000 ~ 4999
	EnemyRangeBullet = 4000,
	MultiShot,
	RepeatSpeedBuff,
};