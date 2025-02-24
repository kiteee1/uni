#include <iostream>
#include <string>
using namespace std;

string add_strings(string num1, string num2) {
	int i = num1.length() - 1;
	int j = num2.length() - 1;
	int carry = 0;
	string result = "";

	while (i >= 0 || j >= 0 || carry) {
		int sum = carry;
		if (i >= 0) {
			sum += num1[i] - '0';
			i--;
		}
		if (j >= 0) {
			sum += num2[j] - '0';
			j--;
		}
		carry = sum / 10;
		result = to_string(sum % 10) + result;
	}

	return result;
}

int main() {
	string num1, num2; 
	
	cout << "Number 1: ";
	cin >> num1;
	cout << "Number 2: ";
	cin >> num2;
	
	string sum = add_strings(num1, num2);

	cout << "Sum: " << sum << endl;
    
	return 0;
}
