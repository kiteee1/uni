#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string reverse_task(string input) {
	reverse(input.begin(), input.end());
	return input;
}

int main() {
	string input;
	
	cout << "String: ";
	cin >> input;
	
	input = reverse_task(input);
	
	cout << "Reversed: " << input << endl;
	return 0;
}
