#include <ctime>

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

std::time_t adjustTimeToGMTMinus3(int year, int month, int day, int hour, int minutes, int seconds) {
    // Array to store the number of days in each month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Adjust for leap years
    if (isLeapYear(year)) {
        daysInMonth[1] = 29; // February has 29 days in leap years
    }
    
    // Adjust the provided time to GMT -3 timezone
    struct tm localTime;
    localTime.tm_sec = seconds;
    localTime.tm_min = minutes;
    localTime.tm_hour = hour - 3; // Adjust for GMT -3 timezone
    localTime.tm_mday = day;
    localTime.tm_mon = month - 1; // tm_mon represents the month from 0 to 11
    localTime.tm_year = year - 1900; // tm_year represents the year since 1900
    localTime.tm_isdst = -1; // Set the flag to determine daylight saving time (using value -1)

    // Normalize the time (handles changes in days, months, and years)
    std::time_t adjustedTime = std::mktime(&localTime);

    // Return the adjusted time
    return adjustedTime;
}
