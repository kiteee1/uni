#include <iostream>
using namespace std;

int main() {
	int number;
	cout << "Input: ";

	if (cin >> number) {
		int power = 1;

		if (number <= 0) {
			power = 0;
		}
		
		else {
			while (number % 2 == 0) {
				number /= 2;
				power *= 2;
			}
		}
		cout << "Output: " << power << endl;
	}
	
	else {
		cout << "Please enter a valid value." << endl;
	}
	
return 0;
}
