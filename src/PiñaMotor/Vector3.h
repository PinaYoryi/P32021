#pragma once
#include <iostream>
using namespace std;

class Vector3
{
public:
	// Constructor vacío (inicia todas las variables a 0)
	Vector3();

	// Constructor por parámetros
	Vector3(float x, float y, float z);

	//// Constructor por copia
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

	Vector3& normalized();

	double dotProduct(const Vector3& vector) const;

	Vector3 crossProduct(const Vector3& vector);

	bool isZero() const;
	void clear();

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
	void print() { cout << "X: " << _x << " Y: " << _y << " Z: " << _z << endl; };

private:
	// Variables
	float _x;
	float _y;
	float _z;
};

