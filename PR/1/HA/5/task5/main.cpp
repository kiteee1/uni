#include <iostream>
#include <vector>

using namespace std;

void cout_combinations(int n, vector<int>& current_combination, int last_summand) {
	if (n == 0) {
		for (int i = 0; i < current_combination.size(); ++i) {
			cout << current_combination[i];
			if (i < current_combination.size() - 1) {
				cout << "+";
			}
		}
		cout << endl;
		return;
	}
	for (int i = 1; i <= last_summand && i <= n; ++i) {
		current_combination.push_back(i);
		cout_combinations(n - i, current_combination, i);
		current_combination.pop_back();
	}
}

void generate_sum_combinations(int n) {
	vector<int> current_combination;
	cout_combinations(n, current_combination, n);
}

int main() {
	int n;
	
	cout << "n: ";
	cin >> n;
	
	generate_sum_combinations(n);
	return 0;
}
