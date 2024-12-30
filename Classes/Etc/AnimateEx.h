#pragma once
#include "cocos2d.h"

class AnimateEx
{
public:
	AnimateEx();
	AnimateEx(cocos2d::Node* owner, std::string name, cocos2d::Animation* defaultAnimate, bool roop = true);
	virtual ~AnimateEx();

	void Init(cocos2d::Node* owner, std::string name, cocos2d::Animation* defaultAnimate, bool roop = true, bool clear = true);
	void Claer();

	void SetOwner(cocos2d::Node* owner);

	// 애니메이션을 넘겨주면 애니메이트로 변환되어 관리된다.
	bool RegisterAnimation(std::string name, cocos2d::Animation* animation, bool roop = true);

	void PlayAnimation(std::string name);

	void StopAnimation();

private:
	// 애니메이션을 실행할 대상
	cocos2d::Node* _owner;

	// 실행 중인 액션
	cocos2d::Action* animAction;

	// 등록된 애니메이트
	std::map<std::string, std::pair<bool,cocos2d::Animate*>> animMap;

};