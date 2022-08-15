#ifndef CLOCK_H
#define CLOCK_H
class Clock {
	unsigned int hours, minutes, seconds;

public:
	Clock() { // initializing to current time
		hours = 21;
		minutes = 51;
		seconds = 07;
	}

	unsigned int getHours() {
		return hours;
	}

	unsigned int getMinutes() {
		return minutes;
	}

	unsigned int getSeconds() {
		return seconds;
	}

	void setHours(unsigned int userHours) {
		hours = userHours;
		return;
	}

	void setMinutes(unsigned int userMinutes) {
		minutes = userMinutes;
		return;
	}

	void setSeconds(unsigned int userSeconds) {
		seconds = userSeconds;
	}
};
#endif