#ifndef ADJUST_TIMEZONE_H
#define ADJUST_TIMEZONE_H

#include <ctime>

std::time_t adjustTimeToGMTMinus3(int year, int month, int day, int hour, int minutes, int seconds);

#endif // ADJUST_TIMEZONE_H
