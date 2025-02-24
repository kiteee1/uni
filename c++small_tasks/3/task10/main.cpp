#include <iostream>
#include <string>
using namespace std;

int main() {
	string expression;
	double result = 0;
	char current_operator = '+';

	cout << "Expression: ";
	cin >> expression;

	for (char& c : expression) {
		if (c == '!') {
			break;
		}
		if (c == '+' || c == '-' || c == '*' || c == '/') {
			current_operator = c;
		} 
		else {
			double number = c - '0';
			while (cin.peek() >= '0' && cin.peek() <= '9') {
				cin >> c;
				number = number * 10 + (c - '0');
			}

			if (current_operator == '+') {
				result += number;
			} 
			else if (current_operator == '-') {
				result -= number;
			} 
			else if (current_operator == '*') {
				result *= number;
			} 
			else if (current_operator == '/') {
				if (number != 0) {
					result /= number;
				} 
				else {
					cout << "Error: Division by zero!" << endl;
					return 1;
				}
			}
		}
	}

	cout << "Output: " << result << endl;

	return 0;
}
