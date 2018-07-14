#pragma once
#include "Item.h"
#include "TextBox.h"

class NumericBox : public Item {
	TextBox* textBox;
public:
	NumericBox();
	virtual ~NumericBox();

private:
	bool BeforeCreate() override;
	bool AfterCreate() override;
};