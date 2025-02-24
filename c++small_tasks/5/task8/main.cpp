#include <iostream>
using namespace std;

int mult(int m, int n) {
	if (n == 0 || m == 0) return 0;
	if (n>0) return m + mult(m, n - 1);
	else return -m + mult(m, n + 1);
}

double power(int m,  int n) {
	if (n == 0 && m == 0) {
		cout << "undefined" << endl; 
		exit(1);
	}
	if (n == 0) return 1;
	if (n == 0 && m < 0) return -1;
	if (m == 0) return 0;
 	return n > 0 ? mult(m, power(m, n - 1)) : 1.0 / mult(m, power(m, -(n + 1)));
}

int main() {
	int int1, int2;
	
	cout << "Int1: ";
	cin >> int1;
	cout << "Int2: ";
	cin >> int2;
	
	cout << "Multiplication: " << mult(int1, int2) << endl;
	cout << "Exponentiation: " << power(int1, int2) << endl;

return 0;
}
