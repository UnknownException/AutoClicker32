#include "stdafx.h"
#include "Cursor.h"

namespace ClickerLib {
	Cursor::Cursor()
	{
	}

	Cursor::~Cursor()
	{
	}

	Vector2<int> Cursor::GetPosition()
	{
		POINT p;
		if (!GetCursorPos(&p))
			return Vector2<int>(-1, -1);

		return Vector2<int>(p.x, p.y);
	}

	void Cursor::SetPosition(Vector2<int> position)
	{
		SetCursorPos(position.x, position.y);
	}

	void Cursor::MouseInput(DWORD buttonFlag)
	{
		INPUT mouseAction;
		ZeroMemory(&mouseAction, sizeof(INPUT));

		mouseAction.type = INPUT_MOUSE;
		mouseAction.mi.dwFlags = buttonFlag;

		SendInput(1, &mouseAction, sizeof(INPUT));
	}

	void Cursor::LeftButtonDown()
	{
		MouseInput(MOUSEEVENTF_LEFTDOWN);
	}

	void Cursor::LeftButtonUp()
	{
		MouseInput(MOUSEEVENTF_LEFTUP);
	}
}