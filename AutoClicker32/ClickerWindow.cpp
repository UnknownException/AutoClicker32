#include "stdafx.h"
#include "ClickerWindow.h"

ClickerWindow::ClickerWindow()
{
	SetClassname(L"ClickerWindow");
	SetTitle(L"AutoClicker32");

	/* Font */
	fntDefault = nullptr;

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
	/* Font */
	if (fntDefault)
		delete fntDefault;

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

	/* Font */
	fntDefault = new Font();
	fntDefault->SetName(L"Arial");
	fntDefault->SetSize(9);

	/* Checkbox */
	cbLockPosition = new Checkbox();
	cbLockPosition->SetPosition(Vector2<int>(4, 60));
	cbLockPosition->SetSize(Vector2<int>(140, 20));
	cbLockPosition->SetText(L"Lock Position");
	cbLockPosition->SetCheck(ClickerLib::GetMousePositionLock());
	cbLockPosition->SetFont(fntDefault);
	cbLockPosition->OnClick = [](bool checked) {
		ClickerLib::SetMousePositionLock(checked);
	};
	cbLockPosition->Create(this);

	
	cbFakeMovement = new Checkbox();
	cbFakeMovement->SetPosition(Vector2<int>(4, 80));
	cbFakeMovement->SetSize(Vector2<int>(140, 20));
	cbFakeMovement->SetText(L"Fake Movement");
	cbFakeMovement->SetCheck(ClickerLib::GetFakeMouseMovement());
	cbFakeMovement->SetFont(fntDefault);
	cbFakeMovement->OnClick = [](bool checked) {
		ClickerLib::SetFakeMouseMovement(checked);
	};
	cbFakeMovement->Create(this);

	cbRandomizeDelay = new Checkbox();
	cbRandomizeDelay->SetPosition(Vector2<int>(4, 100));
	cbRandomizeDelay->SetSize(Vector2<int>(140, 20));
	cbRandomizeDelay->SetText(L"Randomize Delay");
	cbRandomizeDelay->SetCheck(ClickerLib::GetDelayRandomizer());
	cbRandomizeDelay->SetFont(fntDefault);
	cbRandomizeDelay->OnClick = [](bool checked) {
		ClickerLib::SetDelayRandomizer(checked);
	};
	cbRandomizeDelay->Create(this);

	cbApplicationLock = new Checkbox();
	cbApplicationLock->SetPosition(Vector2<int>(4, 120));
	cbApplicationLock->SetSize(Vector2<int>(140, 20));
	cbApplicationLock->SetText(L"Application Lock");
	cbApplicationLock->SetCheck(ClickerLib::GetApplicationLock());
	cbApplicationLock->SetFont(fntDefault);
	cbApplicationLock->OnClick = [](bool checked) {
		ClickerLib::SetApplicationLock(checked);
	};
	cbApplicationLock->Create(this);

	cbRemoveKeyFlag = new Checkbox();
	cbRemoveKeyFlag->SetPosition(Vector2<int>(4, 140));
	cbRemoveKeyFlag->SetSize(Vector2<int>(140, 20));
	cbRemoveKeyFlag->SetText(L"Remove Key Flag");
	cbRemoveKeyFlag->SetCheck(ClickerLib::GetRemoveKeyFlag());
	cbRemoveKeyFlag->SetFont(fntDefault);
	cbRemoveKeyFlag->OnClick = [](bool checked) {
		ClickerLib::SetRemoveKeyFlag(checked);
	};
	cbRemoveKeyFlag->Create(this);

	cbReleaseDelay = new Checkbox();
	cbReleaseDelay->SetPosition(Vector2<int>(4, 160));
	cbReleaseDelay->SetSize(Vector2<int>(140, 20));
	cbReleaseDelay->SetText(L"Release Delay");
	cbReleaseDelay->SetCheck(ClickerLib::GetReleaseDelay());
	cbReleaseDelay->SetFont(fntDefault);
	cbReleaseDelay->OnClick = [](bool checked) {
		ClickerLib::SetReleaseDelay(checked);
	};
	cbReleaseDelay->Create(this);

	/* Text Box*/
	tbInformation = new TextBox();
	tbInformation->SetPosition(Vector2<int>(168, 60));
	tbInformation->SetSize(Vector2<int>(324, 120));
	tbInformation->SetMultiLine(true);
	tbInformation->SetVerticalScroll(true);
	tbInformation->SetText(L"AutoClicker32 - " __DATE__ "\nhttps://github.com/UnknownException/AutoClicker32");
	tbInformation->SetReadOnly(true);
	tbInformation->SetFont(fntDefault);
	tbInformation->Create(this);

	/* Combo Box */
	cmbActionKey = new ComboBox();
	cmbActionKey->SetPosition(Vector2<int>(168, 26));
	cmbActionKey->SetSize(Vector2<int>(160, 24));

	auto keyList = ClickerLib::GetAvailableKeys();
	for (auto it = keyList.begin(); it != keyList.end(); ++it)
	{
		std::string keyName = (*it).keyName;
		wchar_t* wStringBuffer = new wchar_t[keyName.length() + 1];
		MultiByteToWideChar(CP_ACP, 0, keyName.c_str(), -1, wStringBuffer, static_cast<int>(keyName.length() + 1));

		cmbActionKey->AddString(LPCWSTR(wStringBuffer));

		delete[] wStringBuffer;
	}

	cmbActionKey->SetSelection(0);
	cmbActionKey->SetFont(fntDefault);
	cmbActionKey->Create(this);

	cmbEmergencyKey = new ComboBox();
	cmbEmergencyKey->SetPosition(Vector2<int>(332, 26));
	cmbEmergencyKey->SetSize(Vector2<int>(160, 24));

	for (auto it = keyList.begin(); it != keyList.end(); ++it)
	{
		std::string keyName = (*it).keyName;
		wchar_t* wStringBuffer = new wchar_t[keyName.length() + 1];
		MultiByteToWideChar(CP_ACP, 0, keyName.c_str(), -1, wStringBuffer, static_cast<int>(keyName.length() + 1));

		cmbEmergencyKey->AddString(LPCWSTR(wStringBuffer));

		delete[] wStringBuffer;
	}

	cmbEmergencyKey->SetSelection(1);
	cmbEmergencyKey->SetFont(fntDefault);
	cmbEmergencyKey->Create(this);

	/* Numeric Box */
	nbDelay = new NumericBox();
	nbDelay->SetPosition(Vector2<int>(4, 26));
	nbDelay->SetSize(Vector2<int>(160, 24));
	nbDelay->SetMin(5);
	nbDelay->SetMax(2000);
	nbDelay->SetSelection(ClickerLib::GetClickDelay());
	nbDelay->Create(this);

	/* Text Label */
	tlDelay = new TextLabel();
	tlDelay->SetPosition(Vector2<int>(4, 6));
	tlDelay->SetSize(Vector2<int>(160, 20));
	tlDelay->SetText(L"Delay (ms)");
	tlDelay->SetTextAlignment(TextLabel::ALIGNCENTER);
	tlDelay->Create(this);

	tlActionKey = new TextLabel();
	tlActionKey->SetPosition(Vector2<int>(168, 6));
	tlActionKey->SetSize(Vector2<int>(160, 20));
	tlActionKey->SetText(L"Action Key");
	tlActionKey->SetTextAlignment(TextLabel::ALIGNCENTER);
	tlActionKey->Create(this);

	tlEmergencyKey = new TextLabel();
	tlEmergencyKey->SetPosition(Vector2<int>(332, 6));
	tlEmergencyKey->SetSize(Vector2<int>(160, 20));
	tlEmergencyKey->SetText(L"Emergency Key");
	tlEmergencyKey->SetTextAlignment(TextLabel::ALIGNCENTER);
	tlEmergencyKey->Create(this);

	tlWarning = new TextLabel();
	tlWarning->SetPosition(Vector2<int>(4, 190));
	tlWarning->SetSize(Vector2<int>(488, 24));
	tlWarning->SetText(L"Open this application before the target application when using remove key flag");
	tlWarning->SetTextAlignment(TextLabel::ALIGNCENTER);
	tlWarning->SetSunken(true);
	tlWarning->SetFont(fntDefault);
	tlWarning->Create(this);

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
		MultiByteToWideChar(CP_ACP, 0, (*it).c_str(), -1, wStringBuffer, static_cast<int>((*it).length() + 1));
		tbInformation->AppendText(wStringBuffer);
		delete[] wStringBuffer;

		tbInformation->FocusBottom();
	}

	return true;
}

bool ClickerWindow::OnMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND:
		{
			switch (HIWORD(wParam))
			{
				case CBN_SELENDOK:
				{
					HWND control = (HWND)lParam;

					if (cmbActionKey->IsSame(control))
						HandleActionKey();
					else if (cmbEmergencyKey->IsSame(control))
						HandleEmergencyKey();
					else
						break;

					return true;

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
						HandleDelay(((LPNMUPDOWN)lParam)->iPos + ((LPNMUPDOWN)lParam)->iDelta);
					else
						break;

					return true;
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

			return true;
		}
		break;
	}

	return Window::OnMessage(hWnd, message, wParam, lParam);
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

bool ClickerWindow::HandleDelay(int delay)
{
	if (delay < nbDelay->GetMin())
		delay = nbDelay->GetMin();
	else if (delay > nbDelay->GetMax())
		delay = nbDelay->GetMax();

	ClickerLib::SetClickDelay(delay);

	return true;
}