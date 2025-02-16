#include <iostream>
#include <string>
using namespace std;

string decimal_to_binary(const string& decimal_str) {
	try {
		int decimal_num = stoi(decimal_str);
		if (decimal_num < 0) {
			throw invalid_argument("Input must be a non-negative integer");
		}

		if (decimal_num == 0) {
			return "0";
		}

		string binary_str = "";
		while (decimal_num > 0) {
			int remainder = decimal_num % 2;
			binary_str = to_string(remainder) + binary_str;
			decimal_num /= 2;
		}

		return binary_str;
	}
	catch (const invalid_argument& e) {
		return e.what();
	}
}

string binary_to_decimal(const string& binary_str) {
	try {
		int decimal_num = 0;
		int base = 1;

		for (int i = binary_str.size() - 1; i >= 0; --i) {
			if (binary_str[i] == '1') {
				decimal_num += base;
			}
			base *= 2;
		}

		return to_string(decimal_num);
	}
	catch (const invalid_argument& e) {
		return e.what();
	}
}

int main() {
	while (true) {
		cout << "Choose an option:" << endl;
		cout << "1. Decimal to Binary" << endl;
		cout << "2. Binary to Decimal" << endl;
		cout << "3. Quit" << endl;

		int choice;
		cin >> choice;

		if (choice == 1) {
			cout << "Enter a decimal number: ";
			string decimal_str;
			cin >> decimal_str;
			string binary_str = decimal_to_binary(decimal_str);
			cout << decimal_str << " in binary is " << binary_str << endl;
		}
		else if (choice == 2) {
			cout << "Enter a binary number: ";
			string binary_str;
			cin >> binary_str;
			string decimal_str = binary_to_decimal(binary_str);
			cout << binary_str << " in decimal is " << decimal_str << endl;
		}
		else if (choice == 3) {
			break;
		}
		else {	
			cout << "Invalid choice. Please choose a valid option." << endl;
		}
	}

return 0;
}
