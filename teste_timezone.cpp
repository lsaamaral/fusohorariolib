#include <iostream>
#include <ctime>
#include "adjust_timezone.hpp"

int main() {
    std::string inputDateTime;
    std::cout << "Enter date and time in format YYYYMMDD hh:mm:ss: ";
    std::getline(std::cin, inputDateTime);

    int year, month, day, hour, minutes, seconds;
    if (sscanf(inputDateTime.c_str(), "%4d%2d%2d %2d:%2d:%2d", &year, &month, &day, &hour, &minutes, &seconds) != 6) {
        std::cerr << "Invalid input format." << std::endl;
        return 1;
    }

    // Adjust the time for GMT -3 timezone
    std::time_t adjustedTime = adjustTimeToGMTMinus3(year, month, day, hour, minutes, seconds);

    // Convert the time_t value to a tm structure for display
    struct tm* adjustedTm = std::localtime(&adjustedTime);

    // Format the adjusted date and time
    char adjustedDateTime[20];
    std::strftime(adjustedDateTime, sizeof(adjustedDateTime), "%Y%m%d %H:%M:%S", adjustedTm);

    std::cout << "Adjusted date and time: " << adjustedDateTime << std::endl;

    return 0;
}
