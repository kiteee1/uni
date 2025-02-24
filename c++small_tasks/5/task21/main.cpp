#include <iostream>
using namespace std;

long long A(int m,int n) {
	if (m == 0) return n+1;
	if (m > 0 && n == 0) return A(m-1, 1);
	if (m > 0 && n > 0) return A(m-1, A(m, n-1));
}

int main() {
	int n, m;
	
	cout << "Enter the value of m: ";
	cin >> m;
	cout << "Enter the value of n: ";
	cin >> n;
	
	if (n < 0 || m < 0) 
		cout << "Invalid input. n and m should be a non-negative integer." << endl;
	else 
		cout << "A(" << m << ", " << n << ") = " << A(m, n) << endl;
	
return 0;
}
