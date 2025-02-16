#include<iostream>
#include<string>
using namespace std;

void generate_permutations(string &str, int start, int end) {
	if (start == end) {
		cout << str << " ";
		return;
	}
	
	for (int i = start; i <= end; ++i) {
		char temp = str[start];
		str[start] = str[i];
		str[i] = temp;
		generate_permutations(str, start + 1, end);
		temp = str[start];
		str[start] = str[i];
		str[i] = temp;
	}
}

int main() {
	string input;
	int number;
	
	cout << "Enter a number: ";
	cin >> number;
	
	input = to_string(number);
	
	int n = input.length();
	generate_permutations(input, 0, n - 1);
return 0;
}
