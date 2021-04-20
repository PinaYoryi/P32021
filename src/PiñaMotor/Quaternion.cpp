#include "Quaternion.h"
#include "OgreMatrix3.h"

Quaternion::Quaternion() : s(1), v(0, 0, 0) {};

Quaternion::Quaternion(float w, float x, float y, float z) : s(w), v(x, y, z) {}

Quaternion::Quaternion(float scalar, Vector3<float>& vector) : s(scalar), v(vector) {}

Quaternion::Quaternion(const Quaternion& quat) : s(quat.s), v(quat.v) {}

Quaternion::Quaternion(const Matrix3& mat) {
	fromMatrix(mat);
}

Quaternion Quaternion::Euler(Vector3<float> vector) {
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

	float error = 0.000001;
	if (abs(s) < error) s = 0;
	if (abs(v.x) < error) v.x = 0;
	if (abs(v.y) < error) v.y = 0;
	if (abs(v.z) < error) v.z = 0;

	return { s, vec };
}

float Quaternion::Angle(Quaternion& a, Quaternion& b) {
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

	float error = 0.000001;
	if (abs(vec.x) < error) vec.x = 0;
	if (abs(vec.y) < error) vec.y = 0;
	if (abs(vec.z) < error) vec.z = 0;

	return vec * 180 / M_PI;
}

Matrix3 Quaternion::toMatrix()
{
	normalize();
	Matrix3 m;
	m[0][0] = 1 - 2 * (pow(v.y, 2) + pow(v.z, 2)); m[0][1] = 2 * (v.x * v.y - v.z * s);				m[0][2] = 2 * (v.x * v.z + v.y * s);
	m[1][0] = 2 * (v.x * v.y + v.z * s);		   m[1][1] = 1 - 2 * (pow(v.x, 2) + pow(v.z, 2));   m[1][2] = 2 * (v.y * v.z - v.x * s);
	m[2][0] = 2 * (v.x * v.z - v.y * s);		   m[2][1] = 2 * (v.y * v.z + v.x * s);				m[1][1] = 1 - 2 * (pow(v.x, 2) + pow(v.y, 2));

	return m;
}

void Quaternion::fromMatrix(const Matrix3& mat) {
	float trace = mat[0][0] + mat[1][1] + mat[2][2];
	float root;

	if (trace > 0.0)
	{
		// |w| > 1/2, may as well choose w > 1/2
		root = sqrt(trace + 1.0f);  // 2w
		s = 0.5f * root;
		root = 0.5f / root;  // 1/(4w)
		v.x = (mat[2][1] - mat[1][2]) * root;
		v.y = (mat[0][2] - mat[2][0]) * root;
		v.z = (mat[1][0] - mat[0][1]) * root;
	}
	else
	{
		// |w| <= 1/2
		static size_t s_iNext[3] = { 1, 2, 0 };
		size_t i = 0;
		if (mat[1][1] > mat[0][0])
			i = 1;
		if (mat[2][2] > mat[i][i])
			i = 2;
		size_t j = s_iNext[i];
		size_t k = s_iNext[j];

		root = sqrt(mat[i][i] - mat[j][j] - mat[k][k] + 1.0f);
		float* q[3] = { &v.x, &v.y, &v.z };
		*q[i] = 0.5f * root;
		root = 0.5f / root;
		s = (mat[k][j] - mat[j][k]) * root;
		*q[j] = (mat[j][i] + mat[i][j]) * root;
		*q[k] = (mat[k][i] + mat[i][k]) * root;
	}
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
