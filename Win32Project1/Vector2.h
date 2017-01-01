#pragma once
template <class T>
class Vector2
{
protected:
	T _x;
	T _y;

public:
	Vector2() {
		_x = 0;
		_y = 0;
	};
	Vector2(T x, T y) {
		_x = x;
		_y = y;
	};
	~Vector2() {};

	void x(T x)
	{
		_x = x;
	};

	void y(T y)
	{
		_y = y;
	};

	T x()
	{
		return _x;
	};

	T y()
	{
		return _y;
	};

	Vector2<T> operator+ (Vector2& rhs)
	{
		Vector2<T> result;

		result.x(_x + rhs.x());
		result.y(_y + rhs.y());

		return result;

	};
};
