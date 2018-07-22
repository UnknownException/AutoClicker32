#include "stdafx.h"
#include "Item.h"

Item::Item()
{
	SetParent(nullptr);
	SetSelf(nullptr);

	SetClassname(L"");
	SetTitle(L"");

	SetStyle(0);

	SetBorder(false);
	SetVisible(true);
	SetEnabled(true);

	preFont = nullptr;
	fontInstance = nullptr;
}

Item::~Item()
{
	if (self)
		DestroyWindow(self);

	if (classname)
		delete[] classname;

	if (title)
		delete[] title;

	if (preFont)
		delete preFont;

	if (fontInstance)
		DeleteObject(fontInstance);
}

void Item::SetClassname(LPCWSTR c) 
{ 
	if (classname)
		delete[] classname;

	classname = new WCHAR[wcslen(c) + 1];
	wcscpy_s(classname, wcslen(c) + 1, c);
}

void Item::SetTitle(LPCWSTR t) 
{ 
	if (title)
		delete[] title;

	title = new WCHAR[wcslen(t) + 1];
	wcscpy_s(title, wcslen(t) + 1, t);

	if (GetSelf())
		SetWindowText(GetSelf(), title);
}

void Item::SetVisible(bool b)
{
	visible = b;

	if(GetSelf())
		ShowWindow(GetSelf(), b ? SW_SHOWDEFAULT : SW_HIDE);
}

void Item::SetEnabled(bool b)
{
	enabled = b;

	if(GetSelf())
		EnableWindow(GetSelf(), b);
}

void Item::SetFont(Font* font)
{
	if (GetSelf())
	{
		if (fontInstance)
		{
			DeleteObject(fontInstance);
			fontInstance = nullptr;
		}

		if (font)
		{
			HDC hDC = GetDC(GetSelf());
			fontInstance = font->CreateInstance(hDC);
			ReleaseDC(GetSelf(), hDC);
		}

		SendMessage(GetSelf(), WM_SETFONT, (WPARAM)fontInstance, (LPARAM)MAKELONG(TRUE, 0));
	}
	else
	{
		if (preFont)
			delete preFont;

		preFont = new Font();
		preFont->SetName(font->GetName());
		preFont->SetSize(font->GetSize());
		preFont->SetBold(font->GetBold());
	}
}

bool Item::Create(HINSTANCE hInstance)
{
	if (!RegisterControls())
		return false;

	if (hInstance == NULL && !GetParent())
		return false;

	if (!BeforeCreate())
		return false;

	SetSelf(CreateWindowEx(GetBorder() ? WS_EX_CLIENTEDGE : NULL, GetClassname(), GetTitle(), GetStyle(),
		GetPosition().x, GetPosition().y, GetSize().x, GetSize().y, GetParent(), NULL, hInstance, NULL));

	if (!GetSelf())
		return false;

	SetVisible(GetVisible());
	SetEnabled(GetEnabled());
	SetFont(preFont);

	if (!AfterCreate())
		return false;

	return true;
}

bool Item::RegisterControls()
{
	static bool registered = false;
	if (registered)
		return registered;

	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_STANDARD_CLASSES;
	if (!InitCommonControlsEx(&icex))
		return false;

	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_UPDOWN_CLASS;
	if (!InitCommonControlsEx(&icex))
		return false;

	registered = true;
	return registered;
}
