#include "stdafx.h"
#include "NumericBox.h"

NumericBox::NumericBox()
{
	SetClassname(L"msctls_updown32");
	SetStyle(WS_VISIBLE | WS_CHILD | UDS_AUTOBUDDY | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK);

	textBox = nullptr;

	min = 0;
	max = 100;
	preSelection = 0;
}

NumericBox::~NumericBox()
{
	if (textBox)
		delete textBox;
}

void NumericBox::SetMin(int value)
{
	min = value;

	if (GetSelf())
		SendMessage(GetSelf(), UDM_SETRANGE32, min, max);
}

void NumericBox::SetMax(int value)
{
	max = value;

	if (GetSelf())
		SendMessage(GetSelf(), UDM_SETRANGE32, min, max);
}

int NumericBox::GetSelection()
{
	if (!GetSelf())
		return preSelection;

	return (int)SendMessage(GetSelf(), UDM_GETPOS32, 0, 0);

}

void NumericBox::SetSelection(int value)
{
	if (!GetSelf())
		preSelection = value;
	else
		SendMessage(GetSelf(), UDM_SETPOS32, 0, value);
}

/*
	Creates a Text Box before the Up Down Control is made
	The Up Down Control will bind to this Text Box
*/
bool NumericBox::BeforeCreate()
{
	textBox = new TextBox();
	textBox->SetParent(GetParent());
	textBox->SetPosition(GetPosition());
	textBox->SetSize(GetSize());
	textBox->SetReadOnly(true);
	textBox->SetTextAlignment(TextBox::ALIGNCENTER);

	return textBox->Create();
}

bool NumericBox::AfterCreate()
{
	SetMin(GetMin());
	SetMax(GetMax());

	SetSelection(preSelection);

	return true;
}