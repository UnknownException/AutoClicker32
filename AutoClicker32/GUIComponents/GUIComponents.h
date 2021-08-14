// Header generated on 19:46:11 Aug 14 2021
#ifndef _GUICOMPONENTS_HEADER
#define _GUICOMPONENTS_HEADER

#ifdef _GUICOMPONNENTS_HANDLELIBANDHEADERS
	#include <SDKDDKVer.h>

	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>

	#include <CommCtrl.h>
	#pragma comment(lib, "Comctl32.lib")
	#pragma comment(linker,"\"/manifestdependency:type                  = 'win32' \
												  name                  = 'Microsoft.Windows.Common-Controls' \
												  version               = '6.0.0.0' \
												  processorArchitecture = '*' \
												  publicKeyToken        = '6595b64144ccf1df' \
												  language              = '*'\"")

	#include <vector>
#endif

#ifndef _INC_WINDOWS
	#error Windows.h must be included before including the GUIComponents header.
#endif
#ifndef _INC_COMMCTRL
	#error CommCtrl.h must be included before including the GUIComponents header.
#endif

namespace GUIComponents {
// Vector2.h

template <class T>
struct Vector2
{
	T x;
	T y;

	Vector2()
	{
		x = 0;
		y = 0;
	}

	Vector2(T _x, T _y)
	{
		x = _x;
		y = _y;
	}

	Vector2<T> operator+(const Vector2 val)
	{
		Vector2<T> result = *this;
		result.x += val.x;
		result.y += val.y;

		return result;
	}

	Vector2<T> operator-(const Vector2 val)
	{
		Vector2<T> result = *this;
		result.x -= val.x;
		result.y -= val.y;

		return result;
	}

	Vector2<T> operator*(const Vector2 val)
	{
		Vector2<T> result = *this;
		result.x *= val.x;
		result.y *= val.y;

		return result;
	}

	Vector2<T> operator/(const Vector2 val)
	{
		Vector2<T> result = *this;
		result.x /= val.x;
		result.y /= val.y;

		return result;
	}
	
	Vector2<T> operator+(const float val)
	{
		Vector2<T> result = *this;
		result.x += val;
		result.y += val;

		return result;
	}
	
	Vector2<T> operator-(const float val)
	{
		Vector2<T> result = *this;
		result.x -= val;
		result.y -= val;

		return result;
	}
	
	Vector2<T> operator*(const float val)
	{
		Vector2<T> result = *this;
		result.x *= val;
		result.y *= val;

		return result;
	}

	Vector2<T> operator/(const float val)
	{
		Vector2<T> result = *this;
		result.x /= val;
		result.y /= val;

		return result;
	}
};
// eof Vector2.h

// Font.h

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class Font {
	LPWSTR _name;
	int _size;
	bool _bold;

	HFONT _fontInstance;
public:
	LPCWSTR GetName() { return _name; }
	void SetName(LPCWSTR name) {
		if (_name)
			delete[] _name;

		_name = new WCHAR[wcslen(name) + 1];
		wcscpy_s(_name, wcslen(name) + 1, name);
	}

	int GetSize() { return _size; }
	void SetSize(int n) { _size = n; }

	bool GetBold() { return _bold; }
	void SetBold(bool b) { _bold = b; }

	// Don't call! Internal GUIComponents function
	void _CreateInstance(HDC hDC) {
		if (!_fontInstance) {
			LOGFONTW lFnt;
			ZeroMemory(&lFnt, sizeof(LOGFONTW));

			lFnt.lfHeight = hDC ? -MulDiv(GetSize(), GetDeviceCaps(hDC, LOGPIXELSY), 72) : 0;
			lFnt.lfWeight = GetBold() ? FW_BOLD : FW_NORMAL;
			wcscpy_s(lFnt.lfFaceName, sizeof(lFnt.lfFaceName) / sizeof(WCHAR), GetName());

			_fontInstance = CreateFontIndirectW(&lFnt);
		}
	}

	// Don't call! Internal GUIComponents function
	HFONT _GetInstance() { return _fontInstance; }
	
	Font() {
		SetName(L"");
		SetSize(10);
		SetBold(false);	

		_fontInstance = nullptr;
	}
	virtual ~Font() {
		if (_name)
			delete[] _name;	

		if (_fontInstance)
			DeleteObject(_fontInstance);	
	}
};
// eof Font.h

// Item.h

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class Item {
	HWND _self;

	LPWSTR _classname;
	LPWSTR _title;

	DWORD _style;

	Vector2<int> _position;
	Vector2<int> _size;

	bool _border;
	bool _visible;
	bool _enabled;

	Font* _font;

	std::vector<Item*> _children;
protected:
	HWND GetSelf() { return _self; }
	void SetSelf(HWND self) { _self = self; }

	LPCWSTR GetClassname() { return _classname; }
	void SetClassname(LPCWSTR classname) {
		if (_classname)
			delete[] _classname;

		_classname = new WCHAR[wcslen(classname) + 1];
		wcscpy_s(_classname, wcslen(classname) + 1, classname);
	}

	LPCWSTR GetTitle() { return _title; }
	void SetTitle(LPCWSTR title) {
		if (_title)
			delete[] _title;

		_title = new WCHAR[wcslen(title) + 1];
		wcscpy_s(_title, wcslen(title) + 1, title);

		if (GetSelf())
			SetWindowText(GetSelf(), _title);
	}

	DWORD GetStyle() { return _style; }
	void SetStyle(DWORD style) { _style = style; }

	bool GetBorder() { return _border; }
	void SetBorder(bool border) { _border = border; }

public:
	decltype(_position) GetPosition() { return _position; }
	void SetPosition(decltype(_position) position) { _position = position; }

	decltype(_size) GetSize() { return _size; }
	void SetSize(decltype(_size) size) { _size = size; }

	bool GetVisible() { return _visible; }
	void SetVisible(bool visible) {
		_visible = visible;

		if(GetSelf())
			ShowWindow(GetSelf(), _visible ? SW_SHOWDEFAULT : SW_HIDE);
	}

	bool GetEnabled() { return _enabled; }
	void SetEnabled(bool enabled) {
		_enabled = enabled;

		if(GetSelf())
			EnableWindow(GetSelf(), _enabled);
	}

	Font* GetFont() { return _font; }
	void SetFont(Font* font) {
		_font = font;
		if (GetSelf()) {
			if (_font && !_font->_GetInstance()) {
				HDC hDC = GetDC(GetSelf());
				_font->_CreateInstance(hDC);
				ReleaseDC(GetSelf(), hDC);
			}

			SendMessage(GetSelf(), WM_SETFONT, _font ? (WPARAM)_font->_GetInstance() : NULL, (LPARAM)MAKELONG(TRUE, 0));
		}
	}

	bool IsSame(HWND hWnd) { return _self == hWnd; }
	bool Create(Item* parent) { return Create(NULL, parent); }

public:
	Item() {
		SetSelf(nullptr);

		SetClassname(L"");
		SetTitle(L"");

		SetStyle(0);

		SetBorder(false);
		SetVisible(true);
		SetEnabled(true);

		_font = nullptr;
	}
	virtual ~Item() {
		if (_self)
			DestroyWindow(_self);

		if (_classname)
			delete[] _classname;

		if (_title)
			delete[] _title;
	}

protected:
	virtual bool BeforeCreate(Item* parent) = 0; // Before HWND self is set
	bool Create(HINSTANCE hInstance, Item* parent) {
		if (!RegisterControls())
			return false;

		if ((hInstance && parent) || (!hInstance && !parent))
			return false;

		if (!BeforeCreate(parent))
			return false;

		SetSelf(CreateWindowEx(GetBorder() ? WS_EX_CLIENTEDGE : NULL, GetClassname(), GetTitle(), GetStyle(),
			GetPosition().x, GetPosition().y, GetSize().x, GetSize().y, parent ? parent->GetSelf() : NULL, NULL, hInstance, NULL));

		if (!GetSelf())
			return false;

		SetVisible(GetVisible());
		SetEnabled(GetEnabled());
		SetFont(_font);

		if (!AfterCreate())
			return false;

		if (parent)
			parent->RegisterChild(this);

		return true;
	}
	virtual bool AfterCreate() = 0; // After HWND self is set

	virtual bool OnMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		for (Item* child : _children)
		{
			if (child->OnMessage(hWnd, message, wParam, lParam))
				return true;
		}

		return false;
	}

private:
	virtual void RegisterChild(Item* child) {
		_children.push_back(child);
	}

	static bool RegisterControls() {
		static bool registered = false;
		if (registered)
			return registered;

		INITCOMMONCONTROLSEX icex;
		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_STANDARD_CLASSES;
		if (!InitCommonControlsEx(&icex))
			return false;

		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_UPDOWN_CLASS;
		if (!InitCommonControlsEx(&icex))
			return false;

		registered = true;
		return registered;
	}
};
// eof Item.h

// Button.h

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class Button : public Item {
public:
	LPCWSTR GetText() { return GetTitle(); }
	void SetText(LPCWSTR str) { SetTitle(str); }

	Button() {
		SetClassname(L"BUTTON");
		SetStyle(WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON);
	}
	virtual ~Button() {}
	
private:
	virtual bool BeforeCreate(Item* parent) override { return true; }
	virtual bool AfterCreate() override { return true; }
};
// eof Button.h

// Checkbox.h

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class Checkbox : public Item {
	bool _checked;
public:

	LPCWSTR GetText() { return GetTitle(); }
	void SetText(LPCWSTR str) { SetTitle(str); }

	bool GetCheck() {
		if (GetSelf() != nullptr)
			_checked = SendMessage(GetSelf(), BM_GETCHECK, 0, 0);

		return _checked;
	}
	void SetCheck(bool checked) {
		_checked = checked;
		
		if (GetSelf() != nullptr)
			SendMessage(GetSelf(), BM_SETCHECK, (WPARAM)_checked, 0);
	}
	
public:
	Checkbox() {
		SetClassname(L"BUTTON");
		SetStyle(WS_VISIBLE | WS_CHILD | BS_CHECKBOX);

		SetCheck(false);		

		OnClick = nullptr;
	}
	virtual ~Checkbox() {}	
	
	void (*OnClick)(bool);
private:
	virtual bool BeforeCreate(Item* parent) override { return true; }
	virtual bool AfterCreate() override { 
		SetCheck(_checked);

		return true;
	}

	virtual bool OnMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override {
		if (message != WM_COMMAND)
			return false;

		if (HIWORD(wParam) != BN_CLICKED)
			return false;

		HWND control = (HWND)lParam;
		if (control != GetSelf())
			return false;

		SetCheck(!GetCheck());

		if(OnClick)
			OnClick(GetCheck());

		return true;
	}
};
// eof Checkbox.h

// ComboBox.h

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class ComboBox : public Item {
	std::vector<LPCWSTR> _content; // Contains a copy of the combobox items, at the cost of a little bit more memory usage
	int _selection;

	void ClearContent() {
		for(auto it = _content.begin(); it != _content.end(); ++it)
			delete[] *it;

		_content.clear();		
	}

	void AddStringToWin32Component(LPCWSTR string) {
		if (GetSelf()) {
			if (static_cast<int>(SendMessage(GetSelf(), CB_GETCOUNT, 0, 0)) == 0)
				SetWindowText(GetSelf(), string);

			SendMessage(GetSelf(), CB_ADDSTRING, 0, (LPARAM)string);
		}		
	}
public:
	LPCWSTR GetString(int index) {
		if(index < 0 || index >= static_cast<int>(_content.size()))
			return nullptr;
		
		return _content[index];
	}
	void AddString(LPCWSTR string) {
		WCHAR* output = new WCHAR[wcslen(string) + 1];
		wcscpy_s(output, wcslen(string) + 1, string);
			
		AddStringToWin32Component(output);

		_content.push_back(output);
	}

	int GetSelection() { return _selection; }
	void SetSelection(int index) {
		_selection = index;
		
		if (GetSelf())
			SendMessage(GetSelf(), CB_SETCURSEL, (WPARAM)_selection, 0);
	}

	int GetCount() { return static_cast<int>(_content.size()); }
		
	ComboBox() {
		SetClassname(L"COMBOBOX");
		SetStyle(WS_VISIBLE | WS_CHILD | WS_OVERLAPPED | WS_VSCROLL | CBS_DROPDOWN | CBS_HASSTRINGS);

		_selection = 0;
	}
	virtual ~ComboBox() {
		ClearContent();
	}
	
private:
	virtual bool BeforeCreate(Item* parent) override { return true; }
	bool AfterCreate() override {
		for (auto it = _content.begin(); it != _content.end(); ++it)
			AddStringToWin32Component(*it);

		if (_selection >= 0 && _selection < GetCount())
			SetSelection(_selection);

		return true;
	}	
};
// eof ComboBox.h

// TextBox.h

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

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
	LPWSTR text;
	TextAlignment textAlignment;

	void ClearText() {
		if (text) {
			delete[] text;
			text = nullptr;
		}
	}

public:
	LPCWSTR GetText() {
		if (GetSelf()) {
			ClearText();

			int length = static_cast<int>(SendMessage(GetSelf(), WM_GETTEXTLENGTH, 0, 0)) + 1;
			text = new WCHAR[length];
			SendMessage(GetSelf(), WM_GETTEXT, length, (LPARAM)text);
		}

		return text;
	}
	void SetText(LPCWSTR string) {
		if (GetSelf()) {
			SendMessage(GetSelf(), WM_SETTEXT, 0, (LPARAM)string);
		} 
		else {
			ClearText();

			text = new WCHAR[wcslen(string) + 1];
			wcscpy_s(text, wcslen(string) + 1, string);
		}
	}
	void AppendText(LPCWSTR string) {
		LPCWSTR currentText = GetText();

		size_t appendedLength = wcslen(currentText) + wcslen(string) + 1;
		WCHAR* appended = new WCHAR[appendedLength];
		wcscpy_s(appended, appendedLength, currentText);
		wcscat_s(appended, appendedLength, (WCHAR*)string);
		appended[appendedLength - 1] = 0;

		SetText(appended);
		delete[] appended;
	}

	bool GetMultiLine() { return multiLine; }
	void SetMultiLine(bool b) { multiLine = b; }

	bool GetVerticalScroll() { return verticalScroll; }
	void SetVerticalScroll(bool b) { verticalScroll = b; }

	bool GetReadOnly() { return readOnly; }
	void SetReadOnly(bool b) {
		readOnly = b;

		if (GetSelf())
			SendMessage(GetSelf(), EM_SETREADONLY, readOnly, 0);
	}

	TextAlignment GetTextAlignment() { return textAlignment; }
	void SetTextAlignment(TextAlignment ta) { textAlignment = ta; }

	void FocusBottom() {
		SendMessage(GetSelf(), EM_SETSEL, 0, -1); // Select
		SendMessage(GetSelf(), EM_SETSEL, -1, -1); // Unselect
		SendMessage(GetSelf(), EM_SCROLLCARET, 0, 0); // Set caret		
	}

	const LPCWSTR GetNewLine() { return L"\r\n"; }

	TextBox() {
		SetClassname(L"EDIT");
		SetStyle(WS_VISIBLE | WS_CHILD | ES_LEFT | ES_AUTOVSCROLL);
		SetBorder(true);

		SetMultiLine(false);
		SetVerticalScroll(false);
		SetReadOnly(false);

		text = nullptr;
		textAlignment = ALIGNLEFT;
	}
	virtual ~TextBox() {
		ClearText();
	}

private:
	bool BeforeCreate(Item* parent) override {
		DWORD dwStyle = WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL;
		if (multiLine)
			dwStyle |= ES_MULTILINE;
		if (verticalScroll)
			dwStyle |= WS_VSCROLL;
		if (readOnly)
			dwStyle |= ES_READONLY;

		if (textAlignment == ALIGNCENTER)
			dwStyle |= ES_CENTER;
		else if (textAlignment == ALIGNRIGHT)
			dwStyle |= ES_RIGHT;
		else
			dwStyle |= ES_LEFT;

		SetStyle(dwStyle);
		return true;
	}
	bool AfterCreate() override {
		if (text)
			SetText(text);

		return true;
	}
};
// eof TextBox.h

// TextLabel.h

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

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
	LPCWSTR GetText() { return GetTitle(); }
	void SetText(LPCWSTR t) { SetTitle(t); }

	bool GetSunken() { return sunken; }
	void SetSunken(bool b) { sunken = b; }

	TextAlignment GetTextAlignment() { return textAlignment; }
	void SetTextAlignment(TextAlignment ta) { textAlignment = ta; }

	TextLabel() {
		SetClassname(L"STATIC");
		SetStyle(WS_VISIBLE | WS_CHILD);

		sunken = false;
		textAlignment = ALIGNLEFT;
	}
	virtual ~TextLabel() {}	
	
private:
	virtual bool BeforeCreate(Item* parent) override {
		if(sunken)
			SetStyle(GetStyle() | SS_SUNKEN);

		if (textAlignment == ALIGNRIGHT)
			SetStyle(GetStyle() | SS_RIGHT);
		else if (textAlignment == ALIGNCENTER)
			SetStyle(GetStyle() | SS_CENTER);
		else
			SetStyle(GetStyle() | SS_LEFT);

		return true;
	}
	virtual bool AfterCreate() override {
		return true;
	}
};
// eof TextLabel.h

// Window.h

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class Window : public Item {
	bool _resizable;
	bool _minimizable;
	bool _maximizable;

	HINSTANCE _hInstance;
	int _cmdShow;

public:
	bool GetResizable() { return _resizable; }
	void SetResizable(bool resizable) { _resizable = resizable; }

	bool GetMinimizable() { return _minimizable; }
	void SetMinimizable(bool minimizable) { _minimizable = minimizable; }

	bool GetMaximizable() { return _maximizable; }
	void SetMaximizable(bool maximizable) { _maximizable = maximizable; }

	Window() {
		_resizable = true;
		_minimizable = true;
		_maximizable = true;

		_hInstance = GetModuleHandle(NULL);
		_cmdShow = SW_SHOWDEFAULT;
	}
	virtual ~Window() {
		SetWindowLongPtr(GetSelf(), 0, (LONG)nullptr);
	}

private:
	bool BeforeCreate(Item* parent) override {
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = Window::StaticProcessMessage;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(Window*); // For 'this' pointer in StaticProcedure
		wcex.hInstance = _hInstance;
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = GetClassname();
		wcex.hIconSm = NULL;

		RegisterClassExW(&wcex);

		DWORD windowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
		if (_resizable)
			windowStyle |= WS_THICKFRAME;
		if (_minimizable)
			windowStyle |= WS_MINIMIZEBOX;
		if (_maximizable)
			windowStyle |= WS_MAXIMIZEBOX;

		SetStyle(windowStyle);
		return true;
	}
	bool AfterCreate() override {
		SetWindowLongPtr(GetSelf(), 0, (LONG_PTR)this);

		ShowWindow(GetSelf(), _cmdShow);
		UpdateWindow(GetSelf());
		return true;
	}

public:
	bool Create(HINSTANCE hInst, int nCmdShow) {
		_hInstance = hInst;
		_cmdShow = nCmdShow;

		return Item::Create(_hInstance, NULL);
	}
	virtual bool Initialize() {
		if (!GetSelf())
			return false;

		return true;
	}
	virtual bool Update() {
		if (!GetSelf())
			return false;

		return true;
	}

protected:
	virtual bool OnMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override {
		switch (message) {
			case WM_DESTROY:
				PostQuitMessage(0);
				return true;
		}

		return Item::OnMessage(hWnd, message, wParam, lParam);
	}

private:
	LRESULT CALLBACK ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
		if (OnMessage(hWnd, message, wParam, lParam))
			return 0;

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	static LRESULT CALLBACK StaticProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		Window* window = (Window*)GetWindowLongPtr(hWnd, 0);
		if (!window)
			return DefWindowProc(hWnd, message, wParam, lParam);
		else
			return window->ProcessMessage(hWnd, message, wParam, lParam);
	}
};
// eof Window.h

// NumericBox.h

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class NumericBox : public Item {
	TextBox* textBox;
	int min;
	int max;
	int preSelection;

public:
	int GetMin() { return min; }
	void SetMin(int value) {
		min = value;

		if (GetSelf())
			SendMessage(GetSelf(), UDM_SETRANGE32, min, max);
	}

	int GetMax() { return max; }
	void SetMax(int value) {
		max = value;

		if (GetSelf())
			SendMessage(GetSelf(), UDM_SETRANGE32, min, max);
	}

	int GetSelection() {
		if (!GetSelf())
			return preSelection;

		return (int)SendMessage(GetSelf(), UDM_GETPOS32, 0, 0);
	}
	void SetSelection(int value) {
		if (!GetSelf())
			preSelection = value;
		else
			SendMessage(GetSelf(), UDM_SETPOS32, 0, value);
	}

	NumericBox() {
		SetClassname(L"msctls_updown32");
		SetStyle(WS_VISIBLE | WS_CHILD | UDS_AUTOBUDDY | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK);

		textBox = nullptr;

		min = 0;
		max = 100;
		preSelection = 0;
	}
	virtual ~NumericBox() {
		if (textBox)
			delete textBox;
	}
	
private:
	/*
		Creates a Text Box before the Up Down Control is made
		The Up Down Control will bind to this Text Box
	*/
	virtual bool BeforeCreate(Item* parent) override {
		textBox = new TextBox();
		textBox->SetPosition(GetPosition());
		textBox->SetSize(GetSize());
		textBox->SetReadOnly(true);
		textBox->SetTextAlignment(TextBox::ALIGNCENTER);

		return textBox->Create(parent);
	}
	virtual bool AfterCreate() override {
		SetMin(GetMin());
		SetMax(GetMax());

		SetSelection(preSelection);

		return true;
	}
};
// eof NumericBox.h

}

#endif
