#include "stdafx.h"
#include "Settings.h"

namespace ClickerLib {
	static std::atomic<unsigned int> clickDelay = 20;
	unsigned int GetClickDelay()
	{
		return clickDelay;
	}

	void SetClickDelay(unsigned int delay)
	{
		clickDelay = delay;
	}
	
	std::vector<ClickerKey> GetAvailableKeys()
	{
		static std::vector<ClickerKey> keyList;
		if (!keyList.empty())
			return keyList;

		keyList.push_back(ClickerKey(VK_SPACE, "Spacebar"));
		keyList.push_back(ClickerKey(VK_ESCAPE, "Escape (ESC)"));
		keyList.push_back(ClickerKey(VK_LSHIFT, "Left Shift"));
		keyList.push_back(ClickerKey(VK_LSHIFT, "Right Shift"));
		keyList.push_back(ClickerKey(VK_LCONTROL, "Left Control (CTRL)"));
		keyList.push_back(ClickerKey(VK_RCONTROL, "Right Control (CTRL)"));
		keyList.push_back(ClickerKey(VK_LEFT, "Left"));
		keyList.push_back(ClickerKey(VK_RIGHT, "Right"));
		keyList.push_back(ClickerKey(VK_UP, "Up"));
		keyList.push_back(ClickerKey(VK_DOWN, "Down"));
		keyList.push_back(ClickerKey(VK_DELETE, "Delete"));
		keyList.push_back(ClickerKey(VK_HOME, "Home"));
		keyList.push_back(ClickerKey(VK_END, "End"));
		keyList.push_back(ClickerKey(VK_F1, "F1"));
		keyList.push_back(ClickerKey(VK_F2, "F2"));
		keyList.push_back(ClickerKey(VK_F3, "F3"));
		keyList.push_back(ClickerKey(VK_F4, "F4"));
		keyList.push_back(ClickerKey(VK_F5, "F5"));
		keyList.push_back(ClickerKey(VK_F6, "F6"));
		keyList.push_back(ClickerKey(VK_F7, "F7"));
		keyList.push_back(ClickerKey(VK_F8, "F8"));
		keyList.push_back(ClickerKey(VK_F9, "F9"));
		keyList.push_back(ClickerKey(VK_F10, "F10"));
		keyList.push_back(ClickerKey(VK_F11, "F11"));
		keyList.push_back(ClickerKey(VK_F12, "F12"));

		return keyList;
	}

	static std::atomic<int> actionKey = VK_SPACE;
	int GetActionKey()
	{
		return actionKey;
	}

	void SetActionKey(int key)
	{
		actionKey = key;
	}

	static std::atomic<int> emergencyKey = VK_ESCAPE;
	int GetEmergencyKey()
	{
		return emergencyKey;
	}

	void SetEmergencyKey(int key)
	{
		emergencyKey = key;
	}

	static std::atomic<bool> lockMousePosition = true;
	bool GetMousePositionLock()
	{
		return lockMousePosition;
	}

	void SetMousePositionLock(bool b)
	{
		lockMousePosition = b;
	}

	static std::atomic<bool> fakeMouseMovement = true;
	bool GetFakeMouseMovement()
	{
		return fakeMouseMovement;
	}

	void SetFakeMouseMovement(bool b)
	{
		fakeMouseMovement = b;
	}

	static std::atomic<bool> applicationLock = true;
	bool GetApplicationLock()
	{
		return applicationLock;
	}
	
	void SetApplicationLock(bool b)
	{
		applicationLock = b;
	}

	static std::atomic<bool> delayRandomizer = true;
	bool GetDelayRandomizer()
	{
		return delayRandomizer;
	}

	void SetDelayRandomizer(bool b)
	{
		delayRandomizer = b;
	}

	static std::atomic<bool> releaseDelay = true;
	bool GetReleaseDelay()
	{
		return releaseDelay;
	}

	void SetReleaseDelay(bool b)
	{
		releaseDelay = b;
	}

	static HHOOK injectedFlagHook = nullptr;
	LRESULT CALLBACK MouseHookProcedure(int action, WPARAM wParam, LPARAM lParam)
	{
		if (action == HC_ACTION && (wParam == WM_LBUTTONDOWN || wParam == WM_LBUTTONUP))
		{
			MSLLHOOKSTRUCT* info = (MSLLHOOKSTRUCT*)lParam;
			if ((info->flags & LLMHF_INJECTED) == LLMHF_INJECTED)
				info->flags = 0;
		}

		return CallNextHookEx(injectedFlagHook, action, wParam, lParam);
	}

	bool GetRemoveKeyFlag()
	{
		return injectedFlagHook != nullptr;
	}

	void SetRemoveKeyFlag(bool b)
	{
		if (b && !injectedFlagHook)
		{
			injectedFlagHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProcedure, GetModuleHandle(NULL), NULL);
		}
		else if (!b && injectedFlagHook)
		{
			UnhookWindowsHookEx(injectedFlagHook);
			injectedFlagHook = nullptr;
		}
	}
}