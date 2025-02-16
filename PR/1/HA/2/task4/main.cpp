#include<iostream>
using namespace std;

int main() {

	int worker, pieces, workerquestion;
	cin >> worker >> pieces >> workerquestion;
	//cout << pieces/worker*workerquestion; Incorect because of operation order
	cout << (pieces*workerquestion)/worker << endl; // 1st method to use parentheses to ensure the operation order
	cout << static_cast<double>(pieces) * workerquestion / worker << endl;// 2nd use static_cast
	
	return 0;
}
