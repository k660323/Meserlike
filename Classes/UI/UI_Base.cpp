#include "UI_Base.h"
#include "map"
#include "Manager/Managers.h"
#include "Manager/Core/UIManager.h"
USING_NS_CC;

UI_Base::UI_Base()
{

}

UI_Base::~UI_Base()
{
	_objects.clear();
}

bool UI_Base::init()
{
	if (!Super::init())
		return false;

	return true;
}


