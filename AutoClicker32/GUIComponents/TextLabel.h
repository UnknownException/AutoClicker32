#pragma once
#include "Item.h"

class TextLabel : public Item{
	bool sunken;
public:
	TextLabel();
	virtual ~TextLabel();

	LPCWSTR GetText() { return GetTitle(); }
	void SetText(LPCWSTR t) { SetTitle(t); }

	bool GetSunken() { return sunken; }
	void SetSunken(bool b) { sunken = b; }

private:
	bool BeforeCreate() override;
	bool AfterCreate() override;
};