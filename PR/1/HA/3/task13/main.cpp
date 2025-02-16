#include <iostream>
#include <vector>
using namespace std;

int main() {

	const int range = 10000000;
	vector<int> numbers;

	for (int i = 2; i <= range; i++) {
	
		int sum_of_divisors = 1;
		 
		for (int j = 2; j * j <= i; j++) {
		
			if (i % j == 0) {
				sum_of_divisors += j;
					if (j != i / j) {
						sum_of_divisors += i / j;
					}
				}
			}
		
		if (sum_of_divisors == i - 1) {
			numbers.push_back(i);
		}
		
	}

	cout << "Output:" << endl;
	
	for (int num : numbers) {
		cout << num << " ";
	}

	return 0;
}
