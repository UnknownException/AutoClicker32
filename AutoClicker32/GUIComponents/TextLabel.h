#pragma once
#include "Item.h"

class TextLabel : public Item{
public:
	enum TextAlignment {
		ALIGNLEFT,
		ALIGNCENTER,
		ALIGNRIGHT
	};

private:
	bool sunken;
	TextAlignment textAlignment;
public:
	TextLabel();
	virtual ~TextLabel();

	LPCWSTR GetText() { return GetTitle(); }
	void SetText(LPCWSTR t) { SetTitle(t); }

	bool GetSunken() { return sunken; }
	void SetSunken(bool b) { sunken = b; }

	TextAlignment GetTextAlignment() { return textAlignment; }
	void SetTextAlignment(TextAlignment ta) { textAlignment = ta; }

private:
	bool BeforeCreate() override;
	bool AfterCreate() override;
};