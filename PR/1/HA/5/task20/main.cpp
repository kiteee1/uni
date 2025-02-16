#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<int> generate_permutations(string str, int start, int end) {
	vector<int> result;
	
	if (start == end) {
		result.push_back(stoi(str));
		return result;
	}
	
	for (int i = start; i <= end; ++i) {
		char temp = str[start];
		str[start] = str[i];
		str[i] = temp;
		vector<int> sub_permutations = generate_permutations(str, start + 1, end);
		result.insert(result.end(), sub_permutations.begin(), sub_permutations.end());
		temp = str[start];
		str[start] = str[i];
		str[i] = temp;
	}
	
	return result;
}

int main() {
	string input;
	int number;
	
	cout << "Enter a number: ";
	cin >> number;
	
	input = to_string(number);
	int n = input.length();
	vector<int> permutations = generate_permutations(input, 0, n - 1);
	
	cout << "Permutations: ";
	for (int perm : permutations) {
		cout << perm << " ";
	}
	
return 0;
}
