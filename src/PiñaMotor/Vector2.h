#pragma once
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <OgreVector2.h>
using namespace std;

/*
*	Se declara toda la clase en el .h para evitar problemas de link.
*	Al utilizar templates en una clase dividida entre .h y .cpp el
*	compilador se pierde un poco y las soluciones que he visto no parecian muy limpias.
*/


template <typename T = float>
class Vector2 {
public:
	// Constructor vacío (inicia todas las variables a 0)
	Vector2() {
		_x = _y = 0;
	}

	// Constructor por parámetros
	Vector2(T x, T y) :
		_x(x), _y(y) {}

	// Constructor por copia
	Vector2(const Vector2<T>& other) :
		_x(other.getX()), _y(other.getY()){}

	// Destructor (vacío)
	~Vector2() {}

	// Getters
	inline T getX() const { return _x; };
	inline T getY() const { return _y; };

	// Setters
	inline void setX(T x) { _x = x; };
	inline void setY(T y) { _y = y; };

	// Métodos
	double magnitudeSquared() const { return (sqrt(_x) + sqrt(_y)); }
	double magnitude() const { return sqrt(magnitudeSquared()); }

	/// <summary>
	/// Normaliza el vector
	/// </summary>
	void normalized() {
		double length = magnitude();
		if (length > 0) *this /= (T)length;
		else _x = _y = 0;
	}

	/// <summary>
	/// Devuelve el producto escalar entre 2 vectores
	/// </summary>
	double dotProduct(const Vector2<T>& other) const { return _x * other.getX() + _y * other.getY(); }

	/// <summary>
	/// Devuelve true si todas las variables del vector están a 0
	/// </summary>
	bool isZero() const { return ((_x == 0) && (_y == 0)); }

	/// <summary>
	/// Setea el vector a 0
	/// </summary>
	void clear() { _x = _y = 0; }

	/// <summary>
	/// Invierte el vector
	/// </summary>
	void inverse() { _x = -_x; _y = -_y; }

	/// <summary>
	/// Calcula el ángulo con respecto a otro vector
	/// </summary>
	/// <returns> Ángulo en radianes </returns>
	double angleRadians(const Vector2<T>& other) const {
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
	double angleDegrees(const Vector2<T>& other) const {
		double angle = angleRadians(other);
		angle = angle * 180 / M_PI;
		return angle;
	}

	// Operadores
	bool operator==(const Vector2<T>& other) const {
		// Si comparten la misma dirección de memoria es que son el mismo vector
		if (this == &other) return true;
		// Si las tres componentes son iguales también son el mismo vector
		if ((_x == other.getX()) && (_y == other.getY())) return true;
		return false;
	}
	bool operator!=(const Vector2<T>& other) const { return !(*this == other); }

	Vector2<T>& operator+=(const Vector2<T>& other) { _x += other.getX(); _y += other.getY(); return *this; }
	Vector2<T> operator+(const Vector2<T>& other) const { return Vector2<T>(_x, _y) += other; }

	Vector2<T>& operator-=(const Vector2<T>& other) { _x -= other.getX(); _y -= other.getY(); return *this; }
	Vector2<T> operator-(const Vector2<T>& other) const { return Vector2<T>(_x, _y) -= other; }

	Vector2& operator*=(const T val) { _x *= val; _y *= val; return *this; }
	Vector2<T> operator*(const T val) const { return Vector2<T>(_x, _y) *= val; }

	Vector2<T>& operator/=(const T val) { _x /= val; _y /= val; return *this; }
	Vector2<T> operator/(const T val) const { return Vector2<T>(_x, _y) /= val; }

	//Parsear de Vector2 a Ogre::Vector2
	operator Ogre::Vector2() const { return Ogre::Vector2((float)_x, (float)_y); }

	// DEBUG
	void print() { cout << "(" << _x << ", " << _y << ")" << "\n"; };

	// Vectores predefinidos
	static const Vector2<T> up() { return Vector2<T>((T)0, (T)1); }
	static const Vector2<T> down() { return Vector2<T>((T)0, (T)-1); }
	static const Vector2<T> left() { return Vector2<T>((T)-1, (T)0); }
	static const Vector2<T> right() { return Vector2<T>((T)1, (T)0); }
	static const Vector2<T> one() { return Vector2<T>((T)1, (T)1); }
	static const Vector2<T> zero() { return Vector2<T>((T)0, (T)0); }

private:
	// Variables
	T _x;
	T _y;
};