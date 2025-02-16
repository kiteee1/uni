#include<iostream>
using namespace std;

int sequence(int n) {
	if (n==1) return 1;
	else if (n%2==0) return n/2;
	else return 3*n+1;
}

int main() {

	int n;
	
	cout << "Enter positive n: ";
	cin >> n;
	
	if (n<=0) {
		cout << "Please enter valid value" << endl;
		return 1;
	} 
	
	cout << "Sequence: ";
	
	while (n!=1) {
		cout << n << " ";
		n=sequence(n);
	}
	
	cout << "1" << endl;
	
	return 0;
}
