#pragma once
#include "Vector3.h"

class Quaternion {
public:
	float s;
	Vector3<float> v;

	Quaternion();
	Quaternion(float scalar, Vector3<float>& vector);
	Quaternion(const Quaternion& quat);
	~Quaternion() {};

	float magnitude();
	Quaternion normalize();
	Quaternion conjugate();
	Quaternion inverse();

	Quaternion& operator=(const Quaternion& quat);
	void operator+=(const Quaternion& quat);
	Quaternion operator+(const Quaternion& quat) const;
	void operator-=(const Quaternion& quat);
	Quaternion operator-(const Quaternion& quat) const;
	void operator*=(const Quaternion& quat);
	Quaternion operator*(const Quaternion& quat) const;
	void operator*=(const float value);
	Quaternion operator*(const float value) const;
};

