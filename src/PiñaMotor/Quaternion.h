#pragma once
#include "Vector3.h"
#include "Matrix3.h"
#include <btBulletDynamicsCommon.h>

class Quaternion {
public:
	float s;
	Vector3<float> v;

	// Constructores
	Quaternion();
	Quaternion(float w, float x, float y, float z);
	Quaternion(float scalar, Vector3<float>& vector);
	Quaternion(const Quaternion& quat);
	Quaternion(const Matrix3& mat);
	/// <summary>
	/// Convierte una matriz en Quaternion, actua como constructor
	/// </summary>
	/// <param name="mat"></param>
	void fromMatrix(const Matrix3& mat);
	// Destructor
	~Quaternion() {};

	/// <summary>
	/// Convierte el vector dado a Quaternion
	/// </summary>
	/// <param name="vector"> Vector a convertir </param>
	/// <returns></returns>
	static Quaternion Euler(Vector3<float> vector);

	/// <summary>
	/// Devuelve el angulo entre dos Quaterniones
	/// </summary>
	/// <returns></returns>
	static float Angle(Quaternion& a, Quaternion& b);
	

	float magnitude();
	Quaternion normalize();
	// Invierte el signo de la parte imaginaria, actua como inversa
	Quaternion conjugate();
	// La inversa, pero normalizada, es un metodo un poco redundante pues solo se 
	// tendria que usar si se han puesto los Quaterniones a mano y no mediante Euler()
	Quaternion inverse();
	/// <summary>
	/// Convierte el Quaternion en angulos de Euler.
	/// </summary>
	/// <returns></returns>
	Vector3<float> toEuler();
	/// <summary>
	///	Convierte el Quaternion en una matriz con angulos de Euler
	/// </summary>
	/// <returns></returns>
	Matrix3 toMatrix();

	Quaternion& operator=(const Quaternion& quat);
	void operator+=(const Quaternion& quat);
	Quaternion operator+(const Quaternion& quat) const;
	void operator-=(const Quaternion& quat);
	Quaternion operator-(const Quaternion& quat) const;
	void operator*=(const Quaternion& quat);
	Quaternion operator*(const Quaternion& quat) const;
	void operator*=(const float value);
	Quaternion operator*(const float value) const;

#ifdef _DEBUG
	friend ostream& operator<<(ostream& output, const Quaternion& q) {
		output << "(" << q.s << ", " << q.v.x << ", " << q.v.y << ", " << q.v.z << ")" << "\n";
		return output;
	};
#endif // _DEBUG

	//Parsear de Quaternion a btQuaternion
	operator btQuaternion() const { return btQuaternion(v.x, v.y, v.z, s); }

	operator Ogre::Quaternion() const;
	
};

