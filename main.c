#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    printf("5. Print por estado\n");
    printf("6. Editar Tarefas\n");
    printf("7. Print por categoria\n");
    printf("10. Sair\n");
    printf("Escolha uma opção: ");

    char entrada[100];
    fgets(entrada, sizeof(entrada), stdin);
    int opcao = atoi(entrada);

    if (opcao < 1 || opcao > 10) {
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
      case 5:
        if (lista.qtd > 0){
          int estadoEscolhido;
          printf("Digite o estado das tarefas que deseja listar (1 para Concluído, 2 para Em Andamento, 3 para Não Concluído): ");
          scanf("%d", &estadoEscolhido);
          listarEstado(&lista, (EstadoTarefa)estadoEscolhido);
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
      case 7:
      if (lista.qtd > 0){
        char categoriaEscolhida[50];
        printf("Digite a categoria das tarefas que deseja listar: ");
        fgets(categoriaEscolhida, sizeof(categoriaEscolhida), stdin);
        categoriaEscolhida[strlen(categoriaEscolhida) - 1] = '\0'; // Remove a quebra de linha do final
        listarCategoria(&lista, categoriaEscolhida);
        break;
      }
      case 8:
      if (lista.qtd > 0){
          char categoria[50];
          int prioridade;
          printf("Digite a categoria das tarefas que deseja listar: ");
          fgets(categoria, sizeof(categoria), stdin);
          categoria[strlen(categoria) - 1] = '\0';
          // Imprime as tarefas com uma prioridade e categoria escolhidas pelo usuário
          printf("Digite a prioridade das tarefas que deseja listar: ");
          scanf("%d", &prioridade);
          getchar(); // Limpa o caractere de nova linha pendente
          listarCatEPrio(&lista, prioridade, categoria);
          break;
        }
      case 9:
        if (lista.qtd > 0){
          char TarefasPrioridade[50];
          int prioridade;
          printf("Digite o nome do arquivo para exportar as tarefas: ");
          scanf("%s", TarefasPrioridade);

          exportarPrioridade(&lista, prioridade, TarefasPrioridade);
        }
      case 10:
        sair = 1;
        break;
    }
  }

  printf("Programa encerrado.\n");

  return 0;
}