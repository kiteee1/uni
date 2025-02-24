#include <iostream>
#include <vector>
using namespace std;

vector<int> swap_vector(vector<int> input, size_t index = 0) {
	if (index >= input.size() - 1) return input;

	int temp = input[index];
	input[index] = input[index + 1];
	input[index + 1] = temp;

	return swap_vector(input, index + 2);
}

int main() {
	vector<int> input, output;
	int temp;
	cout << "Input vector(Crrz+D to dinish input): ";
	while (cin >> temp) 
		input.push_back(temp);
	output = swap_vector(input);
	cout << "Output: ";
	for (int num : output)
		cout << num << " ";
	cout << endl;
	return 0;
}
