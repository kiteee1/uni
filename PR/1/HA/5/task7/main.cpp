#include <iostream>
#include <vector>
using namespace std;

int factorial(int n) {
	if (n == 0 || n == 1) return 1;
	else return n * factorial(n - 1);
}

int binomial(int n, int k) {
	if (k == 0 || k == n) return 1;
	else return factorial(n) / (factorial(k) * factorial(n - k));
}

int binomialPascal(int n, int k) {
	if (k == 0 || k == n) return 1;
	else return binomialPascal(n - 1, k - 1) + binomialPascal(n - 1, k);
}

int binomialFormula(int n, int k) {
	if (k == 0) return 1;

	else {
	int result = 1;
	
	for (int i = 1; i <= k; ++i) {
		result *= (n - k + i);
		result /= i;
	}
	
	return result;
	}
}

int main() {
	int n, k;
	
	cout << "Enter n: ";
	cin >> n;
	cout << "Enter k: ";
	cin >> k;
	
	if(n < k) {
		cout << "Condition n >= k mus be fullfilled." << endl;
		exit(0);
	}
	
	cout << "Binomial coefficient (" << n << ", " << k << ") using factorials: " << binomial(n, k) << endl;
	cout << "Binomial coefficient (" << n << ", " << k << ") using Pascal's triangle: " << binomialPascal(n, k) << endl;
	cout << "Binomial coefficient (" << n << ", " << k << ") using the formula: " << binomialFormula(n, k) << endl;

    return 0;
}
