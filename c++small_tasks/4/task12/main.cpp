#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int binomial_coefficient(int n, int k) {
	if (k == 0 || k == n) 
		return 1;
		
	int result = 1;
	for (int i = 1; i <= k; i++) {
		result = result * (n - i + 1) / i;
	}
	return result;
}


string expression(int n) {
	string result = "";

	for (int i = 0; i <= n; i++) {
		int coeff = binomial_coefficient(n, i);

		if (coeff != 0) {
			if (i > 0) {
				result += "+";
			}

			if (coeff != 1) {
				result += to_string(coeff);
			}

			if (n - i > 0) {
				result += "a";
				if (n - i > 1) {
					result += "^" + to_string(n - i);
				}
			}

			if (i > 0) {
				result += "b";
				if (i > 1) {
					result += "^" + to_string(i);
				}
			}
		}
	}
	return result;
}

int main() {
	int n;
	cout << "Arguments: ";
	cin >> n;
	cout << "Return value: " << expression(n) << endl;

return 0;
}
