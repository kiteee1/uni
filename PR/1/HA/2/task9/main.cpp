#include<iostream>
#include<random>
#include<cmath>
using namespace std;

int main() {

	double amount, bet;
	int trials;
	short r_number;

  random_device random_device;
  mt19937 gen(random_device());
  uniform_int_distribution<short> range(0, 36);
  
  cout << "Amount: ";
	cin >> bet;
  cout << "Number of trials: ";
  cin >> trials;
  amount=bet;
  
	if (bet>=0 && trials>=0) {
		for (int counter=0; counter<=trials; ++counter) {
			r_number = range(gen);
			cout << "\nResult: " << r_number << endl;
			if (r_number!=0) {
				cout << "\nYou lose!";
				amount=amount-bet;				
			}
			else {
				cout << "You win!";
				break;
			}
		}
		if (amount<=0) cout << "\nYou lost " << abs(amount-bet) << endl;
		else cout << "\nYou've got jackpot! You win money 35 times your bet! Know you have " << amount+bet*35 << endl;
	}
	else cout << "Please enter valid values" << endl;
	return 0;
}

