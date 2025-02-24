#include<iostream>
#include<string>
using namespace std;

bool intTest(int n, char c) {
	string n_string = to_string(n);
	
	for (char i:n_string) {
		if (i==c)
			return true;
	}
	return false;
}

int main() {
	int n;
	char c;
	
	cout << "n: ";
	cin >> n;
	cout << "c: ";
	cin >> c;

	if (intTest(n,c))
		cout << "Occurs? YES" << endl;	
	else 
		cout << "Occurs? NO" << endl;
		
	return 0;
}
