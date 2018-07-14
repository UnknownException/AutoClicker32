#include "stdafx.h"
#include "Checkbox.h"

Checkbox::Checkbox()
{
	SetClassname(L"BUTTON");
	SetStyle(WS_VISIBLE | WS_CHILD | BS_CHECKBOX);

	SetCheck(false);
}

Checkbox::~Checkbox()
{
}

bool Checkbox::GetCheck()
{
	if (GetSelf() != nullptr)
		return SendMessage(GetSelf(), BM_GETCHECK, 0, 0);

	return preCheck;
}

void Checkbox::SetCheck(bool s)
{
	if (GetSelf() != nullptr)
		SendMessage(GetSelf(), BM_SETCHECK, (WPARAM)s, 0);
	else
		preCheck = s;
}

bool Checkbox::BeforeCreate()
{
	return true;
}

bool Checkbox::AfterCreate()
{
	if (GetSelf())
		SetCheck(preCheck);

	return true;
}