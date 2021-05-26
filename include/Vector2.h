#pragma once
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <OgreVector2.h>

/*
*	Se declara toda la clase en el .h para evitar problemas de link.
*	Al utilizar templates en una clase dividida entre .h y .cpp el
*	compilador se pierde un poco y las soluciones que he visto no parecian muy limpias.
*/


template <typename T = float>
class Vector2 {
public:
	// Variables
	T x;
	T y;

	// Constructor vac�o (inicia todas las variables a 0)
	Vector2() : x(), y() {}

	// Constructor por par�metros
	Vector2(T x, T y) :
		x(x), y(y) {}

	// Constructor por copia
	Vector2(const Vector2<T>& other) :
		x(other.x), y(other.y) {}

	// Destructor (vac�o)
	~Vector2() {}

	// M�todos
	double magnitudeSquared() const { return (pow(x, 2) + pow(y, 2)); }
	double magnitude() const { return sqrt(magnitudeSquared()); }

	/// <summary>
	/// Normaliza el vector
	/// </summary>
	Vector2<T> normalized() {
		double length = magnitude();
		if (length > 0) {
			*this /= (T)length;
			return *this;
		}
		throw std::domain_error("Magnitude equals zero");
	}

	/// <summary>
	/// Devuelve el producto escalar entre 2 vectores
	/// </summary>
	double dotProduct(const Vector2<T>& other) const { return x * other.x + y * other.y; }

	/// <summary>
	/// Devuelve true si todas las variables del vector est�n a 0
	/// </summary>
	bool isZero() const { return ((x == 0) && (y == 0)); }

	/// <summary>
	/// Setea el vector a 0
	/// </summary>
	void clear() { x = y = 0; }

	/// <summary>
	/// Invierte el vector
	/// </summary>
	void inverse() { x = -x; y = -y; }

	/// <summary>
	/// Calcula el �ngulo con respecto a otro vector
	/// </summary>
	/// <returns> �ngulo en radianes </returns>
	double angleRadians(const Vector2<T>& other) const {
		double dot = dotProduct(other);
		double lenSq1 = magnitudeSquared();
		double lenSq2 = other.magnitudeSquared();
		double angle = acos(dot / sqrt(lenSq1 * lenSq2));
		return angle;
	}

	/// <summary>
	/// Calcula el �ngulo con respecto a otro vector
	/// </summary>
	/// <returns> �ngulo en grados </returns>
	double angleDegrees(const Vector2<T>& other) const {
		double angle = angleRadians(other);
		angle = angle * 180 / M_PI;
		return angle;
	}

	// Operadores
	bool operator==(const Vector2<T>& other) const {
		// Si comparten la misma direcci�n de memoria es que son el mismo vector
		if (this == &other) return true;
		// Si las tres componentes son iguales tambi�n son el mismo vector
		if ((x == other.x) && (y == other.y)) return true;
		return false;
	}
	bool operator!=(const Vector2<T>& other) const { return !(*this == other); }

	Vector2<T>& operator+=(const Vector2<T>& other) { x += other.x; y += other.y; return *this; }
	Vector2<T> operator+(const Vector2<T>& other) const { return Vector2<T>(x, y) += other; }

	Vector2<T>& operator-=(const Vector2<T>& other) { x -= other.x; y -= other.y; return *this; }
	Vector2<T> operator-(const Vector2<T>& other) const { return Vector2<T>(x, y) -= other; }

	Vector2& operator*=(const T val) { x *= val; y *= val; return *this; }
	Vector2<T> operator*(const T val) const { return Vector2<T>(x, y) *= val; }

	Vector2<T>& operator/=(const T val) { x /= val; y /= val; return *this; }
	Vector2<T> operator/(const T val) const { return Vector2<T>(x, y) /= val; }
	friend std::ostream& operator<<(std::ostream& output, const Vector2<T>& v) {
		output << "(" << v.x << ", " << v.y << ")" << "\n";
		return output;
	};

	//Parsear de Vector2 a Ogre::Vector2
	operator Ogre::Vector2() const { return Ogre::Vector2((float)x, (float)y); }

	// Vectores predefinidos
	static const Vector2<T> up() { return Vector2<T>((T)0, (T)1); }
	static const Vector2<T> down() { return Vector2<T>((T)0, (T)-1); }
	static const Vector2<T> left() { return Vector2<T>((T)-1, (T)0); }
	static const Vector2<T> right() { return Vector2<T>((T)1, (T)0); }
	static const Vector2<T> one() { return Vector2<T>((T)1, (T)1); }
	static const Vector2<T> zero() { return Vector2<T>((T)0, (T)0); }
};