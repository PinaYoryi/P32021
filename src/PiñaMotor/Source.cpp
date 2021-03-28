#include <iostream>
#include "Vector3.h"
using namespace std;

int main() {
	Vector3 a(10, 0, 0);
	Vector3 b(30, 12, 18);
	Vector3 c;
	Vector3 d(b);

	if (a.isZero()) cout << "True" << endl;
	else cout << "False" << endl;

	a.clear();

	if (a.isZero()) cout << "True" << endl;
	else cout << "False" << endl;

	cout << endl;

	a.print();
	a.normalized();
	a.print();

	cout << endl;

	b.print();
	b.normalized();
	b.print();

	cout << endl;

	d.print();
	if (a != b) cout << "NO SON IGUALES" << endl;
	else cout << "SON IGUALES" << endl;


	system("pause");
	return 0;
}