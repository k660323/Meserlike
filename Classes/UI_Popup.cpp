#include "UI_Popup.h"
#include "Managers.h"
#include "UIManager.h"

UI_Popup::UI_Popup()
{
}

UI_Popup::~UI_Popup()
{
}

bool UI_Popup::init()
{
    if (!Super::init())
        return false;

    Managers::UI()->SetCanvas(this);

    Managers::UI()->AddChild(this);

    return true;
}

void UI_Popup::ClosePopupUI()
{
    Managers::UI()->ClosePopupUI(this);
}

void UI_Popup::ClosePopupAllUI()
{
    Managers::UI()->ClosePopupUIAll();
}
