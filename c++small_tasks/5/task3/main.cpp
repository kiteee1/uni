#include <iostream>
#include <vector>
using namespace std;

vector<double> f(const vector<double>& vector1, const vector<double>& vector2, size_t index1, size_t index2) {
	if (index1 == vector1.size() && index2 == vector2.size()) return {};  
	vector<double> result;

	if (index1 < vector1.size()) 
		result.push_back(vector1[index1]);

	if (index2 < vector2.size())
		result.push_back(vector2[index2]);

	vector<double> recursive_result = f(vector1, vector2, index1 + 1, index2 + (index2 < vector2.size()));
	result.insert(result.end(), recursive_result.begin(), recursive_result.end());
	return result;
}

int main() {
	vector<double> vector1 = {1, 2, 3, 4, 5, 6};
	vector<double> vector2 = {7, 8, 9};

	vector<double> result = f(vector1, vector2, 0, 0);

	cout << "{";
	
	for (size_t i = 0; i < result.size(); ++i) {
		cout << result[i];
		if (i < result.size() - 1) {
			cout << ",";
		}
	}
	
	cout << "}" << endl;

    return 0;
}
