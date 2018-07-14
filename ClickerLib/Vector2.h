#pragma once

namespace ClickerLib {
	template <class T>
	struct Vector2
	{
		T x;
		T y;

		Vector2()
		{
			x = 0;
			y = 0;
		}

		Vector2(T _x, T _y)
		{
			x = _x;
			y = _y;
		}

		Vector2<T> operator+(const Vector2 val)
		{
			Vector2<T> result = *this;
			result.x += val.x;
			result.y += val.y;

			return result;
		}
	};
}