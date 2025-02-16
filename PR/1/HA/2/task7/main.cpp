#include<iostream>
using namespace std;

int main() {
	
	double a_double, a_cent_double;
	int a, a_cent, d, e, d_cent, e_cent, c_counter {0};
	
	cout << "Amount(dollars/euros)(int): ";
	cin >> a_double;
	cout << "Cents(dollars/euros): ";
	cin >> a_cent_double;
	
	a = static_cast<int>(a_double);
	a_cent = static_cast<int>(a_cent_double);
	
	cout << a << endl;
	cout << a_cent << endl;
	
	if (a>=0 && a_cent>=0) {
		while (a_cent>=100) {
			a_cent=a_cent-100;
			c_counter++;
		}
		
		d=(a+c_counter)*1.0555;
		d_cent = a_cent*1.0555;
		e=(a+c_counter)/1.0555;
		e_cent = a_cent/1.0555;
		
		if (d_cent>=100) {d_cent=d_cent-100; d++;}
		if (e_cent>=100) {e_cent=d_cent-100; e++;}
		
		cout << "Euro -> Dollars: \nDollars: " << d << " Dollar cents: " << d_cent << endl;
		cout << "\nDollars -> Euro: \nEuro: " << e << " Euro cents: " << e_cent << endl;
	}
	
	else cout << "Enter valid value\n";
	
	return 0;

}
