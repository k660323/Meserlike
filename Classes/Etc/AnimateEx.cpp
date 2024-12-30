#include "AnimateEx.h"
#include "cocos2d.h"
#include "map"

USING_NS_CC;

AnimateEx::AnimateEx()
{
    _owner = nullptr;
    animAction = nullptr;
}

AnimateEx::AnimateEx(cocos2d::Node* owner, std::string name, cocos2d::Animation* defaultAnimate, bool roop) : AnimateEx()
{
    SetOwner(owner);
    RegisterAnimation(name, defaultAnimate, true);
    PlayAnimation(name);
}

AnimateEx::~AnimateEx()
{
    Claer();
}

void AnimateEx::Init(cocos2d::Node* owner, std::string name, cocos2d::Animation* defaultAnimate, bool roop, bool clear)
{
    if (_owner)
        return;
    if (clear)
        Claer();

    SetOwner(owner);
    RegisterAnimation(name, defaultAnimate, true);
    PlayAnimation(name);
}

void AnimateEx::Claer()
{
    StopAnimation();

    _owner = nullptr;

    for (auto anim : animMap)
    {
        if (anim.first != "")
        {
            if (anim.second.second != nullptr)
                anim.second.second->autorelease();
        }
    }

    animMap.clear();
}

void AnimateEx::SetOwner(cocos2d::Node* owner)
{
    if (_owner && animAction)
        _owner->stopAction(animAction);

    _owner = owner;
}

bool AnimateEx::RegisterAnimation(std::string name, cocos2d::Animation* animation, bool roop)
{
    if (animMap.find(name) == animMap.end())
    {
        auto animate = Animate::create(animation);
        animate->retain();
        animMap.insert({ name, {roop, animate}});
 
        return true;
    }
    else
    {
        return false;
    }
}

void AnimateEx::PlayAnimation(std::string name)
{
    if (animMap.find(name) == animMap.end())
        return;

    // 현재 실행중인 애니메이션 중지
    if (animAction)
    {
        _owner->stopAction(animAction);
        animAction = nullptr;
    }

    // 애니메이션 재생
    const bool roop = animMap[name].first;
    Animate* animate = animMap[name].second;

    if (roop)
        animAction = RepeatForever::create(animate);
    else
        animAction = Repeat::create(animate, 1);

    _owner->runAction(animAction);
}

void AnimateEx::StopAnimation()
{
    // 애니메이션 중지
    if (animAction)
    {
        animAction = nullptr;
    }
}
