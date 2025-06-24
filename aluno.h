// B2 ALGORITMOS 2 TRABALHO AVALIATIVO 4
// Arthur Kaun, Gabriella Andrade, Klaiver Coutinho, Rafael Pagotto

#ifndef ALUNO_H
#define ALUNO_H

#define MAX_NOME 51
#define MAX_MATRICULA 15
#define MAX_LIVROS_EMPRESTADOS 2

typedef struct {
    char nome[MAX_NOME];
    char matricula[MAX_MATRICULA];
    int livrosEmprestados;
} Aluno;

int cadastrarAluno(const char* arquivo);
int matriculaExiste(const char* arquivo, const char* matricula);
int podeEmprestar(const char* arquivo, const char* matricula);
void listarAlunos(const char* arquivo);

#endif