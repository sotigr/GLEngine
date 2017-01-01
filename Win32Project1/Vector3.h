#pragma once
#include "Vector2.h"
template <class T>
class Vector3 : public Vector2<T>
{
private:
	T _z;

public:
	Vector3() {
		_x = 0;
		_y = 0;
		_z = 0;
	};
	Vector3(T x, T y, T z) {
		_x = x;
		_y = y;
		_z = z;
	};
	~Vector3() {};

	void z(T z)
	{
		_z = z;
	};
	T z()
	{
		return _z;
	};
	Vector3<T> operator+ (Vector3& rhs)
	{
		Point3D<T> result;

		result.x(_x + rhs.x());
		result.y(_y + rhs.y());
		result.z(_y + rhs.z());
		return result;
	};
};
