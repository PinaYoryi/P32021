#pragma once
#include "Vector3.h"
#include "Matrix3.h"

class Matrix4
{
public:
	void decomposition(Vector3<>& pos, Vector3<>& scale, Quaternion& orientation);
	Matrix3 linear() const;
private:
	float _mat[4][4];
};

