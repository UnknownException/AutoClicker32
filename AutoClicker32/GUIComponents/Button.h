#pragma once
#include "Item.h"

class Button : public Item {
public:
	Button();
	virtual ~Button();

	LPCWSTR GetText() { return GetTitle(); }
	void SetText(LPCWSTR str) { SetTitle(str); }

private:
	bool BeforeCreate() override;
	bool AfterCreate() override;
};