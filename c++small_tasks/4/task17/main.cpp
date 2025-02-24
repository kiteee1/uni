#include <iostream>
#include <string>
using namespace std;

int find_first_char_position(const std::string& input, char character) {
	bool within_quotes = false;
	for (unsigned int i = 0; i < input.length(); ++i) {
		if (input[i] == '\"') {
			within_quotes = !within_quotes;
		}
		else if (!within_quotes && input[i] == character) {
			return i;
		}
	}
	return -1;
}

int main() {
	string input;
	char character;

	cout << "String: ";
	getline(cin, input);
	cout << "Character: ";
	cin >> character;

	int position = find_first_char_position(input, character);

	if (position != -1) {
		cout << "Character '" << character << "' first appears at position " << position << endl;
	}
	else {
		cout << "Character '" << character << "' not found in the string." << endl;
	}

	return 0;
}
