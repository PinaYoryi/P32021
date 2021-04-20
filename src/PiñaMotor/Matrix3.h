#pragma once
#include "Vector3.h"

class Matrix3 {
public:
	Matrix3():_mat() {};
	Matrix3(const float arr[3][3]);
	Matrix3(float a1, float a2, float a3,
		float b1, float b2, float b3,
		float c1, float c2, float c3);
    
	Vector3<float> getColumn(size_t n) const;
	void setColumn(size_t n, Vector3<> v);
	Matrix3 orthonormalised() const;
	void decomposition(Matrix3& kQ, Vector3<>& kD, Vector3<>& kU) const;
	float determinant();

	const float* operator[] (size_t iRow) const;
	float* operator[] (size_t iRow);

private:
	float _mat[3][3];
};

