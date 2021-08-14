#pragma once

class ClickerWindow : public Window{
	Font* fntDefault;

	Checkbox* cbLockPosition;
	Checkbox* cbFakeMovement;
	Checkbox* cbRandomizeDelay;
	Checkbox* cbApplicationLock;
	Checkbox* cbRemoveKeyFlag;
	Checkbox* cbReleaseDelay;

	TextBox* tbInformation;

	ComboBox* cmbActionKey;
	ComboBox* cmbEmergencyKey;

	NumericBox* nbDelay;

	TextLabel* tlDelay;
	TextLabel* tlActionKey;
	TextLabel* tlEmergencyKey;
	TextLabel* tlWarning;
public:
	ClickerWindow();
	virtual ~ClickerWindow();

	bool Initialize() override;
	bool Update() override;

protected:
	virtual bool OnMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	bool HandleActionKey();
	bool HandleEmergencyKey();
	bool HandleDelay(int delay);
};