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

string multiply_strings(string num1, string num2) {
	int m = num1.length();
	int n = num2.length();
	string result = "0";

	for (int i = n - 1; i >= 0; i--) {
		string intermediate_result;
		int carry = 0;

		for (int j = m - 1; j >= 0; j--) {
			int product = (num2[i] - '0') * (num1[j] - '0') + carry;
			carry = product / 10;
			intermediate_result = to_string(product % 10) + intermediate_result;
		}

		if (carry > 0) {
			intermediate_result = to_string(carry) + intermediate_result;
		}

		intermediate_result += string(n - 1 - i, '0');
		result = add_strings(result, intermediate_result);
	}

	return result;
}

int main() {
	string num1, num2; 
	
	cout << "Number 1: ";
	cin >> num1;
	cout << "Number 2: ";
	cin >> num2;
	
	string sum = multiply_strings(num1, num2);

	cout << "Sum: " << sum << endl;
    
	return 0;
}
