#include "stdafx.h"
#include "Communication.h"

static std::vector<std::string> storedMessages;
static std::mutex storedMessageLock;

namespace ClickerLib {
	void StoreMessage(std::string message)
	{
		storedMessageLock.lock();
		storedMessages.push_back(message);
		storedMessageLock.unlock();
	}

	std::vector<std::string> RetrieveMessages()
	{
		decltype(storedMessages) retn;

		storedMessageLock.lock();
		retn.swap(storedMessages);
		storedMessageLock.unlock();

		return retn;
	}

	static std::atomic<bool> shutdownRequested = false;
	void RequestShutdown()
	{
		shutdownRequested = true;
	}

	bool ShutdownRequestReceived()
	{
		return shutdownRequested;
	}
}