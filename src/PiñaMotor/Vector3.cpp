#include "Vector3.h"
#include <math.h>

Vector3<float> Vector3<float>::rotate(float angle, Vector3<float> axis) {
	Vector3<float> axisN = axis.normalized();
	angle *= 2*(M_PI_2 / 180);
	return (*this * cos(angle) + axisN.crossProduct(*this) * sin(angle) + axisN * (axisN.dotProduct(*this) * (1 - cos(angle))));
}