// B2 ALGORITMOS 2 TRABALHO AVALIATIVO 4
// Arthur Kaun, Gabriella Andrade, Klaiver Coutinho, Rafael Pagotto

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"
#include "aluno.h"
#include "auxiliar.h"

int cadastrarLivro(const char* arquivo) {

    Livro l;
    printf("Titulo do livro: ");
    lerString(l.titulo, MAX_TITULO);
    printf("Autor: ");
    lerString(l.autor, MAX_AUTOR);
    strcpy(l.status, "Disponivel");
    strcpy(l.matricula, "");
    strcpy(l.dataEmprestimo, "");
    strcpy(l.dataDevolucao, "");

    FILE *fp = fopen(arquivo, "a");
    if (!fp) {
        printf("Erro ao abrir arquivo de livros!\n");
        return 0;
    }

    fprintf(fp, "%s;%s;%s;%s;%s;%s\n", l.titulo, l.autor, l.status, l.matricula, l.dataEmprestimo, l.dataDevolucao);
    fclose(fp);
    printf("Livro cadastrado com sucesso!\n");
    return 1;
}

void listarLivros(const char* arquivo, int filtrarStatus) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Arquivo de livros nao encontrado.\n");
        return;
    }

    Livro l;
    int count = 0;
    char linha[512];
    printf("\n--- Lista de Livros ---\n");
    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = '\0';
        int campos = sscanf(linha, "%99[^;];%49[^;];%14[^;];%19[^;];%10[^;];%10[^;]",
            l.titulo, l.autor, l.status, l.matricula, l.dataEmprestimo, l.dataDevolucao);
        if (campos < 3) continue;

        if ((filtrarStatus == 1 && _stricmp(l.status, "Disponivel") != 0) || (filtrarStatus == 2 && _stricmp(l.status, "Emprestado") != 0)) {
            continue;
        }
        printf("Titulo: %s | Autor: %s | Status: %s", l.titulo, l.autor, l.status);

        if (_stricmp(l.status, "Emprestado") == 0) {
            printf(" | Matricula: %s | Emprestimo: %s | Devolucao: %s", l.matricula, l.dataEmprestimo, l.dataDevolucao);
        }
        printf("\n");
        count++;
    }

    if (count == 0) printf("Nenhum livro listado!\n");
    fclose(fp);
}

int emprestarLivro(const char* arquivoLivros, const char* arquivoAlunos) {
    char titulo[MAX_TITULO], matricula[MAX_MATRICULA];
    printf("Titulo do livro para emprestar: ");
    lerString(titulo, MAX_TITULO);
    printf("Matricula do aluno: ");
    lerString(matricula, MAX_MATRICULA);

    if (!podeEmprestar(arquivoAlunos, matricula)) {
        printf("Aluno ja possui 2 livros emprestados ou matricula nao encontrada.\n");
        return 0;
    }

    FILE *fp = fopen(arquivoLivros, "r");
    FILE *tmp = fopen("tmp_livros.txt", "w");
    if (!fp || !tmp) {
        printf("Erro ao abrir arquivos de livros.\n");
        if(fp) fclose(fp);
        if(tmp) fclose(tmp);
        return 0;
    }

    int achou = 0;
    Livro l;
    char dataHoje[MAX_DATA], dataPrevista[MAX_DATA];
    obterDataAtual(dataHoje);
    calcularDataDevolucao(dataHoje, dataPrevista);

    char linha[512];
    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = '\0';
        int campos = sscanf(linha, "%99[^;];%49[^;];%14[^;];%19[^;];%10[^;];%10[^;]",
            l.titulo, l.autor, l.status, l.matricula, l.dataEmprestimo, l.dataDevolucao);
        if (campos < 3) continue;
        if (campos < 4) l.matricula[0] = '\0';
        if (campos < 5) l.dataEmprestimo[0] = '\0';
        if (campos < 6) l.dataDevolucao[0] = '\0';

        if (!achou && _stricmp(l.titulo, titulo) == 0 && _stricmp(l.status, "Disponivel") == 0) {
            strcpy(l.status, "Emprestado");
            strcpy(l.matricula, matricula);
            strcpy(l.dataEmprestimo, dataHoje);
            strcpy(l.dataDevolucao, dataPrevista);
            achou = 1;
        }
        fprintf(tmp, "%s;%s;%s;%s;%s;%s\n", l.titulo, l.autor, l.status, l.matricula, l.dataEmprestimo, l.dataDevolucao);
    }
    fclose(fp);
    fclose(tmp);

    if (!achou) {
        remove("tmp_livros.txt"); // Não altera o arquivo original
        printf("Livro nao encontrado ou indisponivel.\n");
        return 0;
    }

    remove(arquivoLivros);
    rename("tmp_livros.txt", arquivoLivros);

    FILE *fa = fopen(arquivoAlunos, "r");
    FILE *ta = fopen("tmp_alunos.txt", "w");
    if (!fa || !ta) {
        printf("Erro ao atualizar alunos.\n");
        if(fa) fclose(fa);
        if(ta) fclose(ta);
        return 0;
    }
    Aluno a;
    char linhaAluno[256];
    while (fgets(linhaAluno, sizeof(linhaAluno), fa)) {
        linhaAluno[strcspn(linhaAluno, "\n")] = '\0';
        int campos = sscanf(linhaAluno, "%49[^;];%19[^;];%d", a.nome, a.matricula, &a.livrosEmprestados);
        if (campos >= 2 && strcmp(a.matricula, matricula) == 0) a.livrosEmprestados++;
        fprintf(ta, "%s;%s;%d\n", a.nome, a.matricula, a.livrosEmprestados);
    }
    fclose(fa);
    fclose(ta);
    remove(arquivoAlunos);
    rename("tmp_alunos.txt", arquivoAlunos);

    printf("Livro emprestado com sucesso!\n");
    return 1;
}

int devolverLivro(const char* arquivoLivros, const char* arquivoAlunos) {
    char titulo[MAX_TITULO], matricula[MAX_MATRICULA];
    printf("Titulo do livro para devolucao: ");
    lerString(titulo, MAX_TITULO);
    printf("Matricula do aluno: ");
    lerString(matricula, MAX_MATRICULA);

    FILE *fp = fopen(arquivoLivros, "r");
    FILE *tmp = fopen("tmp_livros.txt", "w");
    if (!fp || !tmp) {
        printf("Erro ao abrir arquivos de livros.\n");
        if(fp) fclose(fp);
        if(tmp) fclose(tmp);
        return 0;
    }

    int achou = 0;
    Livro l;
    char linha[512];
    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = '\0';
        int campos = sscanf(linha, "%99[^;];%49[^;];%14[^;];%19[^;];%10[^;];%10[^;]",
            l.titulo, l.autor, l.status, l.matricula, l.dataEmprestimo, l.dataDevolucao);
        if (campos < 3) continue;
        if (campos < 4) l.matricula[0] = '\0';
        if (campos < 5) l.dataEmprestimo[0] = '\0';
        if (campos < 6) l.dataDevolucao[0] = '\0';

        if (!achou && _stricmp(l.titulo, titulo) == 0 && _stricmp(l.status, "Emprestado") == 0 && _stricmp(l.matricula, matricula) == 0) {
            strcpy(l.status, "Disponivel");
            strcpy(l.matricula, "");
            strcpy(l.dataEmprestimo, "");
            strcpy(l.dataDevolucao, "");
            achou = 1;
            printf("Livro devolvido com sucesso!\n");
        }
        fprintf(tmp, "%s;%s;%s;%s;%s;%s\n", l.titulo, l.autor, l.status, l.matricula, l.dataEmprestimo, l.dataDevolucao);
    }

    fclose(fp);
    fclose(tmp);

    if (!achou) {
        remove("tmp_livros.txt");
        printf("Livro nao encontrado ou nao esta emprestado para esse aluno.\n");
        return 0;
    }

    remove(arquivoLivros);
    rename("tmp_livros.txt", arquivoLivros);

    FILE *fa = fopen(arquivoAlunos, "r");
    FILE *ta = fopen("tmp_alunos.txt", "w");
    Aluno a;
    char linhaAluno[256];
    while (fgets(linhaAluno, sizeof(linhaAluno), fa)) {
        linhaAluno[strcspn(linhaAluno, "\n")] = '\0';
        int campos = sscanf(linhaAluno, "%49[^;];%19[^;];%d", a.nome, a.matricula, &a.livrosEmprestados);
        if (campos >= 2 && strcmp(a.matricula, matricula) == 0 && a.livrosEmprestados > 0) a.livrosEmprestados--;
        fprintf(ta, "%s;%s;%d\n", a.nome, a.matricula, a.livrosEmprestados);
    }
    fclose(fa);
    fclose(ta);
    remove(arquivoAlunos);
    rename("tmp_alunos.txt", arquivoAlunos);

    return 1;
}