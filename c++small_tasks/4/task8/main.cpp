#include<iostream>
using namespace std;

int mult(int m, int n) {
	int result = 0;
	int negative = 0;

	if (m < 0) {
		m = -m;
		negative = !negative;
	}

	if (n < 0) {
		n = -n;
		negative = !negative;
	}

	for (int i = 0; i < n; i++) 
		result += m;
	

	if (negative) 
		return -result;
	else 
		return result;
}

int power(int m, unsigned int n) {
	int result = 1;

	for (unsigned int i = 0; i < n; i++) {
		result = mult(result, m);
	}

	return result;
}

int main() {
	int m, n;
	
	cout << "m: ";
	cin >> m;
	cout << "n: ";
	cin >> n;
	
	cout << "Multiplication: " << mult(m,n) << endl;
	cout << "Power: " << power(m,n) << endl;

return 0;
}
