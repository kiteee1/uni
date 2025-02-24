#include<iostream>
#include<cmath>
using namespace std;

int main() {
	
	constexpr int seconds_in_year{31536000}, seconds_in_day{86400}, seconds_in_hour{3600}, seconds_in_minute{60};
	
	short choice;
	double seconds{0}, years{0}, days{0}, hours{0}, minutes{0}, whole_seconds;
	long whole_seconds_int;
	
	cout << "Convert seconds(0) or vice versa(1)? ";
	cin >> choice;
	
	if (choice==0) {
	
				cout << "Seconds: ";
				cin >> seconds;
				if (seconds<0) {cout << "Please enter valid value" << endl; exit(1);}
				seconds = modf(seconds, &whole_seconds);
				whole_seconds_int = static_cast<long>(whole_seconds);
				
				while (whole_seconds_int>=seconds_in_year) {
					years++;
					whole_seconds_int = whole_seconds_int-seconds_in_year;
				}

				while (whole_seconds_int>=seconds_in_day) {
					days++;
					whole_seconds_int = whole_seconds_int-seconds_in_day;
				}
				while (whole_seconds_int>=seconds_in_hour) {
					hours++;
					whole_seconds_int = whole_seconds_int-seconds_in_hour;
				}
				while (whole_seconds_int>=seconds_in_minute) {
					minutes++;
					whole_seconds_int = whole_seconds_int-seconds_in_minute;
				}
				
				seconds=seconds+whole_seconds_int;
				
				cout << "Years: " << years << endl;
				cout << "Days: " << days << endl;
				cout << "Hours: " << hours << endl;
				cout << "Minutes: " << minutes << endl;
				cout << "Seconds: " << seconds << endl; 

	}
	
	else if (choice == 1) {
		cout << "Years: ";
		cin >> years;
		if (years<0) {cout << "Please enter valid value" << endl; exit(1);}
		cout << "Days: ";
		cin >> days;
		if (days<0) {cout << "Please enter valid value" << endl; exit(1);}
		cout << "Hours: ";
		cin >> hours;
		if (hours<0) {cout << "Please enter valid value" << endl; exit(1);}
		cout << "Minutes: ";
		cin >> minutes;
		if (minutes<0) {cout << "Please enter valid value" << endl; exit(1);}
		cout << "Seconds: ";
		cin >> seconds;
		if (seconds<0) {cout << "Please enter valid value" << endl; exit(1);}
		
		seconds = seconds+(minutes*seconds_in_minute)+(hours*seconds_in_hour)+(days*seconds_in_day)+(years*seconds_in_year);
		
		cout << "Seconds: " << seconds << endl;
	
	}
	
	else {cout << "Please enter valid value" << endl; exit(1);}
	return 0;

}
