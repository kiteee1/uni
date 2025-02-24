#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string reverse_loop(string to_reverse) {
	string reversed;
	
	for (int i = to_reverse.length() - 1; i>=0; i--)
		reversed += to_reverse.at(i);
	return reversed;
}

string reverse_recursion(string to_reverse, int start, int end) {
	if (start >= end) return to_reverse;
	
	char temp = to_reverse.at(start);
	to_reverse.at(start) = to_reverse.at(end);
	to_reverse.at(end) = temp;
	
	return reverse_recursion(to_reverse, start+1, end-1);
}

int main (){
	string input;
	
	cout << "Enter string: ";
	cin >> input;
	
	cout << reverse_loop(input) << endl;
	cout << reverse_recursion(input, 0, input.length() - 1) << endl;	

	return 0;
}
