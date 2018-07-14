#include "stdafx.h"
#include "NumericBox.h"

NumericBox::NumericBox()
{
	SetClassname(L"msctls_updown32");
	SetStyle(WS_VISIBLE | WS_CHILD | UDS_AUTOBUDDY | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK);

	textBox = nullptr;
}

NumericBox::~NumericBox()
{
	if (textBox)
		delete textBox;
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

	return textBox->Create();
}

bool NumericBox::AfterCreate()
{
	return true;
}