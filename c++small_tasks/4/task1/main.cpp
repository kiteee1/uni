#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string delete_character(string input_string, char to_remove) {
	input_string.erase(remove(input_string.begin(), input_string.end(), to_remove), input_string.end());
	return input_string;
}

int main() {
	string input_string;
	char to_remove;
	
	cout << "Input string: ";
	cin >> input_string;
	cout << "Input character: ";
	while (cin >> to_remove) {
		cout << delete_character(input_string, to_remove) << endl;
		cout << "Input character: ";
	}
	
	return 0;
}

