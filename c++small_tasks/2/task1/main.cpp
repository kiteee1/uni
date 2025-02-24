#include<iostream>
#include<cmath>
using namespace std;

int main() {

	int m, n;
	
	cout << "m=";
	cin >> m;
	cout << "n=";
	cin >> n;
	
	int result = m/int((pow(10,n-1)))%10;
	
	cout << result << endl;
	
	return 0;

}
