#include <iostream>
#include <vector>

using namespace std;

int main() {
	int num, inversions{0};
	vector<int> digits;
	cout << "Input: ";
	cin >> num;

	if (num < 0) {
		cout << "Please enter a non-negative integer." << endl;
		return 1;
	}

	while (num > 0) {
		digits.insert(digits.begin(), num % 10);
		num /= 10;
	}

	for (unsigned int i = 0; i < digits.size(); ++i) {
		for (unsigned int j = i + 1; j < digits.size(); ++j) {
			if (digits[i] > digits[j]) {
				inversions++;
			}
		}
	}

	cout << "Output: " << inversions << endl;
	return 0;
}
