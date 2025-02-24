#include<iostream>
using namespace std;

int main() {

	int n;
	long long result{0}, term{1};
	
	cout << "n: ";
	cin >> n;

	for (int i = 1; i<=n; ++i) {
		for (int j =1; j<=i; ++j) {
			term = term * i;
		}
		result = result + term;
		term = 1;
	}
	
	cout << "Sum: " << result << endl;
	
	return 0;
}
