#include<iostream>
#include<string>
using namespace std;

int count_char(string input_string, char character) {
	int count{0};
	for (char c:input_string) {
		if(c==character) 
			count++;
	}
	return count;
}

int main() {
	string input_string, used_characters;
	int count;
	char character;
	
	cout << "Enter string: ";
	while (getline(cin, input_string)) {
		cout << "Output: ";
		for (unsigned int i = 0; i<input_string.length(); i++) {
			character = input_string[i];
			if (character == ' ') continue;
			size_t found = used_characters.find_first_of (character);
			if (found == string::npos) 
				used_characters.push_back(character);
			else continue;
			count = count_char(input_string, character);
			cout << character << "(" << count << ") ";
		}
		cout << endl;
	}
		
	
	return 0;
}
