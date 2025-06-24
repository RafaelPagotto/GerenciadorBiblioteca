// B2 ALGORITMOS 2 TRABALHO AVALIATIVO 4
// Arthur Kaun, Gabriella Andrade, Klaiver Coutinho, Rafael Pagotto

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "livro.h"
#include "aluno.h"
#include "auxiliar.h"

#define ARQ_LIVROS "biblioteca.txt"
#define ARQ_ALUNOS "alunos.txt"

int main() {
    int opcao;
    do {
        printf("\n--- Biblioteca ---\n");
        printf("1. Cadastrar Livro\n");
        printf("2. Cadastrar Aluno\n");
        printf("3. Listar Alunos\n");
        printf("4. Emprestar Livro\n");
        printf("5. Devolver Livro\n");
        printf("6. Listar Livros (Todos)\n");
        printf("7. Listar Livros Disponiveis\n");
        printf("8. Listar Livros Emprestados\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                cadastrarLivro(ARQ_LIVROS);
                break;
            case 2:
                cadastrarAluno(ARQ_ALUNOS);
                break;
            case 3:
                listarAlunos(ARQ_ALUNOS);
                break;
            case 4:
                emprestarLivro(ARQ_LIVROS, ARQ_ALUNOS);
                break;
            case 5:
                devolverLivro(ARQ_LIVROS, ARQ_ALUNOS);
                break;
            case 6:
                listarLivros(ARQ_LIVROS, 0); // todos
                break;
            case 7:
                listarLivros(ARQ_LIVROS, 1); // disponíveis
                break;
            case 8:
                listarLivros(ARQ_LIVROS, 2); // emprestados
                break;
            case 0:
                printf("\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

        system("pause");
        system("cls");

    } while(opcao != 0);

    return 0;
}