#include "Vector3.h"

// CONSTRUCTORES
Vector3::Vector3()
{
	_x = _y = _z = 0;
}

Vector3::Vector3(float x, float y, float z) :
	_x(x), _y(y), _z(z)
{

}

//Vector3::Vector3(Vector3& other)
//{
//	*this = other;
//}

Vector3::~Vector3()
{

}

// MÉTODOS
double Vector3::magnitudeSquared() const
{
	return (_x * _x + _y * _y + _z * _z);
}

double Vector3::magnitude() const
{
	return sqrt(magnitudeSquared());
}


Vector3& Vector3::normalized()
{
	double length = magnitude();

	if (length > 0) *this /= length;
	else _x = _y = _z = 0;

	return *this;
}

double Vector3::dotProduct(const Vector3& other) const
{
	return _x * other.getX() + _y * other.getY() + _z * other.getZ();
}

Vector3 Vector3::crossProduct(const Vector3& other)
{
	float nx = _y * other.getZ() - _z * other.getY();
	float ny = _z * other.getX() - _x * other.getZ();
	float nz = _x * other.getY() - _y * other.getX();

	return Vector3(nx, ny, nz);
}

bool Vector3::isZero() const
{
	return ((_x == 0) && (_y == 0) && (_z == 0));
}

void Vector3::clear()
{
	_x = _y = _z = 0;
}

// OPERADORES
bool Vector3::operator==(const Vector3& other) const
{
	// Si comparten la misma dirección de memoria es que son el mismo vector
	if (this == &other)
		return true;

	// Si las tres componentes son iguales también son el mismo vector
	if ((_x == other.getX()) && (_y == other.getY()) && (_z == other.getZ()))
		return true;

	return false;
}

bool Vector3::operator!=(const Vector3& other) const
{
	// Lo contrario a que sean iguales
	return !(*this == other);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	// Modifica el Vector3
	_x += other.getX();
	_y += other.getY();
	_z += other.getZ();

	return *this;
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	// Devuelve un Vector3 nuevo sin modificar este
	return Vector3(_x, _y, _z) += other;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	// Modifica el Vector3
	_x -= other.getX();
	_y -= other.getY();
	_z -= other.getZ();

	return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	// Devuelve un Vector3 nuevo sin modificar este
	return Vector3(_x, _y, _z) -= other;
}

Vector3& Vector3::operator*=(const double val)
{
	// Modifica el Vector3
	_x *= val;
	_y *= val;
	_z *= val;

	return *this;
}

Vector3 Vector3::operator*(const double val) const
{
	// Devuelve un Vector3 nuevo sin modificar este
	return Vector3(_x, _y, _z) *= val;
}

Vector3& Vector3::operator/=(const double val)
{
	// Modifica el Vector3
	_x /= val;
	_y /= val;
	_z /= val;

	return *this;
}

Vector3 Vector3::operator/(const double val) const
{
	// Devuelve un Vector3 nuevo sin modificar este
	return Vector3(_x, _y, _z) /= val;
}

