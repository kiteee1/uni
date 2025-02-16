#include<iostream>
using namespace std;

int main() {

	int number, result {0}, counter{0};
	
	cout << "Number: ";
	cin >> number;
	
	for (; number>0; number=number/10) {
		result=result+number%10;
		counter++;
		if (counter>3) {
			cout << "Please enter a valid number" << endl;
			exit(1);
		}
	}
	if (counter!=3) {
			cout << "Please enter a valid number" << endl;
			exit(1);
		}
	
	if (result%3==0) cout << "Result is divisible by 3" << endl;
	else 	cout << "Result is not divisible by 3" << endl;

	return 0;

}
