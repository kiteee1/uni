#include <iostream>
using namespace std;

long long Fn(int n) {
	if (n == 0 || n == 1 || n == 2) return 1;
	return 2 * Fn(n - 1) + Fn(n - 2) * Fn(n - 3);
}

int main() {
	int n;
	
	cout << "Enter the value of n: ";
	cin >> n;
	
	if (n < 0) 
		cout << "Invalid input. n should be a non-negative integer." << endl;
	else 
		cout << "F" << n << " = " << Fn(n) << endl;
	
return 0;
}
