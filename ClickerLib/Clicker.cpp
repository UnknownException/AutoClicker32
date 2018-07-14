#include "stdafx.h"
#include "Clicker.h"
#include "Settings.h"
#include "Communication.h"
#include "Cursor.h"

namespace ClickerLib {
	std::string GetWindowName()
	{
		HWND window = GetForegroundWindow();

		char buffer[256];
		GetWindowTextA(window, buffer, sizeof(buffer));

		return std::string(buffer);
	}

	Clicker::Clicker()
	{
		worker = nullptr;
		workerActive = false;

		SetRemoveKeyFlag(true);
	}

	Clicker::~Clicker()
	{
		Stop();

		SetRemoveKeyFlag(false);
	}

	void Clicker::WorkerThread()
	{
		Cursor* cursor = new Cursor();

		std::string applicationName = GetWindowName();

		bool clickerEnabled = false;
		std::string clickerWindow = "";
		Vector2<int> clickerPosition(0, 0);

		while (workerActive)
		{
			if (GetAsyncKeyState(GetEmergencyKey()))
			{
				workerActive = false;
				RequestShutdown();
				break;
			}

			if (GetAsyncKeyState(GetActionKey()))
			{
				clickerEnabled = !clickerEnabled;
				clickerWindow = GetWindowName();
				clickerPosition = cursor->GetPosition();

				if (clickerPosition.x < 0 || clickerPosition.y < 0)
				{
					StoreMessage("Invalid mouse position\n");
					clickerEnabled = false;
				}
				else if (strcmp(applicationName.c_str(), clickerWindow.c_str()) == 0)
				{
					StoreMessage("Can't enable clicker in this application\n");
					clickerEnabled = false;
				}
				else
				{
					char buffer[512];
					sprintf_s(buffer, sizeof(buffer), "%s for: %s\n", clickerEnabled ? "Enabled" : "Disabled", clickerWindow.c_str());
					StoreMessage(buffer);
				}

				Sleep(300);
			}

			if (GetApplicationLock())
			{
				if (clickerEnabled && strcmp(clickerWindow.c_str(), GetWindowName().c_str()) != 0)
				{
					clickerEnabled = false;
					StoreMessage("Disabling clicker to prevent clicking in another application\n");
				}
			}

			if (clickerEnabled)
			{
				Vector2<int> modifier;
				if (GetFakeMouseMovement())
				{
					if ((rand() % 100) > 90)
						modifier = Vector2<int>(-2 + rand() % 5, -2 + rand() % 5);
				}

				if(GetMousePositionLock())
					cursor->SetPosition(clickerPosition + modifier);

#ifndef _DEBUG
				cursor->LeftButtonDown();
#endif

				if (GetReleaseDelay())
				{
					DWORD sleepTime = rand() % 10 + 10;
					Sleep(sleepTime);
				}

				modifier = Vector2<int>(0, 0);
				if (GetFakeMouseMovement())
				{
					if ((rand() % 100) > 80)
						modifier = Vector2<int>(-1 + rand() % 3, -1 + rand() % 3);
				}

				if(GetMousePositionLock())
					cursor->SetPosition(clickerPosition + modifier);

#ifndef _DEBUG
				cursor->LeftButtonUp();
#endif
			}
			
			DWORD sleepTime = GetClickDelay();
			if(GetDelayRandomizer())
				sleepTime = rand() % 20 + sleepTime;

			Sleep(sleepTime);
		}

		delete cursor;
	}

	void Clicker::Start()
	{
		if (!worker)
		{
			worker = new std::thread(&Clicker::WorkerThread, this);
			workerActive = true;
		}
	}

	void Clicker::Stop()
	{
		workerActive = false;

		if (worker)
		{
			worker->join();

			delete worker;
			worker = nullptr;
		}
	}

	bool Clicker::IsActive()
	{
		return workerActive;
	}
}