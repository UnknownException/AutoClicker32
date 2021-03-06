#include "stdafx.h"
#include "ClickerWindow.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	ClickerWindow* clickerWindow = new ClickerWindow();
	clickerWindow->SetPosition(Vector2<int>(CW_USEDEFAULT, 0));
	clickerWindow->SetSize(Vector2<int>(512, 256));
	clickerWindow->SetResizable(false);
	clickerWindow->SetMaximizable(false);

	if (!clickerWindow->Create(hInstance, nCmdShow))
	{
		MessageBox(NULL, L"Failed to create application interface", L"Error", MB_ICONERROR);
		
		delete clickerWindow;
		return FALSE;
	}

	ClickerLib::Clicker* clicker = new ClickerLib::Clicker();
	clicker->Start();

	clickerWindow->Initialize();

	MSG msg;
	UINT_PTR timer = SetTimer(NULL, NULL, 250, NULL);
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		clickerWindow->Update();

		KillTimer(NULL, timer);
		if (ClickerLib::ShutdownRequestReceived())
			PostQuitMessage(0);
		else
			timer = SetTimer(NULL, NULL, 250, NULL);
	}

	clicker->Stop();
	delete clicker;

	delete clickerWindow;

	return (int) msg.wParam;
}