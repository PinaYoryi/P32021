#pragma once
#include "Vector3.h"

class Matrix3
{
public:
	Matrix3();
	Vector3<float> getColumn(size_t n) const;
	void setColumn(size_t n, Vector3<> v);
	Matrix3 orthonormalised() const;
	void decomposition(Matrix3& kQ, Vector3<>& kD, Vector3<>& kU) const;
	float determinant();
private:
	float _mat[3][3];
};

