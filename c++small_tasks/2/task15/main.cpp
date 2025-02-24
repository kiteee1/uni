#include<iostream>
using namespace std;

int main() {
	int kegs, liters;

	cout << "Enter the keg capacity: ";
	cin >> liters;
	cout << "Enter the order quantity: ";
	cin >> kegs;
	
	cout << "You need " << (kegs+liters-1)/liters << " keg(s) to complete the order" << endl;
	
	return 0;
}
