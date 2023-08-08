#include <stdio.h>
#include "adjust_timezone.hpp"

int main(){
    int year = 0, month = 0, day = 0, hour = 0, minutes = 0, seconds = 0;
    scanf("%d %d %d %d %d %d", &year, &month, &day, &hour, &minutes, &seconds);

    // Ajusta o tempo para o fuso horario -3
    std::time_t adjustedTime = adjustTimeToGMTMinus3(year, month, day, hour, minutes, seconds);

    // Converte o tempo ajustado para a estrutura tm
    struct tm *timeinfo;
    timeinfo = localtime(&adjustedTime);

    // Obtem os componentes da data e hora ajustados
    year = timeinfo->tm_year + 1900;
    month = timeinfo->tm_mon + 1;
    day = timeinfo->tm_mday;
    hour = timeinfo->tm_hour;
    minutes = timeinfo->tm_min;
    seconds = timeinfo->tm_sec;

    // Imprime os valores ajustados
    printf("%d %d %d %d %d %d\n", year, month, day, hour, minutes, seconds);

    return 0;
}
