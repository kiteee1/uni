#include <iostream>
#include <vector>
using namespace std;

double mean(const vector<double>& values, size_t index = 0, double sum = 0) {
	if (index == values.size()) 
		return values.size() > 0 ? sum / values.size() : 0;
		
	else
		return mean(values, index + 1, sum + values[index]);
}

int main() {
	vector<double> values;
	double temp;
	cout << "Enter values(Ctrl+D to finish): ";
	while (cin >> temp)
		values.push_back(temp);
	cout << "Mean: " << mean(values) << endl;
	
	return 0;
}
