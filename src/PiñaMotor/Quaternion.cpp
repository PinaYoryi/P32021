#include "Quaternion.h"

Quaternion::Quaternion(float scalar, Vector3<float>& vector) : s(scalar), v(vector) { }

Quaternion::Quaternion(const Quaternion& quat) : s(quat.s), v(quat.v) {}

float Quaternion::magnitude() {
	float scalar = s * s;
	float vec = v.dotProduct(v);
	return sqrt(scalar + vec);
}

Quaternion Quaternion::normalize() {
	float mag = magnitude();
	if (mag != 0) {
		float normalizeValue = 1 / mag;

		s *= normalizeValue;
		v *= normalizeValue;
		return *this;
	}

	throw std::domain_error("Magnitude equals zero");
}

Quaternion Quaternion::conjugate() {
	Vector3<float> vec = v * -1;
	return { s, vec };
}

Quaternion Quaternion::inverse() {
	float mag = magnitude();
	mag *= mag;
	mag = 1 / mag;

	Quaternion conj = conjugate();
	Vector3<float> vec = conj.v * mag;

	return { conj.s * mag , vec };
}

Quaternion& Quaternion::operator=(const Quaternion& quat) {
	s = quat.s;
	v = quat.v;
	return *this;
}

void Quaternion::operator+=(const Quaternion& quat) {
	s += quat.s;
	v += quat.v;
}

Quaternion Quaternion::operator+(const Quaternion& quat) const {
	Vector3<float> vec = v + quat.v;
	return { s + quat.s, vec };
}

void Quaternion::operator-=(const Quaternion& quat) {
	s -= quat.s;
	v -= quat.v;
}

Quaternion Quaternion::operator-(const Quaternion& quat) const {
	Vector3<float> vec = v - quat.v;
	return { s - quat.s, vec };
}

void Quaternion::operator*=(const Quaternion& quat) {
	s = s * quat.s - v.dotProduct(quat.v);
	v = quat.v * s + v * quat.s + v.crossProduct(quat.v);
}

Quaternion Quaternion::operator*(const Quaternion& quat) const {
	float scalar = s * quat.s - v.dotProduct(quat.v);
	Vector3<float> vec = quat.v * s + v * quat.s + v.crossProduct(quat.v);
	return { scalar, vec };
}

void Quaternion::operator*=(const float value) {
	s *= value;
	v *= value;
}

Quaternion Quaternion::operator*(const float value) const {
	Vector3<float> vec = v * value;
	return { s * value, vec };
}