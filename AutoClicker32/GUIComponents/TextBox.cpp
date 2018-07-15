#include "stdafx.h"
#include "TextBox.h"

TextBox::TextBox()
{
	SetClassname(L"EDIT");
	SetStyle(WS_VISIBLE | WS_CHILD | ES_LEFT | ES_AUTOVSCROLL);
	SetBorder(true);

	SetMultiLine(false);
	SetVerticalScroll(false);
	SetReadOnly(false);

	text = nullptr;
	textAlignment = ALIGNLEFT;
}

TextBox::~TextBox()
{
	ClearText();
}

void TextBox::ClearText()
{
	if (text)
	{
		delete[] text;
		text = nullptr;
	}
}

LPCWSTR TextBox::GetText()
{
	if (GetSelf())
	{
		int length = static_cast<int>(SendMessage(GetSelf(), WM_GETTEXTLENGTH, 0, 0)) + 1;

		ClearText();
		WCHAR* output = new WCHAR[length];

		SendMessage(GetSelf(), WM_GETTEXT, length, (LPARAM)output);
		text = output;
	}

	return text;
}

void TextBox::SetText(LPCWSTR string)
{
	if (GetSelf())
	{
		SendMessage(GetSelf(), WM_SETTEXT, 0, (LPARAM)string);
	}
	else
	{
		ClearText();
		WCHAR* output = new WCHAR[wcslen(string) + 1];

		wcscpy_s(output, wcslen(string) + 1, string);
		text = output;
	}
}

void TextBox::AppendText(LPCWSTR string)
{
	LPCWSTR currentText = GetText();

	int appendedLength = wcslen(currentText) + wcslen(string) + 1;
	WCHAR* appended = new WCHAR[appendedLength];
	wcscpy_s(appended, appendedLength, currentText);
	wcscat_s(appended, appendedLength, (WCHAR*)string);
	appended[appendedLength - 1] = 0;

	SetText(appended);
	delete[] appended;
}

void TextBox::SetReadOnly(bool b)
{
	readOnly = b;

	if (GetSelf())
		SendMessage(GetSelf(), EM_SETREADONLY, readOnly, 0);
}

void TextBox::FocusBottom()
{
	SendMessage(GetSelf(), EM_SETSEL, 0, -1); // Select
	SendMessage(GetSelf(), EM_SETSEL, -1, -1); // Unselect
	SendMessage(GetSelf(), EM_SCROLLCARET, 0, 0); // Set caret
}

bool TextBox::BeforeCreate()
{
	DWORD dwStyle = WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL;
	if (multiLine)
		dwStyle |= ES_MULTILINE;
	if (verticalScroll)
		dwStyle |= WS_VSCROLL;
	if (readOnly)
		dwStyle |= ES_READONLY;

	if (textAlignment == ALIGNCENTER)
		dwStyle |= ES_CENTER;
	else if (textAlignment == ALIGNRIGHT)
		dwStyle |= ES_RIGHT;
	else
		dwStyle |= ES_LEFT;

	SetStyle(dwStyle);

	return true;
}

bool TextBox::AfterCreate()
{
	if (text)
		SetText(text);

	return true;
}

