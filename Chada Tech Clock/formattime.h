
#ifndef FORMATTIME_H
#define FORMATTIME_H
#include <string>

std::string twoDigitString(unsigned int userNumber);
std::string formatTime12(unsigned int hours, unsigned int minutes, unsigned int seconds);
std::string formatTime24(unsigned int hours, unsigned int minutes, unsigned int seconds);

#endif
