#include<iostream>
#include<vector>
using namespace std;

int main() {

	double limit_up, limit_down, num;
	vector<double> numbers;
	int below{0}, within{0}, above{0};
	
	cout << "Lower limit: ";
	cin >> limit_down;
	cout << "Upper limit: ";
	cin >> limit_up;

	cout << "Numbers: ";
	while (cin >> num) numbers.push_back(num);
	
	for(double i:numbers){
		if (i<limit_down) below++;
		else if (i<=limit_up && i>=limit_down) within++;
		else above++; 
	}
	
	cout << "Below: " << below << endl;
	cout << "Within: " << within << endl;
	cout << "Above: " << above << endl;
	
	return 0;
}
