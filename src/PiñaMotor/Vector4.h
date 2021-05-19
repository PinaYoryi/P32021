#pragma once
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <OgreVector.h>
/*
*	Se declara toda la clase en el .h para evitar problemas de link.
*	Al utilizar templates en una clase dividida entre .h y .cpp el
*	compilador se pierde un poco y las soluciones que he visto no parecian muy limpias.
*/

class Quaternion;

template <typename T = float>
class Vector4 {
public:
	// Variables
	T x;
	T y;
	T z;
	T w;

	// Constructor vac�o (inicia todas las variables a 0)
	Vector4() :x(), y(), z(), w() {}

	// Constructor por parámetros
	Vector4(T x, T y, T z, T w) :
		x(x), y(y), z(z), w(w) {}

	// Constructor por copia
	Vector4(const Vector4<T>& other) :
		x(other.x), y(other.y), z(other.z), w(other.w) {}

	// Constructor a partir de Ogre::Vector4
	Vector4(const Ogre::Vector4& other) :
		x(other.x), y(other.y), z(other.z), w(other.w) {}

	// Constructor a partir de Ogre::ColourValue
	Vector4(const Ogre::ColourValue& other) :
		x(other.r), y(other.g), z(other.b), w(other.a) {}

	// Destructor (vacío)
	~Vector4() {}

	// Métodos
	double magnitudeSquared() const { return (pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2)); }
	double magnitude() const { return sqrt(magnitudeSquared()); }

	/// <summary>
	/// Normaliza el vector
	/// </summary>
	Vector4<T> normalize() {
		double length = magnitude();
		if (length > 0) {
			*this /= (T)length;
			return *this;
		}
		throw std::domain_error("Magnitude equals zero");
	}

	/// <summary>
	/// Devuelve el vector normalizado, pero no lo cambia
	/// </summary>
	Vector4<T> normalized() const {
		double length = magnitude();
		if (length > 0)
			return  *this / (T)length;
		throw std::domain_error("Magnitude equals zero");
	}

	/// <summary>
	/// Devuelve el producto escalar entre 2 vectores
	/// </summary>
	double dotProduct(const Vector4<T>& other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }

	/// <summary>
	/// Devuelve true si todas las variables del vector están a 0
	/// </summary>
	bool isZero() const { return ((x == 0) && (y == 0) && (z == 0) && (w == 0)); }

	/// <summary>
	/// Setea el vector a 0
	/// </summary>
	void clear() { x = y = z = w = 0; }

	/// <summary>
	/// Invierte el vector
	/// </summary>
	void inverse() { x = -x; y = -y; z = -z; w = -w; }

	// Operadores
	bool operator==(const Vector4<T>& other) const {
		// Si comparten la misma dirección de memoria es que son el mismo vector
		if (this == &other) return true;
		// Si las tres componentes son iguales también son el mismo vector
		if ((x == other.x) && (y == other.y) && (z == other.z) && (w == other.w)) return true;
		return false;
	}
	bool operator!=(const Vector4<T>& other) const { return !(*this == other); }

	Vector4<T>& operator+=(const Vector4<T>& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
	Vector4<T> operator+(const Vector4<T>& other) const { return Vector4<T>(x, y, z, w) += other; }

	Vector4<T>& operator-=(const Vector4<T>& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
	Vector4<T> operator-(const Vector4<T>& other) const { return Vector4<T>(x, y, z, w) -= other; }

	Vector4<T>& operator*=(const T val) { x *= val; y *= val; z *= val; w *= val; return *this; }
	Vector4<T> operator*(const T val) const { return Vector4<T>(x, y, z, w) *= val; }

	Vector4<T>& operator/=(const T val) { x /= val; y /= val; z /= val; w /= val; return *this; }
	Vector4<T> operator/(const T val) const { return Vector4<T>(x, y, z, w) /= val; }
#ifdef _DEBUG
	friend std::ostream& operator<<(std::ostream& output, const Vector4<T>& v) {
		output << "(" << v.x << ", " << v.y << ", " << v.z << "," << v.w << ")" >> "\n";
		return output;
	};
#endif // _DEBUG


	//Parsear de Vector3 a Ogre::Vector3
	operator Ogre::Vector4() const { return Ogre::Vector4((float)x, (float)y, (float)z, (float)w); }
	operator Ogre::ColourValue() const { return Ogre::ColourValue((float)x, (float)y, (float)z, (float)w); }


	// Vectores predefinidos
	static const Vector4<T> zero() { return Vector4<T>((T)0, (T)0, (T)0, (T)0); }
};