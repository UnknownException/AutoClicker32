#include "stdafx.h"
#include "Button.h"

Button::Button()
{
	SetClassname(L"BUTTON");
	SetStyle(WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON);
}

Button::~Button()
{
}

bool Button::BeforeCreate()
{
	return true;
}

bool Button::AfterCreate()
{
	return true;
}