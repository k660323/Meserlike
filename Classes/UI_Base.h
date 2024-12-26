#pragma once
#include "cocos2d.h"

class map;

// cocos2d-x는 UTF-8 유니코드를 기본적으로 지원하고 있다.
// 그러나 이것이 PC 환경에서는 작동하지 않으므로 별도의 활성화 처리가 필요하다.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

namespace cocos2d
{
	class Sprite;
	class Label;
	namespace ui
	{
		class Button;
		class LoadingBar;
		class ImageView;
	}
}

class UI_Base : public cocos2d::Layer
{
	using Super = cocos2d::Layer;
public:
	UI_Base();
	virtual ~UI_Base();

	virtual bool init() override;

	CREATE_FUNC(UI_Base);

protected:
	template<typename T>
	void Bind(Node* node, int tagId)
	{
		std::string objType = typeid(T).name();

		if (_objects.find(objType) == _objects.end())
		{

			std::map<int, cocos2d::Node* > m = { { tagId, node } };
			_objects.insert({ objType, m });
		}
		else
			_objects[objType].insert({ tagId, node });
	}

public:
	template<typename T>
	T* Get(int idx)
	{
		std::string objType = typeid(T).name();
		if (_objects.find(objType) == _objects.end())
			return nullptr;

		auto v = _objects[objType][idx];
		return dynamic_cast<T*>(v);
	}
protected:
	std::map<std::string, std::map<int, cocos2d::Node*>> _objects;

};