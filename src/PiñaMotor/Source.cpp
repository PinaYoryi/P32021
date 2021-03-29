#include <iostream>
#include "Vector3.h"
using namespace std;

int main() {
	double angle = VECTOR_3_UP.angleRadians(VECTOR_3_RIGHT);
	cout << "Angle Radians: " << angle << endl;	
	angle = VECTOR_3_UP.angleDegrees(VECTOR_3_RIGHT);
	cout << "Angle Degrees: " << angle << endl;

	Vector3 a(4, -7, 11);
	Vector3 b(0, 3, -5);
	angle = a.angleRadians(b);
	cout << "Angle Radians: " << angle << endl;
	angle = a.angleDegrees(b);
	cout << "Angle Degrees: " << angle << endl;

	system("pause");
	return 0;
}