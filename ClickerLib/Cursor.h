#pragma once

namespace ClickerLib {
	class Cursor {
	public:
		Cursor();
		virtual ~Cursor();

		void SetPosition(Vector2<int> position);
		Vector2<int> GetPosition();

	private:
		void MouseInput(DWORD buttonFlag);
	public:
		void LeftButtonDown();
		void LeftButtonUp();
	};
}