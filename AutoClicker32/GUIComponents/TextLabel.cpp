#include "stdafx.h"
#include "TextLabel.h"

TextLabel::TextLabel()
{
	SetClassname(L"STATIC");
	SetStyle(WS_VISIBLE | WS_CHILD | SS_CENTER);

	sunken = false;
}

TextLabel::~TextLabel()
{
}

bool TextLabel::BeforeCreate()
{
	if(sunken)
		SetStyle(GetStyle() | SS_SUNKEN);

	return true;
}

bool TextLabel::AfterCreate()
{
	return true;
}