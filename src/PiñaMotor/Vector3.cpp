#include "Vector3.h"
#include "Quaternion.h"

Vector3<float> Vector3<float>::rotate(Vector3<float> axis) {
	// Convertirmos el eje en un cuaternion puro
	Quaternion a(0, *this);
	
	// Creamos ahora el cuaternion
	Quaternion b= Quaternion::Euler(axis);
	// Normalizamos el cuaternion
	b.normalize();
	// Conseguimos el inverso
	Quaternion bInverse = b.inverse();

	// Aplicamos la rotacion y la devolvemos
	return (b * a * bInverse).v;
}