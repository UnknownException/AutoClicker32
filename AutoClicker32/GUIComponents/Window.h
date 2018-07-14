#pragma once
#include "Item.h"

class Window : public Item {
	bool resizable;
	bool minimizable;
	bool maximizable;

	HINSTANCE hInstance;
	int cmdShow;
public:
	Window();
	virtual ~Window();

public:
	bool GetResizable() { return resizable; }
	void SetResizable(bool b) { resizable = b; }

	bool GetMinimizable() { return minimizable; }
	void SetMinimizable(bool b) { minimizable = b; }

	bool GetMaximizable() { return maximizable; }
	void SetMaximizable(bool b) { maximizable = b; }

private:
	bool BeforeCreate() override;
	bool AfterCreate() override;

public:
	bool Create(HINSTANCE hInstance, int nCmdShow);
	virtual bool Initialize();
	virtual bool Update();

private:
	virtual LRESULT CALLBACK Procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK StaticProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};