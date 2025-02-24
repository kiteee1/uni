#include<iostream>
using namespace std;

int main() {

	int int_value = 2147483647;
	unsigned int unsigned_value = 2147483647;
	long long_value = 2147483647;
	double double_value = 2147483647;

	int_value++;
	unsigned_value++;
	long_value++;
	double_value++;

	cout << "int result: " << int_value << endl;
	cout << "unsigned result: " << unsigned_value << endl;
	cout << "long result: " << long_value << endl;
	cout << "double result: " << double_value << endl;

	return 0;
}
