#pragma once

/*
	Thread Safe
*/

namespace ClickerLib {
	void StoreMessage(std::string message);
	std::vector<std::string> RetrieveMessages();

	void RequestShutdown();
	bool ShutdownRequestReceived();
}