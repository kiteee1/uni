#include<iostream>
#include<cmath>
using namespace std;

int main() {

	double p, q, d, x;
	
	cout << "x^2+px+q" << endl;
	cout << "p: ";
	cin >> p;
	cout << "q: ";
	cin >> q;
	
	d=p*p-4*q;
	
	if (d>0) {
		x=(-p+sqrt(d))/2;
		cout << "x1: " << x << endl;
		x=(-p-sqrt(d))/2;
		cout << "x2: " << x << endl;
	}
	else if (d==0) {
		x=(-p)/2;
		cout << "x: " << x << endl;
	}
	else cout << "D<0" << endl;
	
	return 0;
}
