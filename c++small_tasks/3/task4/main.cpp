#include<iostream>
using namespace std;

int main() {

	int n;
	long long factorial = 1;
	
	cout << "n: ";
	cin >> n;
	
	if (n<0) cout << "Please enter valid value" << endl;
	else {
		for (int i = 1; i <=n; ++i) factorial = factorial * i;
	}
	
	cout << n << "! = " << factorial << endl;
	
	return 0;
}
