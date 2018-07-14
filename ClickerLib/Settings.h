#pragma once

namespace ClickerLib {
	struct ClickerKey {
		int vKey;
		std::string keyName;

		ClickerKey(int key, std::string name) {
			vKey = key;
			keyName = name;
		}
	};

	/* Thread Safe */
	unsigned int GetClickDelay();
	void SetClickDelay(unsigned int delay);

	std::vector<ClickerKey> GetAvailableKeys();

	int GetActionKey();
	void SetActionKey(int key);

	int GetEmergencyKey();
	void SetEmergencyKey(int key);

	bool GetMousePositionLock();
	void SetMousePositionLock(bool b);

	bool GetFakeMouseMovement();
	void SetFakeMouseMovement(bool b);

	bool GetApplicationLock();
	void SetApplicationLock(bool b);

	bool GetDelayRandomizer();
	void SetDelayRandomizer(bool b);

	bool GetReleaseDelay();
	void SetReleaseDelay(bool b);

	/* Not Thread Safe */
	bool GetRemoveKeyFlag();
	void SetRemoveKeyFlag(bool b);
};