#include<iostream>
#include<cmath>
using namespace std;

int main() {

	double x;
	
	cout << "x: ";
	cin >> x;

	int round_x = round(x);
	
	cout << "Rounded: " << round_x << endl;

	return 0;
}
