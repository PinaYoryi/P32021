#pragma once
#include <iostream>
//#include <OgreVector3.h>
using namespace std;

# define PI 3.14159265358979323846

class Vector3
{
public:
	// Constructor vacío (inicia todas las variables a 0)
	Vector3();

	// Constructor por parámetros
	Vector3(float x, float y, float z);

	//// Constructor por copia (Está comentado porque se carga el resto de constructores)
	//Vector3(Vector3& other);

	// Destructor (vacío)
	~Vector3();

	// Getters
	inline float getX() const { return _x; };
	inline float getY() const { return _y; };
	inline float getZ() const { return _z; };

	// Setters
	inline void setX(float x) { _x = x; };
	inline void setY(float y) { _y = y; };
	inline void setZ(float z) { _z = z; };

	// Métodos
	double magnitudeSquared() const;
	double magnitude() const;

	/// <summary>
	/// Normaliza el vector
	/// </summary>
	void normalized();

	/// <summary>
	/// Devuelve el producto escalar entre 2 vectores
	/// </summary>
	double dotProduct(const Vector3& vector) const;

	/// <summary>
	/// Devuelve el producto cruzado entre 2 vectores
	/// </summary>
	Vector3 crossProduct(const Vector3& vector) const;

	/// <summary>
	/// Devuelve true si todas las variables del vector están a 0
	/// </summary>
	bool isZero() const;

	/// <summary>
	/// Setea el vector a 0
	/// </summary>
	void clear();

	/// <summary>
	/// Invierte el vector
	/// </summary>
	void inverse();

	/// <summary>
	/// Calcula el ángulo con respecto a otro vector
	/// </summary>
	/// <returns> Ángulo en radianes </returns>
	double angleRadians(const Vector3& other) const;

	/// <summary>
	/// Calcula el ángulo con respecto a otro vector
	/// </summary>
	/// <returns> Ángulo en grados </returns>
	double angleDegrees(const Vector3& other) const;

	// Operadores
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;

	Vector3& operator+=(const Vector3& other);
	Vector3 operator+(const Vector3& other) const;

	Vector3& operator-=(const Vector3& other);
	Vector3 operator-(const Vector3& other) const;

	Vector3& operator*=(const double val);
	Vector3 operator*(const double val) const;

	Vector3& operator/=(const double val);
	Vector3 operator/(const double val) const;

	// DEBUG
	void print() { cout << "(" << _x << ", " << _y << ", " << _z << ")" << endl; };

private:
	// Variables
	float _x;
	float _y;
	float _z;
};

// Vectores predefinidos
const static Vector3 VECTOR_3_UP = Vector3(0.0, 1.0, 0.0);
const static Vector3 VECTOR_3_DOWN = Vector3(0.0, -1.0, 0.0);
const static Vector3 VECTOR_3_RIGHT = Vector3(1.0, 0.0, 0.0);
const static Vector3 VECTOR_3_LEFT = Vector3(-1.0, 0.0, 0.0);
const static Vector3 VECTOR_3_FORDWARD = Vector3(0.0, 0.0, 1.0);
const static Vector3 VECTOR_3_BACK = Vector3(0.0, 0.0, -1.0);
const static Vector3 VECTOR_3_ONE = Vector3(1.0, 1.0, 1.0);
const static Vector3 VECTOR_3_ZERO = Vector3(0.0, 0.0, 0.0);