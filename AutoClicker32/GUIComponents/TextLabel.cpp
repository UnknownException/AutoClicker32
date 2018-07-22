#include "stdafx.h"
#include "TextLabel.h"

TextLabel::TextLabel()
{
	SetClassname(L"STATIC");
	SetStyle(WS_VISIBLE | WS_CHILD);

	sunken = false;
	textAlignment = ALIGNLEFT;
}

TextLabel::~TextLabel()
{
}

bool TextLabel::BeforeCreate()
{
	if(sunken)
		SetStyle(GetStyle() | SS_SUNKEN);

	if (textAlignment == ALIGNRIGHT)
		SetStyle(GetStyle() | SS_RIGHT);
	else if (textAlignment == ALIGNCENTER)
		SetStyle(GetStyle() | SS_CENTER);
	else
		SetStyle(GetStyle() | SS_LEFT);

	return true;
}

bool TextLabel::AfterCreate()
{
	return true;
}