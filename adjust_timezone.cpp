#include "adjust_timezone.hpp"

namespace {
    // Funcao auxiliar para verificar se um ano e bissexto
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
}

std::time_t adjustTimeToGMTMinus3(int year, int month, int day, int hour, int minutes, int seconds) {
    // Verifica se o ano e bissexto e ajusta a quantidade de dias de fevereiro
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year)) {
        daysInMonth[1] = 29; // Fevereiro tem 29 dias em anos bissextos
    } else {
        daysInMonth[1] = 28; // Fevereiro tem 28 dias em anos nao bissextos
    }

    // Verifica se o dia fornecido e valido para o mes atual
    if (day > daysInMonth[month - 1]) {
        // Se nao for valido, ajusta para o ultimo dia valido do mes
        day = daysInMonth[month - 1];
    }

    // Ajusta os anos e meses se o fuso horario causar mudanca de mes ou ano
    if (hour < 3) {
        if (month == 1) { // Janeiro (mes 1)
            month = 12; // Dezembro (mes 12)
            year--;
        } else {
            month--;
        }
        // Verifica se o dia ajustado e valido para o mes anterior
        if (day > daysInMonth[month - 1]) {
            // Se nao for valido, ajusta para o ultimo dia valido do mes
            day = daysInMonth[month - 1];
        }
    }

    // Constroi a estrutura tm com os valores fornecidos
    std::tm localTime;
    localTime.tm_sec = seconds;
    localTime.tm_min = minutes;
    localTime.tm_hour = hour;
    localTime.tm_mday = day;
    localTime.tm_mon = month - 1; // tm_mon representa o mes de 0 a 11
    localTime.tm_year = year - 1900; // tm_year representa o ano desde 1900
    localTime.tm_isdst = -1; // Configura o flag para determinar horario de verao (usando valor -1)

    // Converte a estrutura tm para segundos desde a epoch (1 de janeiro de 1970)
    std::time_t adjustedTime = std::mktime(&localTime);

    // Adiciona o ajuste do fuso horario -3 em segundos
    adjustedTime -= 3 * 3600;

    // Calcula a diferenca em segundos entre o tempo ajustado e o original
    int timeDifference = static_cast<int>(adjustedTime - std::mktime(&localTime));

    // Verifica se o ajuste do fuso horario faz com que o tempo resultante seja menor que o original
    if (timeDifference < 0) {
        // Se for o caso, ajusta o tempo em mais 24 horas (86400 segundos) para corrigir esse problema
        adjustedTime += 24 * 3600;
    }

    return adjustedTime;
}
