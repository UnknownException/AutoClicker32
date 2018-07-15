#pragma once
#include "Item.h"

class TextBox : public Item {
public:
	enum TextAlignment {
		ALIGNLEFT,
		ALIGNCENTER,
		ALIGNRIGHT
	};

private:
	bool multiLine;
	bool verticalScroll;
	bool readOnly;
	LPCWSTR text;
	TextAlignment textAlignment;
public:
	TextBox();
	virtual ~TextBox();

private:
	void ClearText();

public:
	LPCWSTR GetText();
	void SetText(LPCWSTR string);
	void AppendText(LPCWSTR string);

	bool GetMultiLine() { return multiLine; }
	void SetMultiLine(bool b) { multiLine = b; }

	bool GetVerticalScroll() { return verticalScroll; }
	void SetVerticalScroll(bool b) { verticalScroll = b; }

	bool GetReadOnly() { return readOnly; }
	void SetReadOnly(bool b);

	TextAlignment GetTextAlignment() { return textAlignment; }
	void SetTextAlignment(TextAlignment ta) { textAlignment = ta; }

	void FocusBottom();

	const LPCWSTR GetNewLine() { return L"\r\n"; }

private:
	bool BeforeCreate() override;
	bool AfterCreate() override;
};