#pragma once

namespace cocos2d
{
	class Node;
}

class IHitable
{
public:
	virtual void OnAttacked(float damage) = 0;
	virtual void OnAttacked(cocos2d::Node* other, float damage) = 0;
};