#pragma once
#include "Item.h"
#include "TextBox.h"

class NumericBox : public Item {
	TextBox* textBox;
	int min;
	int max;
	int preSelection;

public:
	NumericBox();
	virtual ~NumericBox();

	int GetMin() { return min; }
	void SetMin(int value);

	int GetMax() { return max; }
	void SetMax(int value);

	int GetSelection();
	void SetSelection(int value);

private:
	bool BeforeCreate() override;
	bool AfterCreate() override;
};