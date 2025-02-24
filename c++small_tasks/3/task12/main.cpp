#include <iostream>

using namespace std;

int main() {

	int number;
	cout << "Input: ";
	cin >> number;

	if (number <= 0) {
		cout << "Please enter a valid value." << endl;
	}
	
	else {
	
		int divisors_sum = 0;
		
		for (int i = 1; i < number; i++) {
		
			if (number % i == 0) {
				divisors_sum += i;
			}
			
		}

		if (divisors_sum == number) {
			cout << "perfect" << endl;
		}
		
		else if (divisors_sum < number) {
			cout << "deficient" << endl;
		}
		
		else {
			cout << "abundant" << endl;
		}
		
	}

return 0;
}
