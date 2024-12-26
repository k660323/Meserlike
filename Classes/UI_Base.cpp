#include "UI_Base.h"
#include "map"
#include "Managers.h"
#include "UIManager.h"
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


