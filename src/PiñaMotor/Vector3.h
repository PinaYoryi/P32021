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
	// Variables
	T x;
	T y;
	T z;
	
	// Constructor vac�o (inicia todas las variables a 0)
	Vector3():x(), y(), z() {}

	// Constructor por parámetros
	Vector3(T x, T y, T z) :
		x(x), y(y), z(z) {}

	// Constructor por copia
	Vector3(const Vector3<T>& other) :
		x(other.x), y(other.y), z(other.z) {}

	// Destructor (vacío)
	~Vector3() {}

	// Métodos
	double magnitudeSquared() const { return (pow(x, 2) + pow(y, 2) + pow(z, 2)); }
	double magnitude() const { return sqrt(magnitudeSquared()); }

	Vector3<float> rotate(float angle, Vector3<float> axis);

	/// <summary>
	/// Normaliza el vector
	/// </summary>
	Vector3<T> normalized() {
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
	double dotProduct(const Vector3<T>& other) const { return x * other.x + y * other.y + z * other.z; }

	/// <summary>
	/// Devuelve el producto cruzado entre 2 vectores
	/// </summary>
	Vector3<T> crossProduct(const Vector3<T>& other) const {
		float nx = y * other.z - z * other.y;
		float ny = z * other.x - x * other.z;
		float nz = x * other.y - y * other.x;
		return Vector3<T>(nx, ny, nz);
	}

	/// <summary>
	/// Devuelve true si todas las variables del vector están a 0
	/// </summary>
	bool isZero() const { return ((x == 0) && (y == 0) && (z == 0)); }

	/// <summary>
	/// Setea el vector a 0
	/// </summary>
	void clear() { x = y = z = 0; }

	/// <summary>
	/// Invierte el vector
	/// </summary>
	void inverse() { x = -x; y = -y; z = -z; }

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
		if ((x == other.x) && (y == other.y) && (z == other.z)) return true;
		return false;
	}
	bool operator!=(const Vector3<T>& other) const { return !(*this == other); }

	Vector3<T>& operator+=(const Vector3<T>& other) { x += other.x; y += other.y; z += other.z; return *this; }
	Vector3<T> operator+(const Vector3<T>& other) const { return Vector3<T>(x, y, z) += other; }

	Vector3<T>& operator-=(const Vector3<T>& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	Vector3<T> operator-(const Vector3<T>& other) const { return Vector3<T>(x, y, z) -= other; }

	Vector3<T>& operator*=(const T val) { x *= val; y *= val; z *= val; return *this; }
	Vector3<T> operator*(const T val) const { return Vector3<T>(x, y, z) *= val; }

	Vector3<T>& operator/=(const T val) { x /= val; y /= val; z /= val; return *this; }
	Vector3<T> operator/(const T val) const { return Vector3<T>(x, y, z) /= val; }
	friend ostream& operator<<(ostream& output, const Vector3<T>& v) {
		output << "(" << v.x << ", " << v.y << ", " << v.z << ")" << "\n";
		return output;
	};

	//Parsear de Vector3 a Ogre::Vector3
	operator Ogre::Vector3() const { return Ogre::Vector3((float)x, (float)y, (float)z); }


	// Vectores predefinidos
	static const Vector3<T> up() { return Vector3<T>((T)0, (T)1, (T)0); }
	static const Vector3<T> down() { return Vector3<T>((T)0, (T)-1, (T)0); }
	static const Vector3<T> left() { return Vector3<T>((T)-1, (T)0, (T)0); }
	static const Vector3<T> right() { return Vector3<T>((T)1, (T)0, (T)0); }
	static const Vector3<T> forward() { return Vector3<T>((T)0, (T)0, (T)1); }
	static const Vector3<T> back() { return Vector3<T>((T)0, (T)0, (T)-1); }
	static const Vector3<T> one() { return Vector3<T>((T)1, (T)1, (T)1); }
	static const Vector3<T> zero() { return Vector3<T>((T)0, (T)0, (T)0); }
};