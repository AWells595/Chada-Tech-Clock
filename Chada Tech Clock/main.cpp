#include<iostream>
#include<string>
#include<thread> // for thread 
#include<ctime> // for time() and localtime_s()
#include<Windows.h> // for sleep()
#include "Clock.h"
#include "formattime.h"

// declared in global scope so main() can set value to false and stop thread from running when program should terminate
static bool updateLoop = true;
using namespace std;

string nCharString(size_t n, char c);
void printMenu(string strings[], unsigned int numStrings, unsigned char width);
void displayClocks(unsigned int h, unsigned int m, unsigned int s);
int getMenuChoice();
void addOneSecond(Clock &userClock);
void addOneMinute(Clock &userClock);
void addOneHour(Clock &userClock);
void updateClock(Clock &userClock);

int main() {
	Clock clock;
	tm localTime; // struc to hold time from localtime function later
	int systemHour, systemMinute, systemSecond;
	int userChoice = 0;\

	time_t now = time(0); // time since epoch
	localtime_s(&localTime, &now); // populates localTime with local system time, EST in my case
	 
	// each call stores the hour, minute, then second from the localTime struct
	systemHour = localTime.tm_hour;
	systemMinute = localTime.tm_min;
	systemSecond = localTime.tm_sec; 
	
	// then set the attributes of the clock to the new data
	clock.setHours(systemHour);
	clock.setMinutes(systemMinute);
	clock.setSeconds(systemSecond);

	// since the .join() function needs to be after the loop, updateThread must be initialized in main() scope rather than in the loop
	thread updateThread(updateClock, ref(clock));

	do {
		userChoice = getMenuChoice();

		if (userChoice == 1) {
			addOneHour(clock);
		}
		else if (userChoice == 2) {
			addOneMinute(clock);

		}
		else if (userChoice == 3) {
			addOneSecond(clock);

		}
		else if (userChoice == -1) {
			cout << "Invalid Input" << endl;
		}
		else if (userChoice == 4) {
			updateLoop = false;
		}
	} while (userChoice != 4);
	updateThread.join(); // ends update loop
	return 0;
}

void updateClock(Clock& userClock) {
	string strings[4] = { "Add One Hour", "Add One Minute", "Add One Second", "Exit Program" };  // easiest to declare in this scope rather than pass from main
	// loops until main() changes update loop to false, which is right before thread is joined
	while (updateLoop) {
		displayClocks(userClock.getHours(), userClock.getMinutes(), userClock.getSeconds());
		printMenu(strings, 4, 27);
		addOneSecond(userClock);
		Sleep(1000);
		cout << flush;
		system("CLS"); // clears console for new time and menu display
	}
}

string nCharString(size_t n, char c) {
	string formattedString;

	for (int i = 0; i < n; i++) {
		formattedString = formattedString + c;
	}
	return formattedString;
}

void printMenu(string strings[], unsigned int numStrings, unsigned char width) {
	int spacesNeeded;
	const int widthAdjustment = 7; // width gets subtracted by 7 to account for the 7 characters at that start of the line and the * at the end

	cout << nCharString(16, ' ') << nCharString(width, '*') << endl; // 16 spaces before * centers menu below clocks per specifications
	// 4 loops for now, but easily expandable if more options are added
	for (int i = 0; i < numStrings; i++) {
		if ((i < numStrings - 1)) {
			spacesNeeded = (width - widthAdjustment) - strings[i].length();  // spaces from end of string to border *
			cout << nCharString(16, ' ') << "* " << i + 1 << " - " << strings[i] << nCharString(spacesNeeded, ' ') << "*" << endl << endl;
		}
		else {
			spacesNeeded = (width - widthAdjustment) - strings[i].length();
			cout << nCharString(16, ' ') << "* " << i + 1 << " - " << strings[i] << nCharString(spacesNeeded, ' ') << "*" << endl;
		}
	}
	cout << nCharString(16, ' ') << nCharString(width, '*') << endl;
	return;
}

void displayClocks(unsigned int hours, unsigned int minutes, unsigned int seconds) {
	string time12Hours = formatTime12(hours, minutes, seconds);
	string time24Hours = formatTime24(hours, minutes, seconds);

	// spacing numbers from client specification
	cout << nCharString(27, '*') << nCharString(3, ' ') << nCharString(27, '*')<<endl;
	cout << nCharString(1, '*') << nCharString(6, ' ') << "12-HOUR CLOCK" << nCharString(6, ' ') << nCharString(1, '*') << nCharString(3, ' ');
	cout << nCharString(1, '*') << nCharString(6, ' ') << "24-HOUR CLOCK" << nCharString(6, ' ') << nCharString(1, '*') << endl << endl;
	cout << nCharString(1, '*') << nCharString(6, ' ') << time12Hours << nCharString(7, ' ') << nCharString(1, '*') << nCharString(3, ' ');
	cout << nCharString(1, '*') << nCharString(8, ' ') << time24Hours << nCharString(9, ' ') << nCharString(1, '*') << endl;
	cout << nCharString(27, '*') << nCharString(3, ' ') << nCharString(27, '*') << endl;
}

int getMenuChoice() {
	int userInput;
	cin >> userInput;

	if (userInput <= 0 || userInput >= 5) {
		userInput = -1; // invalid input
	}
	return userInput;
}

void addOneSecond(Clock &userClock) {
	int currentSecond = userClock.getSeconds();

	if (currentSecond + 1 >= 60) {
		currentSecond = 0;
		addOneMinute(userClock);
	}
	else {
		currentSecond++;
	}
	userClock.setSeconds(currentSecond);
	return;
}

void addOneMinute(Clock &userClock) {
	int currentMinute = userClock.getMinutes();

	if(currentMinute + 1 >= 60){
		currentMinute = 0;
		addOneHour(userClock);
	}
	else {
		currentMinute++;
	}
	userClock.setMinutes(currentMinute);
	return;
}

void addOneHour(Clock &userClock) {
	int currentHour = userClock.getHours();

	if (currentHour + 1 >= 24) {
		currentHour = 0;
	}
	else {
		currentHour++;
	}
	userClock.setHours(currentHour);
	return;
}