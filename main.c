#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"
// Luiz Fernando de Oliveira Lopes RA: 22.123.013-9
// Larissa Santos Fiuza RA: 22.123.042-8
// Cria a estrutura de tarefa, dando 3 parâmetros, priroidade, categoria e descrição

int main() {
  ListaDeTarefas lista;
  lista.qtd = 0;
  int sair = 0;

  carregarLista(&lista, "tarefas.bin");

  while (!sair) {
    printf("\nMenu:\n");
    printf("1. Cadastrar Tarefa\n");
    printf("2. Deletar Tarefa\n");
    printf("3. Listar Tarefas\n");
    printf("4. Editar Tarefa\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");

    char entrada[100];
    fgets(entrada, sizeof(entrada), stdin);
    int opcao = atoi(entrada);

    switch (opcao) {
      case 1:
        cadastrarTarefa(&lista);
        salvarLista(lista, "tarefas.bin");
        break;
      case 2:
        if (lista.qtd > 0) {
          int indice;
          printf("Digite o índice da tarefa a ser deletada: ");
          scanf("%d", &indice);
          getchar(); // Limpa o caractere de nova linha pendente
          deletarTarefa(&lista, indice);
          salvarLista(lista, "tarefas.bin");
        } else {
          printf("A lista de tarefas está vazia. Nada para deletar.\n");
        }
        break;
      case 3:
        listarTarefas(lista);
        break;
      case 4:
        printf("Detalhes da tarefa antes da edição:\n");
        editarTarefa(&lista, 0);
        salvarLista(lista, "tarefas.bin");
        break;
      case 5:
        sair = 1;
        break;
      default:
        printf("Opção inválida. Tente novamente.\n");
    }
  }

  printf("Programa encerrado. \n");

  return 0;
}

