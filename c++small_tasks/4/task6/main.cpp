#include<iostream>
using namespace std;

int gcd(int a, int b) {
	if (b==0) return a;
	return gcd(b, a % b);
}

int main() {
	int a, b;
	
	cout << "a: ";
	cin >> a;
	cout << "b: ";
	cin >> b;
	
	cout << "Greatest common denominator: " << gcd(a, b) << endl;
	return 0;
}
