#include<iostream>
using namespace std;

int main() {

	int n;
	
	cout << "n: ";
	cin >> n;

	cout << "\nAddition\n" << endl;
	for(int i =  0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cout << (i+j)%n << " ";
		}
		cout << endl;
	}
	
	cout << "\nMultiplication\n" << endl;
	for(int i =  0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cout << (i*j)%n << " ";
		}
		cout << endl;
	}
	
	return 0;
}
