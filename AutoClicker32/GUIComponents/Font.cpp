#include "stdafx.h"
#include "Font.h"

Font::Font()
{
	SetName(L"");
	SetSize(10);
	SetBold(false);
}

Font::~Font()
{
	if (name)
		delete[] name;
}

void Font::SetName(LPCWSTR font)
{
	if (name)
		delete[] name;

	name = new WCHAR[wcslen(font) + 1];
	wcscpy_s(name, wcslen(font) + 1, font);
}

HFONT Font::CreateInstance(HDC hDC)
{
	if (!hDC)
		return nullptr;

	LOGFONTW lFnt;
	ZeroMemory(&lFnt, sizeof(LOGFONTW));

	lFnt.lfHeight = -MulDiv(GetSize(), GetDeviceCaps(hDC, LOGPIXELSY), 72);
	lFnt.lfWeight = GetBold() ? FW_BOLD : FW_NORMAL;
	wcscpy_s(lFnt.lfFaceName, sizeof(lFnt.lfFaceName) / sizeof(WCHAR), GetName());

	return CreateFontIndirectW(&lFnt);
}