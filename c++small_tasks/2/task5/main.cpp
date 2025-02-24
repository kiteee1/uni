#include<iostream>
#include<cmath>
using namespace std;

int main() {

	double x1, y1, z1, x2, y2, z2, distance;
	
	cout << "A(x1, y1, z1) B(x2, y2, z2)\nx1: ";
	cin >> x1;
	cout << "y1: ";
	cin >> y1;
	cout << "z1: ";
	cin >> z1;
	cout << "x2: ";
	cin >> x2;
	cout << "y2: ";
	cin >> y2;
	cout << "z2: ";
	cin >> z2;
	
	distance = sqrt(pow((x2-x1), 2)+pow((y2-y1), 2)+pow((z2-z1), 2));
	cout << "Distance AB: " << distance << endl;

	return 0;

}
