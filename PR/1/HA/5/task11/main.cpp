#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string transform(const string& input, size_t index = 0, string odd = "", string even = "") {
    if (index >= input.length()) {
        reverse(even.begin(), even.end());
        return odd + even;
    }

    if (index % 2 == 0)
        even.push_back(input[index]);
    else
        odd.push_back(input[index]);

    return transform(input, index + 1, odd, even);
}

int main() {
	string input;
	
	cout << "Parameter: ";
	cin >> input;
	
	cout << "Return: " << transform(input) << endl;
	return 0;
}
