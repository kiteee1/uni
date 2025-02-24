#include<iostream>
#include<vector>
using namespace std;

int main() {

	vector<double> numbers;
	double num, sum{0}, mean;
	
	cout << "Enter values: ";
	while(cin >> num) numbers.push_back(num);

	double min{numbers[0]}, max{numbers[0]};
	
	for (double i:numbers) {
		sum = sum + i;
		if(i<min) min = i;
		if(i>max) max= i;
	}
	
	mean = sum/numbers.size();
	
	cout << "Max:" << max << endl;
	cout << "Min:" << min << endl;
	cout << "Max:" << mean << endl;
	
	return 0;
}
