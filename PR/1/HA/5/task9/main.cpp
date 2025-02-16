#include <iostream>
using namespace std;

bool intTest(int n, char c) {
	if (n == 0) return false;
	if (n % 10 == (c - '0')) return true;  
	else return intTest(n / 10, c);
}

int main() {
	int number;
	char digit;
	
	cout << "Number: ";
	cin >> number;
	cout << "Enter a digit to test: ";
	cin >> digit;
	
	if (intTest(number, digit)) 
		cout << digit << " is present in the number " << number << "." << endl;

	else 
		cout << digit << " is not present in the number " << number << "." << endl;

	return 0;
}
