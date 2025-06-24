// B2 ALGORITMOS 2 TRABALHO AVALIATIVO 4
// Arthur Kaun, Gabriella Andrade, Klaiver Coutinho, Rafael Pagotto

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#include "auxiliar.h"

int matriculaExiste(const char* arquivo, const char* matricula) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        return 0;
    }

    char linha[256];
    char nome[MAX_NOME], mat[MAX_MATRICULA];
    int livrosEmprestados;

    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = '\0';
        int campos = sscanf(linha, "%49[^;];%19[^;];%d", nome, mat, &livrosEmprestados);
        if (campos >= 2 && strcmp(mat, matricula) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

int cadastrarAluno(const char* arquivo) {

    Aluno a;
    printf("Matricula: ");
    lerString(a.matricula, MAX_MATRICULA);
    if (matriculaExiste(arquivo, a.matricula)) {
        printf("Matricula ja cadastrada!\n");
        return 0;
    }
    printf("Nome do aluno: ");
    lerString(a.nome, MAX_NOME);

    a.livrosEmprestados = 0;

    FILE *fp = fopen(arquivo, "a");
    if (!fp) {
        printf("Erro ao abrir arquivo de alunos!\n");
        return 0;
    }

    fprintf(fp, "%s;%s;%d\n", a.nome, a.matricula, a.livrosEmprestados);
    fclose(fp);
    printf("Aluno cadastrado com sucesso!\n");
    return 1;
}

int podeEmprestar(const char* arquivo, const char* matricula) {

    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Arquivo de alunos nao encontrado.\n");
        return 0;
    }

    Aluno a;
    while (fscanf(fp, "%49[^;];%19[^;];%d\n", a.nome, a.matricula, &a.livrosEmprestados) == 3) {
        if (strcmp(a.matricula, matricula) == 0) {
            fclose(fp);
            return a.livrosEmprestados < MAX_LIVROS_EMPRESTADOS;
        }
    }

    fclose(fp);
    printf("Matricula nao encontrada.\n");
    return 0;
}

void listarAlunos(const char* arquivo) {

    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Arquivo de alunos nao encontrado.\n");
        return;
    }

    Aluno a;
    int count = 0;
    printf("\n--- Lista de Alunos ---\n");
    while (fscanf(fp, "%49[^;];%19[^;];%d\n", a.nome, a.matricula, &a.livrosEmprestados) == 3) {
        printf("Nome: %s | Matricula: %s | Livros emprestados: %d\n", a.nome, a.matricula, a.livrosEmprestados);
        count++;
    }

    if (count == 0) {
        printf("Nenhum aluno cadastrado!\n");
    }
    
    fclose(fp);
}