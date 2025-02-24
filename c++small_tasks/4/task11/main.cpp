#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string transform(string input) {
	string odd, even, output;
	
	for (size_t i = 0; i<input.length(); ++i) {
		if (i % 2 == 0)
			even.push_back(input[i]);
		else
			odd.push_back(input[i]);
	}
	reverse(even.begin(), even.end());
	output = odd + even;
	return output;
}

int main() {
	string input;
	
	cout << "Parameter: ";
	cin >> input;
	
	cout << "Return: " << transform(input) << endl;
	return 0;
}
