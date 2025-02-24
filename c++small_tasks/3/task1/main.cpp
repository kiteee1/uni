#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {

	double num;
	vector<double> numbers;
	
	cout << "Enter numbers: " << endl;;
	
	while (numbers.size()!=3) {
		cin >> num;
		numbers.push_back(num);
	}

	sort(numbers.begin(), numbers.end());
	
	cout << "Sorted: ";
	for (double i: numbers) cout << i << " ";
	cout << endl;
	
	return 0;
}
