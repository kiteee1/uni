#include<iostream>
#include<string>
using namespace std;

string caesar(string input_string, int n) {
	string output_string;
	
	for(char c:input_string) {
	
		if (isalpha(c)) {
		
			char lower_c = tolower(c);
			int c_ascii = lower_c - 'a';
			int encoded_c_ascii = (c_ascii + n) % 26;
			char encoded_c = encoded_c_ascii + 'a';
			
			if (isupper(c)) encoded_c = toupper(encoded_c);
			
			output_string.push_back(encoded_c);
		}
		else output_string.push_back(c);
	}
	return output_string;
}

int main() {
	string input_string;
	int n;
	
	cout << "Enter string to enconde and key-integer n: ";
	while (cin >> input_string >> n) {
		cout << "Encoded: " << caesar(input_string, n) << endl;
		cout << "Enter string to enconde and key-integer n: ";
	}	
	
	return 0;
}
