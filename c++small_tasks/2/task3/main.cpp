#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main() {

	string number;
	
	cout << "Number: ";
	cin >> number;
	
	if (number.length()!=3) {
			cout << "Please enter a 3-digit number" << endl;
			exit(1);
	}
	
	reverse(number.begin(), number.end());
	cout << number << endl;

	return 0;

}
