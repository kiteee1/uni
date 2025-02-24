#include<iostream>
#include<string>
using namespace std;

string sort_task(string input) {
	char first_char = input[0];
	string larger_chars, lesser_chars;
	
	if(input.empty())
		return input;
		
	for (unsigned int i = 1; i<input.length(); i++) {
		if (input[i] < first_char)
			lesser_chars += input[i];
		else 
			larger_chars += input[i];
	}
		
	return lesser_chars + first_char + larger_chars;
}

int main() {
	string input;
	
	cout << "String: ";
	cin >> input;
	
	input = sort_task(input);
	
	cout << "Sorted: " << input << endl;
	return 0;
}
