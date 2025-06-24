// B2 ALGORITMOS 2 TRABALHO AVALIATIVO 4
// Arthur Kaun, Gabriella Andrade, Klaiver Coutinho, Rafael Pagotto

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "auxiliar.h"

void lerString(char* buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void obterDataAtual(char* buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void calcularDataDevolucao(const char* dataEmprestimo, char* dataDevolucao) {
    int dia, mes, ano;
    sscanf(dataEmprestimo, "%d/%d/%d", &dia, &mes, &ano);
    struct tm tm = {0};
    tm.tm_mday = dia + 7;
    tm.tm_mon = mes - 1;
    tm.tm_year = ano - 1900;
    mktime(&tm);
    sprintf(dataDevolucao, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}