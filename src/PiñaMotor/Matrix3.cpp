#include "Matrix3.h"
Vector3<float> Matrix3::getColumn(size_t n)const {
	return  { _mat[0][n], _mat[1][n], _mat[2][n] };
}

void Matrix3::setColumn(size_t n, Vector3<> v)
{
	_mat[0][n] = v.x; _mat[1][n] = v.y; _mat[2][n] = v.z;
}

#define MINOR(m, r0, r1, r2, c0, c1, c2) = m[r0][c0] * (m[r1][c1] * m[r2][c2] - m[r2][c1] * m[r1][c2]) - m[r0][c1] * (m[r1][c0] * m[r2][c2] - m[r2][c0] * m[r1][c2]) + m[r0][c2] * (m[r1][c0] * m[r2][c1] - m[r2][c0] * m[r1][c1]);

float Matrix3::determinant() {
	return _mat[0][0] * MINOR(*this, 1, 2, 3, 1, 2, 3) -
		_mat[0][1] * Minor(*this, 1, 2, 3, 0, 2, 3) +
		_mat[0][2] * Minor(*this, 1, 2, 3, 0, 1, 3) -
		_mat[0][3] * Minor(*this, 1, 2, 3, 0, 1, 2);
}


/// Gram-Schmidt orthogonalisation (applied to columns of rotation matrix)
Matrix3 Matrix3::orthonormalised() const
{
	Matrix3 Q;
	Q.setColumn(0, getColumn(0).normalize());

	float dot0 = Q.getColumn(0).dotProduct(getColumn(1));
	Q.setColumn(1, (getColumn(1) - Q.getColumn(0) * dot0).normalized());

	// compute q2
	float dot1 = Q.getColumn(1).dotProduct(getColumn(2));
	dot0 = Q.getColumn(0).dotProduct(getColumn(2));
	Q.setColumn(2, (getColumn(2) - Q.getColumn(0) * dot0 + Q.getColumn(1) * dot1).normalized());

	return Q;
}
void Matrix3::decomposition(Matrix3& kQ, Vector3<>& kD, Vector3<>& kU) const {
	// build orthogonal matrix Q
	kQ = orthonormalised();

	// guarantee that orthogonal matrix has determinant 1 (no reflections)
	if (kQ.determinant() < 0.0) {
		for (size_t iRow = 0; iRow < 3; iRow++)
			for (size_t iCol = 0; iCol < 3; iCol++)
				kQ[iRow][iCol] = -kQ[iRow][iCol];
	}

	// build "right" matrix R
	Matrix3 kR;
	kR[0][0] = kQ.getColumn(0).dotProduct(getColumn(0));
	kR[0][1] = kQ.getColumn(0).dotProduct(getColumn(1));
	kR[0][2] = kQ.getColumn(0).dotProduct(getColumn(2));
	kR[1][1] = kQ.getColumn(1).dotProduct(getColumn(1));
	kR[1][2] = kQ.getColumn(1).dotProduct(getColumn(2));
	kR[2][2] = kQ.getColumn(2).dotProduct(getColumn(2));

	// the scaling component
	kD[0] = kR[0][0];
	kD[1] = kR[1][1];
	kD[2] = kR[2][2];
}