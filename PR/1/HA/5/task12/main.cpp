#include <iostream>
#include <cmath>
using namespace std;

int count_representations(int n, int start = 1) {
	if (2 * n < start * (start + 1)) return 0;
	
	if ((2 * n - start * (start - 1)) % (2 * start) == 0) 
		return 1 + count_representations(n, start + 1);
	
	else return count_representations(n, start + 1);
}

int main() {
	int number;
	
	cout << "Number: ";
	cin >> number;	
	cout << "Number of representations for " << number << ": " << count_representations(number)-1 << endl;
return 0;
}
