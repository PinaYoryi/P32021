#include "Matrix4.h"
#include "Matrix3.h"
#include "Quaternion.h"

void Matrix4::decomposition(Vector3<>& pos, Vector3<>& scale, Quaternion& orientation) {
	Matrix3 matQ;
	Vector3<> vecU;
	linear().decomposition(matQ, scale, vecU);

	orientation = Quaternion(matQ);
	pos = Vector3<>(_mat[0][3], _mat[1][3], _mat[2][3]);
}

Matrix3 Matrix4::linear() const {
	return Matrix3(_mat[0][0], _mat[0][1], _mat[0][2],
		_mat[1][0], _mat[1][1], _mat[1][2],
		_mat[2][0], _mat[2][1], _mat[2][2]);
}
