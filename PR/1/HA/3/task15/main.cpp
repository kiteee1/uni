#include <iostream>
#include <string>
#include <vector>
using namespace std;

string digits[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

string digit_to_word(char digit) {
	return digits[digit - '0'];
}


string integer_to_words(int number) {
	if (number == 0) {
	return digit_to_word('0');
	}

	string words;
	while (number > 0) {
		int digit = number % 10;
		words = digit_to_word('0' + digit) + "-" + words;
		number /= 10;
	}
	return words;
}


string number_to_words(double real_number) {
	int integer_part = static_cast<int>(real_number);
	double decimal_part = real_number - integer_part;

	string integer_words = integer_to_words(integer_part);
	string decimal_str = to_string(decimal_part).substr(2); 
	string decimal_words;
	
	for (char digit : decimal_str) {
		decimal_words += digit_to_word(digit) + "-";
	}
	
	return integer_words + "point-" + decimal_words;
}

int main() {
	double real_number;

	cout << "Enter a real number: ";
	cin >> real_number;

	string verbal_representation = number_to_words(real_number);
	cout << "Verbal representation: " << verbal_representation << endl;

return 0;
}
