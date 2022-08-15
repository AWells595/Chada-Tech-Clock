#include<string>
using namespace std;

/*There is surely an easier way to concentrate the final strings using a C string instead of a std::string
however I prefer the string library for displaying the results over similar C string methods*/

string twoDigitString(unsigned int timeToFormat) {
	string twoDigit;

	if (timeToFormat < 10) {
		twoDigit = "0" + to_string(timeToFormat);
	}

	else {
		twoDigit = to_string(timeToFormat);
	}

	return twoDigit;
}

string formatTime24(unsigned int hours, unsigned int minutes, unsigned int seconds) {
	string formatedTime;

	formatedTime.append(twoDigitString(hours));
	formatedTime.append(":");
	formatedTime.append(twoDigitString(minutes));
	formatedTime.append(":");
	formatedTime.append(twoDigitString(seconds));

	return formatedTime;
}

string formatTime12(unsigned int hours, unsigned int minutes, unsigned int seconds) {
	string formatedTime;
	string amOrPm = " A M";
	if (hours >= 12) { // coverting from 24 hours to 12, hours over 12 get subtracted by 12
		hours = hours - 12;
		amOrPm = " P M";
	}
	if (hours == 0) { // converting from 24 horus to 12, 0 becomes 12 which for this program represents both noon and midnight
		hours = 12;
	}
	formatedTime.append(twoDigitString(hours));
	formatedTime.append(":");
	formatedTime.append(twoDigitString(minutes));
	formatedTime.append(":");
	formatedTime.append(twoDigitString(seconds));
	formatedTime.append(amOrPm);

	return formatedTime;
}
