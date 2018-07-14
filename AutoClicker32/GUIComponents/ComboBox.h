#pragma once
#include "Item.h"

class ComboBox : public Item {
	std::vector<LPCWSTR> preStrings;
	int preSelection;
public:
	ComboBox();
	virtual ~ComboBox();

private:
	void ClearPreSelection();

public:
	void AddString(LPCWSTR str);

	int GetSelection();
	void SetSelection(int index);

	int GetCount();

private:
	bool BeforeCreate() override;
	bool AfterCreate() override;
};