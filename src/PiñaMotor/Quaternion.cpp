#include "Quaternion.h"
Quaternion::Quaternion(): s(1), v(0,0,0) {};

Quaternion::Quaternion(float w, float x, float y, float z) : s(w), v(x,y,z) {}

Quaternion::Quaternion(float scalar, Vector3<float>& vector) : s(scalar), v(vector) {}

Quaternion::Quaternion(const Quaternion& quat) : s(quat.s), v(quat.v) {}

Quaternion Quaternion::euler(Vector3<float> vector) {
	Vector3<> v = vector * M_PI / 180;

	float cx = cosf(v.x * 0.5);
	float sx = sinf(v.x * 0.5);
	float cy = cosf(v.y * 0.5);
	float sy = sinf(v.y * 0.5);
	float cz = cosf(v.z * 0.5);
	float sz = sinf(v.z * 0.5);

	Vector3<float> vec;
	float s = cx * cy * cz + sx * sy * sz;
	vec.x = sx * cy * cz - cx * sy * sz;
	vec.y = cx * sy * cz + sx * cy * sz;
	vec.z = cx * cy * sz - sx * sy * cz;

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
	float sinx_cosy = 2 * (s * v.x + v.y * v.z);
	float cosx_cosy = 1 - 2 * (v.x * v.x + v.y * v.y);
	vec.x = atan2(sinx_cosy, cosx_cosy);

	float siny = 2 * (s * v.y - v.z * v.x);
	if (abs(siny) >= 1)
		vec.y = copysignf(M_PI_2, siny);
	else
		vec.y = asinf(siny);

	float sinz_cosy = 2 * (s * v.z + v.x * v.y);
	float cosz_cosy = 1 - 2 * (v.y * v.y + v.z * v.z);
	vec.z = atan2(sinz_cosy, cosz_cosy);

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

Quaternion::operator Ogre::Quaternion() const {
	return { s, v.x, v.y, v.z }; 
}
