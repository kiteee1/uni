#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string output(int n) {
	string string_n = to_string(n);
	string reverse_n;
	
	for (char i:string_n) {
		reverse_n.push_back(i);
		reverse_n.push_back(' ');
	}
	string_n = reverse_n;
	reverse(reverse_n.begin(), reverse_n.end());
	string_n = reverse_n + " * " + string_n;
	
	return string_n;
}

int main() {
	int n;
	
	cout << "Number: ";
	cin >> n;
	
	cout << "Return:" << output(n) << endl;
	return 0;
}
