#pragma once
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <OgreVector3.h>
using namespace std;

/*
*	Se declara toda la clase en el .h para evitar problemas de link.
*	Al utilizar templates en una clase dividida entre .h y .cpp el
*	compilador se pierde un poco y las soluciones que he visto no parecian muy limpias.
*/

class Quaternion;

template <typename T = float>
class Vector3 {
public:
	// Constructor vacío (inicia todas las variables a 0)
	Vector3() {
		_x = _y = _z = 0;
	}

	// Constructor por parámetros
	Vector3(T x, T y, T z) :
		_x(x), _y(y), _z(z) {}

	// Constructor por copia (Está comentado porque se carga el resto de constructores)
	Vector3(const Vector3<T>& other) :
		_x(other.getX()), _y(other.getY()), _z(other.getZ()) {}

	// Destructor (vacío)
	~Vector3() {}

	// Getters
	inline T getX() const { return _x; };
	inline T getY() const { return _y; };
	inline T getZ() const { return _z; };

	// Setters
	inline void setX(T x) { _x = x; };
	inline void setY(T y) { _y = y; };
	inline void setZ(T z) { _z = z; };

	// Métodos
	double magnitudeSquared() const { return (sqrt(_x) + sqrt(_y) + sqrt(_z)); }
	double magnitude() const { return sqrt(magnitudeSquared()); }

	Vector3<float> rotate(float angle, Vector3<float> axis);

	/// <summary>
	/// Normaliza el vector
	/// </summary>
	void normalized() {
		double length = magnitude();
		if (length > 0) *this /= (T)length;
		throw std::domain_error("Magnitude equals zero");
	}

	/// <summary>
	/// Devuelve el producto escalar entre 2 vectores
	/// </summary>
	double dotProduct(const Vector3<T>& other) const { return _x * other.getX() + _y * other.getY() + _z * other.getZ(); }

	/// <summary>
	/// Devuelve el producto cruzado entre 2 vectores
	/// </summary>
	Vector3<T> crossProduct(const Vector3<T>& other) const {
		float nx = _y * other.getZ() - _z * other.getY();
		float ny = _z * other.getX() - _x * other.getZ();
		float nz = _x * other.getY() - _y * other.getX();
		return Vector3<T>(nx, ny, nz);
	}

	/// <summary>
	/// Devuelve true si todas las variables del vector están a 0
	/// </summary>
	bool isZero() const { return ((_x == 0) && (_y == 0) && (_z == 0)); }

	/// <summary>
	/// Setea el vector a 0
	/// </summary>
	void clear() { _x = _y = _z = 0; }

	/// <summary>
	/// Invierte el vector
	/// </summary>
	void inverse() { _x = -_x; _y = -_y; _z = -_z; }

	/// <summary>
	/// Calcula el ángulo con respecto a otro vector
	/// </summary>
	/// <returns> Ángulo en radianes </returns>
	double angleRadians(const Vector3<T>& other) const {
		double dot = dotProduct(other);
		double lenSq1 = magnitudeSquared();
		double lenSq2 = other.magnitudeSquared();
		double angle = acos(dot / sqrt(lenSq1 * lenSq2));
		return angle;
	}

	/// <summary>
	/// Calcula el ángulo con respecto a otro vector
	/// </summary>
	/// <returns> Ángulo en grados </returns>
	double angleDegrees(const Vector3<T>& other) const {
		double angle = angleRadians(other);
		angle = angle * 180 / M_PI;
		return angle;
	}

	// Operadores
	bool operator==(const Vector3<T>& other) const {
		// Si comparten la misma dirección de memoria es que son el mismo vector
		if (this == &other) return true;
		// Si las tres componentes son iguales también son el mismo vector
		if ((_x == other.getX()) && (_y == other.getY()) && (_z == other.getZ())) return true;
		return false;
	}
	bool operator!=(const Vector3<T>& other) const { return !(*this == other); }

	Vector3<T>& operator+=(const Vector3<T>& other) { _x += other.getX(); _y += other.getY(); _z += other.getZ(); return *this; }
	Vector3<T> operator+(const Vector3<T>& other) const { return Vector3<T>(_x, _y, _z) += other; }

	Vector3<T>& operator-=(const Vector3<T>& other) { _x -= other.getX(); _y -= other.getY(); _z -= other.getZ(); return *this; }
	Vector3<T> operator-(const Vector3<T>& other) const { return Vector3<T>(_x, _y, _z) -= other; }

	Vector3<T>& operator*=(const T val) { _x *= val; _y *= val; _z *= val; return *this; }
	Vector3<T> operator*(const T val) const { return Vector3<T>(_x, _y, _z) *= val; }

	Vector3<T>& operator/=(const T val) { _x /= val; _y /= val; _z /= val; return *this; }
	Vector3<T> operator/(const T val) const { return Vector3<T>(_x, _y, _z) /= val; }

	//Parsear de Vector3 a Ogre::Vector3
	operator Ogre::Vector3() const { return Ogre::Vector3((float)_x, (float)_y, (float)_z); }

	// DEBUG
#ifdef _DEBUG
	void print() { cout << "(" << _x << ", " << _y << ", " << _z << ")" << "\n"; };
#endif 
	

	// Vectores predefinidos
	static const Vector3<T> up() { return Vector3<T>((T)0, (T)1, (T)0); }
	static const Vector3<T> down() { return Vector3<T>((T)0, (T)-1, (T)0); }
	static const Vector3<T> left() { return Vector3<T>((T)-1, (T)0, (T)0); }
	static const Vector3<T> right() { return Vector3<T>((T)1, (T)0, (T)0); }
	static const Vector3<T> forward() { return Vector3<T>((T)0, (T)0, (T)1); }
	static const Vector3<T> back() { return Vector3<T>((T)0, (T)0, (T)-1); }
	static const Vector3<T> one() { return Vector3<T>((T)1, (T)1, (T)1); }
	static const Vector3<T> zero() { return Vector3<T>((T)0, (T)0, (T)0); }

private:
	// Variables
	T _x;
	T _y;
	T _z;
};