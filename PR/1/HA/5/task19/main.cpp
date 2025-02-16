#include <iostream>
#include <string>
using namespace std;

void generate_combinations(const string& characters, int length, string current) {
	if (length == 0) {
		cout << current << endl;
		return;
	}
	for (char c : characters) {
		generate_combinations(characters, length - 1, current + c);
	}
}

int main() {
	string charset;
	int number;
	
	cout << "Enter a number: ";
	cin >> number;
	
	charset = to_string(number);
	int length = charset.length();
	generate_combinations(charset, length, "");

return 0;
}
