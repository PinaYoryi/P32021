#include "Quaternion.h"

Quaternion::Quaternion(float w, float x, float y, float z) : s(w), v(x,y,z) {}

Quaternion::Quaternion(float scalar, Vector3<float>& vector) : s(scalar), v(vector) {}

Quaternion::Quaternion(const Quaternion& quat) : s(quat.s), v(quat.v) {}

Quaternion Quaternion::euler(Vector3<float>& vector) {
	Vector3<> v = vector * M_PI / 180;

	float cx = cosf(v.getX() * 0.5);
	float sx = sinf(v.getX() * 0.5);
	float cy = cosf(v.getY() * 0.5);
	float sy = sinf(v.getY() * 0.5);
	float cz = cosf(v.getZ() * 0.5);
	float sz = sinf(v.getZ() * 0.5);

	Vector3<float> vec;
	float s = cx * cy * cz + sx * sy * sz;
	vec.setX(sx * cy * cz - cx * sy * sz);
	vec.setY(cx * sy * cz + sx * cy * sz);
	vec.setZ(cx * cy * sz - sx * sy * cz);

	return { s, vec };
}

float Quaternion::angle(Quaternion& a, Quaternion& b) {
	Quaternion ab = a.conjugate() * b;
	return 2.0 * atan2(ab.v.magnitude(), ab.s);
}

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

Vector3<float> Quaternion::toEuler() {
	Vector3<float> vec;
	float sinx_cosy = 2 * (s * v.getX() + v.getY() * v.getZ());
	float cosx_cosy = 1 - 2 * (v.getX() * v.getX() + v.getY() * v.getY());
	vec.setX(atan2(sinx_cosy, cosx_cosy));

	float siny = 2 * (s * v.getY() - v.getZ() * v.getX());
	if (abs(siny) >= 1)
		vec.setY(copysignf(M_PI_2, siny));
	else
		vec.setY(asinf(siny));

	float sinz_cosy = 2 * (s * v.getZ() + v.getX() * v.getY());
	float cosz_cosy = 1 - 2 * (v.getY() * v.getY() + v.getZ() * v.getZ());
	vec.setZ(atan2(sinz_cosy, cosz_cosy));

	return vec * 180 / M_PI;
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