#include <iostream>
using namespace std;
long long f(int n);

long long h(int n) {
	if (n == 0) return 1;
	return n*h(n-1);
}

long long g(int n) {
	if (n == 0) return 0;
	return 2*f(n);
}

long long f(int n) {
	if (n == 0) return 0;
	return h(n)+g(n-1);
}

int main() {
	int n;
	
	cout << "Enter the value of n: ";
	cin >> n;
	
	if (n < 0) 
		cout << "Invalid input. n should be a non-negative integer." << endl;
	else 
		cout << "f(n) = " << f(n) << endl;
	
return 0;
}
