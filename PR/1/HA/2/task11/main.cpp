#include<iostream>
#include<cmath>
using namespace std;
int main() {

	double n;
	
	cout << "Enter a number: ";
	cin >> n;

	if (floor(n) == n) cout << "An integer" << endl;
	else cout << "Not an integer" << endl;

	return 0;
}
