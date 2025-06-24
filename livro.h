// B2 ALGORITMOS 2 TRABALHO AVALIATIVO 4
// Arthur Kaun, Gabriella Andrade, Klaiver Coutinho, Rafael Pagotto

#ifndef LIVRO_H
#define LIVRO_H

#define MAX_TITULO 101
#define MAX_AUTOR 51
#define MAX_STATUS 11
#define MAX_MATRICULA 15
#define MAX_DATA 11

typedef struct {
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    char status[MAX_STATUS];
    char matricula[MAX_MATRICULA];
    char dataEmprestimo[MAX_DATA];
    char dataDevolucao[MAX_DATA];
} Livro;

int cadastrarLivro(const char* arquivo);
void listarLivros(const char* arquivo, int filtrarStatus);
int emprestarLivro(const char* arquivoLivros, const char* arquivoAlunos);
int devolverLivro(const char* arquivoLivros, const char* arquivoAlunos);

#endif