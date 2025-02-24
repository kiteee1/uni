#include<iostream>
#include<vector>
using namespace std;

int main() {

	int input;
	vector<int> numbers;
	
	cout << "4-digit integer: ";
	cin >> input;
	
	if (input<1000 ||input>9999) {
		cout << "Please enter a valid number" << endl;
		return 1;
	}
	
	int temp = input;
	for (int i=3; i>=0; i--) {
		numbers.insert(numbers.begin() ,temp%10);
		temp = temp / 10;
	}
	
	short counter = 0;
	for (int i: numbers){
		if (counter==1 || counter==2 || counter==3) cout << "-";
		if (i==0) cout << "zero";
		if (i==1) cout << "one";
		if (i==2) cout << "two";
		if (i==3) cout << "three";
		if (i==4) cout << "four";
		if (i==5) cout << "five";
		if (i==6) cout << "six";
		if (i==7) cout << "seven";
		if (i==8) cout << "eight";
		if (i==9) cout << "nine";
		counter++;
	}
	cout << endl;
	
	
	
	return 0;
}
