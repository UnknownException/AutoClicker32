#pragma once

class Font {
	WCHAR* name;
	int size;
	bool bold;
public:
	Font();
	virtual ~Font();

	LPCWSTR GetName() { return name; }
	void SetName(LPCWSTR psz);

	int GetSize() { return size; }
	void SetSize(int n) { size = n; }

	bool GetBold() { return bold; }
	void SetBold(bool b) { bold = b; }

	HFONT CreateInstance(HDC hDC);
};