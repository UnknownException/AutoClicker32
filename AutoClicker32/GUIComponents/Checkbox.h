#pragma once
#include "Item.h"

class Checkbox : public Item {
	bool preCheck;
public:
	Checkbox();
	virtual ~Checkbox();

	LPCWSTR GetText() { return GetTitle(); }
	void SetText(LPCWSTR str) { SetTitle(str); }

	bool GetCheck();
	void SetCheck(bool s);

private:
	bool BeforeCreate() override;
	bool AfterCreate() override;
};