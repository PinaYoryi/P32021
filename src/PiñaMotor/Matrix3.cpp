#include "Matrix3.h"
explicit Matrix3::Matrix3(const float arr[3][3]) {
	memcpy(_mat, arr, 9 * sizeof(float));
}

Matrix3::Matrix3(float a1, float a2, float a3, float b1, float b2, float b3, float c1, float c2, float c3) {
	_mat[0][0] = a1;
	_mat[0][1] = a2;
	_mat[0][2] = a3;
	_mat[1][0] = b1;
	_mat[1][1] = b2;
	_mat[1][2] = b3;
	_mat[2][0] = c1;
	_mat[2][1] = c2;
	_mat[2][2] = c3;
}

Vector3<float> Matrix3::getColumn(size_t n)const {
	return  { _mat[0][n], _mat[1][n], _mat[2][n] };
}

void Matrix3::setColumn(size_t n, Vector3<> v) {
	_mat[0][n] = v.x; _mat[1][n] = v.y; _mat[2][n] = v.z;
}

float Matrix3::determinant() {
	float Cofactor1 = _mat[1][1] * _mat[2][2] - _mat[1][2] * _mat[2][1];
	float Cofactor2 = _mat[1][2] * _mat[2][0] - _mat[1][0] * _mat[2][2];
	float Cofactor3 = _mat[1][0] * _mat[2][1] - _mat[1][1] * _mat[2][0];

	return _mat[0][0] * Cofactor1 + _mat[0][1] * Cofactor2 + _mat[0][2] * Cofactor3;
}

// Ortogonalizacion de Gram-Schmidt aplicada a las columnas de rotacion
Matrix3 Matrix3::orthonormalised() const {
	Matrix3 Q;
	Q.setColumn(0, getColumn(0).normalize());

	float dot0 = Q.getColumn(0).dotProduct(getColumn(1));
	Q.setColumn(1, (getColumn(1) - Q.getColumn(0) * dot0).normalized());

	// calculamos q2 y lo multiplicamos
	float dot1 = Q.getColumn(1).dotProduct(getColumn(2));
	dot0 = Q.getColumn(0).dotProduct(getColumn(2));
	Q.setColumn(2, (getColumn(2) - Q.getColumn(0) * dot0 + Q.getColumn(1) * dot1).normalized());

	return Q;
}

void Matrix3::decomposition(Matrix3& kQ, Vector3<>& kD, Vector3<>& kU) const {
	// construimos la matriz ortogonal
	kQ = orthonormalised();

	// garantizamos que el determinante sea 1
	if (kQ.determinant() < 0.0) {
		for (int iRow = 0; iRow < 3; iRow++)
			for (int iCol = 0; iCol < 3; iCol++)
				kQ[iRow][iCol] = -kQ[iRow][iCol];
	}

	// Construimos la matriz de rotacion
	Matrix3 kR;
	kR[0][0] = kQ.getColumn(0).dotProduct(getColumn(0));
	kR[0][1] = kQ.getColumn(0).dotProduct(getColumn(1));
	kR[0][2] = kQ.getColumn(0).dotProduct(getColumn(2));
	kR[1][1] = kQ.getColumn(1).dotProduct(getColumn(1));
	kR[1][2] = kQ.getColumn(1).dotProduct(getColumn(2));
	kR[2][2] = kQ.getColumn(2).dotProduct(getColumn(2));

	// y el componente de escala
	kD.x = kR[0][0];
	kD.y = kR[1][1];
	kD.z = kR[2][2];
}

const float* Matrix3::operator[] (size_t iRow) const {
	return _mat[iRow];
}

float* Matrix3::operator[] (size_t iRow) {
	return _mat[iRow];
}