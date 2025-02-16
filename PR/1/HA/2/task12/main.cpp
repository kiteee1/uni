#include<iostream>
#include<cmath>
using namespace std;
int main() {

	int n1, n2;
	
	cout << "Enter first number: ";
	cin >> n1;
	cout << "Enter second number: ";
	cin >> n2;

	if (n1%n2==0) cout << n2 <<" divides " << n1 << endl;
	else cout << n2 << " does not divide " << n1 << endl;

	return 0;
}
