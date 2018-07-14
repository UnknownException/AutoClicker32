#pragma once
#include "Vector2.h"
#include "Font.h"

class Item {
	HWND parent;
	HWND self;

	WCHAR* classname;
	WCHAR* title;

	DWORD style;

	Vector2<int> position;
	Vector2<int> size;

	bool border;
	bool visible;
	bool enabled;

	Font* preFont;
	HFONT fontInstance;
public:
	Item();
	virtual ~Item();

	HWND GetParent() { return parent; }
	void SetParent(HWND p) { parent = p; }

protected:
	HWND GetSelf() { return self; }
	void SetSelf(HWND s) { self = s; }

	LPCWSTR GetClassname() { return classname; }
	void SetClassname(LPCWSTR c);

	LPCWSTR GetTitle() { return title; }
	void SetTitle(LPCWSTR t);

	DWORD GetStyle() { return style; }
	void SetStyle(DWORD dw) { style = dw; }

	bool GetBorder() { return border; }
	void SetBorder(bool b) { border = b; }

public:
	decltype(position) GetPosition() { return position; }
	void SetPosition(decltype(position) p) { position = p; }

	decltype(size) GetSize() { return size; }
	void SetSize(decltype(size) s) { size = s; }

	bool GetVisible() { return visible; }
	void SetVisible(bool b);

	bool GetEnabled() { return enabled; }
	void SetEnabled(bool b);

	HFONT GetFont() { return fontInstance; }
	void SetFont(Font* f);

	bool IsSame(HWND hWnd) { return self == hWnd; }
	bool Create() { return Create(NULL); }

protected:
	virtual bool BeforeCreate() = 0; // Before HWND self is set
	bool Create(HINSTANCE hInstance);
	virtual bool AfterCreate() = 0; // After HWND self is set

	static bool RegisterControls();
};
