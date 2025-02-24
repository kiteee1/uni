#include<iostream>
using namespace std;

int binomial(int n, int k) {
	if(k==0 || k==n)
		return 1;
	return binomial(n-1, k-1) + binomial(n-1, k);
}

int main() {
	int n, k;
	
	cout << "n: ";
	cin >> n;
	cout << "k: ";
	cin >> k;
	
	cout << "Binomial coefficient: " << binomial(n, k) << endl;
	return 0;
}
