#pragma once

namespace ClickerLib {
	class Clicker {
		std::thread* worker;
		std::atomic<bool> workerActive;
	public:
		Clicker();
		virtual ~Clicker();
	private:
		void WorkerThread();
	public:
		void Start();
		void Stop();
		bool IsActive();
	};
}