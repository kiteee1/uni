#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int char_to_value(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	}
	else if (c >= 'A' && c <= 'Z') {
		return c - 'A' + 10;
	}

	return -1;
}

char value_to_char(int val) {
	if (val >= 0 && val <= 9) {
		return '0' + val;
	}
	else if (val >= 10 && val <= 35) {
		return 'A' + (val - 10);
	}

	return '\0';
}

string convert_base(const string& input, int base1, int base2) {
	if (base1 < 1 || base2 < 1 || base1 > 30 || base2 > 30) {
		return "Invalid base values.";
	}

	int decimal_value = 0;
	for (char c : input) {
		int digit_value = char_to_value(c);
		if (digit_value == -1 || digit_value >= base1) {
			return "Invalid input string for the given base1.";
		}
		decimal_value = decimal_value * base1 + digit_value;
	}

	string result;
	while (decimal_value > 0) {
		int remainder = decimal_value % base2;
		result = value_to_char(remainder) + result;
		decimal_value /= base2;
	}

	return result;
}

int main() {
	string input;
	int base1, base2;

	cout << "Enter the input string: ";
	cin >> input;
	cout << "Enter base1 (from 1 to 30): ";
	cin >> base1;
	cout << "Enter base2 (from 1 to 30): ";
	cin >> base2;

	string result = convert_base(input, base1, base2);

	if (result == "Invalid base values." || result == "Invalid input string for the given base1.") {
		cout << "Invalid input. " << result << endl;
	}
	else {
		cout << "Result: " << result << endl;
	}

return 0;
}
