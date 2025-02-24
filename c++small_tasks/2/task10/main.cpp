#include<iostream>
using namespace std;

int main() {
	int kegs, liters;

	cout << "Enter the keg capacity: ";
	cin >> liters;
	cout << "Enter the order quantity: ";
	cin >> kegs;
	
	if (kegs>0 && liters>0) {
		if (kegs%liters!=0) {
			kegs = kegs / liters;
			kegs++;
		}
		else kegs = kegs / liters;
		cout << "You need " << kegs << " keg(s) to complete the order" << endl;
	}
	return 0;
}
