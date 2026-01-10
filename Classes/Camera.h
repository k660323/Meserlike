#pragma once

namespace cocos2d
{
	class Node;
}

class Camera
{
public:
	Camera();
	virtual ~Camera();


private:
	cocos2d::Node* _target;

};