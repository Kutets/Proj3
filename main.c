#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

int main() {
  ListaDeTarefas lista;
  lista.qtd = 0;
  int sair = 0;

  carregarLista(&lista, "tarefas.bin");

  while (!sair) {
    printf("\nMenu:\n");
    printf("1. Cadastrar Tarefa\n");
    printf("2. Deletar Tarefa\n");
    printf("3. Listar por prioridade\n");
    printf("4. Print todas as tarefas\n");
    printf("6. Editar Tarefas\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");

    char entrada[100];
    fgets(entrada, sizeof(entrada), stdin);
    int opcao = atoi(entrada);

    if (opcao < 1 || opcao > 5) {
      printf("Opção inválida. Tente novamente.\n");
      continue; // Volta para o início do loop
    }

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

          if (indice < 0 || indice >= lista.qtd) {
            printf("Índice inválido. Nada foi deletado.\n");
            getchar(); // Limpa o caractere de nova linha pendente
          } else {
            getchar(); // Limpa o caractere de nova linha pendente
            deletarTarefa(&lista, indice);
            salvarLista(lista, "tarefas.bin");
          }
        } else {
          printf("A lista de tarefas está vazia. Nada para deletar.\n");
        }
        break;
      case 3:
        if (lista.qtd > 0) {
          int prioridadeEscolhida;
          printf("Digite a prioridade das tarefas que deseja listar: ");
          scanf("%d", &prioridadeEscolhida);
          getchar(); // Limpa o caractere de nova linha pendente
          listarPrioridade(&lista, prioridadeEscolhida);
        } else {
          printf("A lista de tarefas está vazia.\n");
        }
        break;
      case 4:
        if (lista.qtd > 0){
          printf("Todas as tarefas\n");
          listarTarefas(lista);
        }
      break;
      case 6:
        if (lista.qtd > 0) {
          printf("Detalhes da tarefa antes da edição:\n");
          printTarefa(&(lista.tarefas[0]));
          editarTarefa(&lista, 0);
          salvarLista(lista, "tarefas.bin");
        } else {
          printf("A lista de tarefas está vazia. Nada para editar.\n");
        }
        break;
      case 10:
        sair = 1;
        break;
    }
  }

  printf("Programa encerrado.\n");

  return 0;
}