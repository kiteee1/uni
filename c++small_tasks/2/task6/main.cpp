#include<iostream>
using namespace std;

int main() {

	double a, b, c, x, result;
	
	cout << "ax^2+bx+c\na: ";
	cin >> a;
	cout << "b: ";
	cin >> b;
	cout << "c: ";
	cin >> c;
	cout << "x: ";
	cin >> x;
	
	result = c+x*(b+x*a); // Rewritten second order polinomial using Horner's method
	cout << "Result: " << result << endl;

	return 0;

}
