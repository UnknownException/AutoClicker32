#include "stdafx.h"
#include "ClickerWindow.h"

ClickerWindow::ClickerWindow()
{
	SetClassname(L"ClickerWindow");
	SetTitle(L"AutoClicker32");

	/* Checkbox */
	cbLockPosition = nullptr;
	cbFakeMovement = nullptr;
	cbRandomizeDelay = nullptr;
	cbApplicationLock = nullptr;
	cbRemoveKeyFlag = nullptr;
	cbReleaseDelay = nullptr;

	/* Text Box */
	tbInformation = nullptr;

	/* Combo Box */
	cmbActionKey = nullptr;
	cmbEmergencyKey = nullptr;

	/* Numeric Box */
	nbDelay = nullptr;

	/* Text Label */
	tlDelay = nullptr;
	tlActionKey = nullptr;
	tlEmergencyKey = nullptr;
	tlWarning = nullptr;
}

ClickerWindow::~ClickerWindow()
{
	/* Checkbox */
	if (cbLockPosition)
		delete cbLockPosition;

	if (cbFakeMovement)
		delete cbFakeMovement;

	if (cbRandomizeDelay)
		delete cbRandomizeDelay;

	if (cbApplicationLock)
		delete cbApplicationLock;

	if (cbRemoveKeyFlag)
		delete cbRemoveKeyFlag;

	if (cbReleaseDelay)
		delete cbReleaseDelay;

	/* Text Box */
	if (tbInformation)
		delete tbInformation;

	/* Combo Box */
	if (cmbActionKey)
		delete cmbActionKey;

	if (cmbEmergencyKey)
		delete cmbEmergencyKey;

	/* Numeric Box */
	if (nbDelay)
		delete nbDelay;
	
	/* Text Label */
	if (tlDelay)
		delete tlDelay;

	if (tlActionKey)
		delete tlActionKey;

	if (tlEmergencyKey)
		delete tlEmergencyKey;

	if (tlWarning)
		delete tlWarning;
}

bool ClickerWindow::Initialize()
{
	if (!Window::Initialize())
		return false;

	/* Checkbox */
	cbLockPosition = new Checkbox();
	cbLockPosition->SetParent(GetSelf());
	cbLockPosition->SetPosition(Vector2<int>(4, 60));
	cbLockPosition->SetSize(Vector2<int>(140, 20));
	cbLockPosition->SetText(L"Lock Position");
	cbLockPosition->SetCheck(ClickerLib::GetMousePositionLock());
	cbLockPosition->Create();

	cbFakeMovement = new Checkbox();
	cbFakeMovement->SetParent(GetSelf());
	cbFakeMovement->SetPosition(Vector2<int>(4, 80));
	cbFakeMovement->SetSize(Vector2<int>(140, 20));
	cbFakeMovement->SetText(L"Fake Movement");
	cbFakeMovement->SetCheck(ClickerLib::GetFakeMouseMovement());
	cbFakeMovement->Create();

	cbRandomizeDelay = new Checkbox();
	cbRandomizeDelay->SetParent(GetSelf());
	cbRandomizeDelay->SetPosition(Vector2<int>(4, 100));
	cbRandomizeDelay->SetSize(Vector2<int>(140, 20));
	cbRandomizeDelay->SetText(L"Randomize Delay");
	cbRandomizeDelay->SetCheck(ClickerLib::GetDelayRandomizer());
	cbRandomizeDelay->Create();

	cbApplicationLock = new Checkbox();
	cbApplicationLock->SetParent(GetSelf());
	cbApplicationLock->SetPosition(Vector2<int>(4, 120));
	cbApplicationLock->SetSize(Vector2<int>(140, 20));
	cbApplicationLock->SetText(L"Application Lock");
	cbApplicationLock->SetCheck(ClickerLib::GetApplicationLock());
	cbApplicationLock->Create();

	cbRemoveKeyFlag = new Checkbox();
	cbRemoveKeyFlag->SetParent(GetSelf());
	cbRemoveKeyFlag->SetPosition(Vector2<int>(4, 140));
	cbRemoveKeyFlag->SetSize(Vector2<int>(140, 20));
	cbRemoveKeyFlag->SetText(L"Remove Key Flag");
	cbRemoveKeyFlag->SetCheck(ClickerLib::GetRemoveKeyFlag());
	cbRemoveKeyFlag->Create();

	cbReleaseDelay = new Checkbox();
	cbReleaseDelay->SetParent(GetSelf());
	cbReleaseDelay->SetPosition(Vector2<int>(4, 160));
	cbReleaseDelay->SetSize(Vector2<int>(140, 20));
	cbReleaseDelay->SetText(L"Release Delay");
	cbReleaseDelay->SetCheck(ClickerLib::GetReleaseDelay());
	cbReleaseDelay->Create();

	/* Text Box*/
	tbInformation = new TextBox();
	tbInformation->SetParent(GetSelf());
	tbInformation->SetPosition(Vector2<int>(168, 60));
	tbInformation->SetSize(Vector2<int>(324, 120));
	tbInformation->SetMultiLine(true);
	tbInformation->SetVerticalScroll(true);
	tbInformation->SetText(L"AutoClicker32 - Release N/A\nhttps://github.com/UnknownException/AutoClicker32");
	tbInformation->SetReadOnly(true);
	tbInformation->Create();

	/* Combo Box */
	cmbActionKey = new ComboBox();
	cmbActionKey->SetParent(GetSelf());
	cmbActionKey->SetPosition(Vector2<int>(168, 26));
	cmbActionKey->SetSize(Vector2<int>(160, 24));

	auto keyList = ClickerLib::GetAvailableKeys();
	for (auto it = keyList.begin(); it != keyList.end(); ++it)
	{
		std::string keyName = (*it).keyName;
		wchar_t* wStringBuffer = new wchar_t[keyName.length() + 1];
		MultiByteToWideChar(CP_ACP, 0, keyName.c_str(), -1, wStringBuffer, keyName.length() + 1);

		cmbActionKey->AddString(LPCWSTR(wStringBuffer));

		delete[] wStringBuffer;
	}

	cmbActionKey->SetSelection(0);
	cmbActionKey->Create();

	cmbEmergencyKey = new ComboBox();
	cmbEmergencyKey->SetParent(GetSelf());
	cmbEmergencyKey->SetPosition(Vector2<int>(332, 26));
	cmbEmergencyKey->SetSize(Vector2<int>(160, 24));

	for (auto it = keyList.begin(); it != keyList.end(); ++it)
	{
		std::string keyName = (*it).keyName;
		wchar_t* wStringBuffer = new wchar_t[keyName.length() + 1];
		MultiByteToWideChar(CP_ACP, 0, keyName.c_str(), -1, wStringBuffer, keyName.length() + 1);

		cmbEmergencyKey->AddString(LPCWSTR(wStringBuffer));

		delete[] wStringBuffer;
	}

	cmbEmergencyKey->SetSelection(1);
	cmbEmergencyKey->Create();

	/* Numeric Box */
	nbDelay = new NumericBox();
	nbDelay->SetParent(GetSelf());
	nbDelay->SetPosition(Vector2<int>(4, 26));
	nbDelay->SetSize(Vector2<int>(160, 24));
//	nbDelay->SetText(L"20MS");
	nbDelay->Create();

	/* Text Label */
	tlDelay = new TextLabel();
	tlDelay->SetParent(GetSelf());
	tlDelay->SetPosition(Vector2<int>(4, 6));
	tlDelay->SetSize(Vector2<int>(160, 20));
	tlDelay->SetText(L"Delay");
	tlDelay->Create();

	tlActionKey = new TextLabel();
	tlActionKey->SetParent(GetSelf());
	tlActionKey->SetPosition(Vector2<int>(168, 6));
	tlActionKey->SetSize(Vector2<int>(160, 20));
	tlActionKey->SetText(L"Action Key");
	tlActionKey->Create();

	tlEmergencyKey = new TextLabel();
	tlEmergencyKey->SetParent(GetSelf());
	tlEmergencyKey->SetPosition(Vector2<int>(332, 6));
	tlEmergencyKey->SetSize(Vector2<int>(160, 20));
	tlEmergencyKey->SetText(L"Emergency Key");
	tlEmergencyKey->Create();

	tlWarning = new TextLabel();
	tlWarning->SetParent(GetSelf());
	tlWarning->SetPosition(Vector2<int>(4, 190));
	tlWarning->SetSize(Vector2<int>(488, 24));
	tlWarning->SetText(L"Open this application before the target application when using remove key flag");
	tlWarning->SetSunken(true);
	tlWarning->Create();

	return true;
}

bool ClickerWindow::Update()
{
	if (!Window::Update())
		return false;

	std::vector<std::string> messages = ClickerLib::RetrieveMessages();
	for (auto it = messages.begin(); it != messages.end(); ++it)
	{
		tbInformation->AppendText(tbInformation->GetNewLine());

		wchar_t* wStringBuffer = new wchar_t[(*it).length() + 1];
		MultiByteToWideChar(CP_ACP, 0, (*it).c_str(), -1, wStringBuffer, (*it).length() + 1);
		tbInformation->AppendText(wStringBuffer);
		delete[] wStringBuffer;

		tbInformation->FocusBottom();
	}

	return true;
}

LRESULT CALLBACK ClickerWindow::Procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND:
		{
			switch (HIWORD(wParam))
			{
				case BN_CLICKED:
				{
					HWND control = (HWND)lParam;
					if (cbLockPosition->IsSame(control))
					{
						ClickerLib::SetMousePositionLock(!ClickerLib::GetMousePositionLock());
						cbLockPosition->SetCheck(ClickerLib::GetMousePositionLock());
					}
					else if (cbFakeMovement->IsSame(control))
					{
						ClickerLib::SetFakeMouseMovement(!ClickerLib::GetFakeMouseMovement());
						cbFakeMovement->SetCheck(ClickerLib::GetFakeMouseMovement());
					}
					else if (cbRandomizeDelay->IsSame(control))
					{
						ClickerLib::SetDelayRandomizer(!ClickerLib::GetDelayRandomizer());
						cbRandomizeDelay->SetCheck(ClickerLib::GetDelayRandomizer());
					}
					else if (cbApplicationLock->IsSame(control))
					{
						ClickerLib::SetApplicationLock(!ClickerLib::GetApplicationLock());
						cbApplicationLock->SetCheck(ClickerLib::GetApplicationLock());
					}
					else if (cbRemoveKeyFlag->IsSame(control))
					{
						ClickerLib::SetRemoveKeyFlag(!ClickerLib::GetRemoveKeyFlag());
						cbRemoveKeyFlag->SetCheck(ClickerLib::GetRemoveKeyFlag());
					}
					else if (cbReleaseDelay->IsSame(control))
					{
						ClickerLib::SetReleaseDelay(!ClickerLib::GetReleaseDelay());
						cbReleaseDelay->SetCheck(ClickerLib::GetReleaseDelay());
					}
					else
					{
						break;
					}

					return 0;
				}
				case CBN_SELENDOK:
				{
					HWND control = (HWND)lParam;

					if (cmbActionKey->IsSame(control))
						HandleActionKey();
					else if (cmbEmergencyKey->IsSame(control))
						HandleEmergencyKey();
					else
						break;

					return 0;

				}
				default:
					break;
			}
		}
		break;
		case WM_NOTIFY:
		{
			switch (((LPNMHDR)lParam)->code)
			{
				case UDN_DELTAPOS:
				{
					HWND control = ((LPNMHDR)lParam)->hwndFrom;
					if (nbDelay->IsSame(control))
						HandleDelay();
					else
						break;

					return 0;
				}
				default:
					break;
			}
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...
			EndPaint(hWnd, &ps);

			return 0;
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool ClickerWindow::HandleActionKey()
{
	auto keyList = ClickerLib::GetAvailableKeys();
	if (cmbActionKey->GetSelection() < 0 || cmbActionKey->GetSelection() >= static_cast<int>(keyList.size()))
	{
		ClickerLib::StoreMessage("ActionKey selection out of availablekey bounds");
		return false;
	}

	/* Swap Keys */
	if (cmbActionKey->GetSelection() == cmbEmergencyKey->GetSelection())
	{
		for (unsigned int i = 0; i < keyList.size(); ++i)
		{
			if (keyList[i].vKey == ClickerLib::GetActionKey())
			{
				ClickerLib::SetEmergencyKey(keyList[i].vKey);
				cmbEmergencyKey->SetSelection(i);

				break;
			}
		}
	}

	ClickerLib::SetActionKey(keyList[cmbActionKey->GetSelection()].vKey);

	return true;
}

bool ClickerWindow::HandleEmergencyKey()
{
	auto keyList = ClickerLib::GetAvailableKeys();
	if (cmbEmergencyKey->GetSelection() < 0 || cmbEmergencyKey->GetSelection() >= static_cast<int>(keyList.size()))
	{
		ClickerLib::StoreMessage("EmergencyKey selection out of availablekey bounds");
		return false;
	}

	/* Swap Keys */
	if (cmbEmergencyKey->GetSelection() == cmbActionKey->GetSelection())
	{
		for (unsigned int i = 0; i < keyList.size(); ++i)
		{
			if (keyList[i].vKey == ClickerLib::GetEmergencyKey())
			{
				ClickerLib::SetActionKey(keyList[i].vKey);
				cmbActionKey->SetSelection(i);

				break;
			}
		}
	}

	ClickerLib::SetEmergencyKey(keyList[cmbEmergencyKey->GetSelection()].vKey);

	return true;
}

bool ClickerWindow::HandleDelay()
{
	return true;
}