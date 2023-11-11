#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

// Função de atualizar a lista toda vez que ela for usada
void salvarLista(ListaDeTarefas lt, const char *tarefas) {
  FILE *arquivo = fopen(tarefas, "wb");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo para escrita.\n");
    return;
  }

  fwrite(&lt, sizeof(ListaDeTarefas), 1, arquivo);
  fclose(arquivo);
}
// Carregar a lista quando precisar acessá-la
void carregarLista(ListaDeTarefas *lt, const char *tarefas) {
  FILE *arquivo = fopen(tarefas, "rb");
  if (arquivo == NULL) {
    printf("Arquivo de lista não encontrado. Iniciando com lista vazia.\n");
    return;
  }

  fread(lt, sizeof(ListaDeTarefas), 1, arquivo);
  fclose(arquivo);
}

// Função de criar a tarefa, dando os parâmetros necessaríos
void cadastrarTarefa(ListaDeTarefas *lt) {
  if (lt->qtd < 100) {
    Tarefa novaTarefa;
    printf("Digite a prioridade da tarefa: ");
    scanf("%d", &novaTarefa.prioridade);
    getchar(); // Limpa o caractere de nova linha pendente
    printf("Digite a categoria da tarefa: ");
    fgets(novaTarefa.categoria, sizeof(novaTarefa.categoria), stdin);
    novaTarefa.categoria[strlen(novaTarefa.categoria) - 1] = '\0'; 
    // Remove o caractere de nova linha
    printf("Digite a descrição da tarefa: ");
    fgets(novaTarefa.descricao, sizeof(novaTarefa.descricao), stdin);
    novaTarefa.descricao[strlen(novaTarefa.descricao) - 1] = '\0'; 
    printf("Digite o estado da tarefa (1 para Concluído, 2 para Em Andamento, 3 para Não Concluído): ");
    scanf("%d", (int*)&novaTarefa.estado);
    lt->tarefas[lt->qtd] = novaTarefa;
    lt->qtd++;
    printf("Tarefa cadastrada com sucesso!\n");
  } else {
    printf("A lista de tarefas está cheia. Não é possível cadastrar mais tarefas.\n");
  }
}


// Função para listar tarefas com uma prioridade específica
void listarPrioridade(ListaDeTarefas *lt, int prioridade) {
  for (int i = 0; i < lt->qtd; i++) {
    if (lt->tarefas[i].prioridade == prioridade) {
      printTarefa(&(lt->tarefas[i]));
      printf("\n");
    }
  }
}
//Função para listar tarefas com um estado específico
void listarEstado(ListaDeTarefas *lt, EstadoTarefa estado) {
  printf("Tarefas com estado %d:\n", (int)estado);
  for (int i = 0; i < lt->qtd; i++) {
    if (lt->tarefas[i].estado == estado) {
      printTarefa(&(lt->tarefas[i]));
      printf("\n");
    }
  }
}



// Compara as tarefas através da prioridade
int compararTarefas(const void *a, const void *b) {
  return ((Tarefa *)a)->prioridade - ((Tarefa *)b)->prioridade;
}

// Listar as tarefas a partir do nível de prioridade, junto do índice
void listarTarefas(ListaDeTarefas lt) {
  if (lt.qtd == 0) {
    printf("A lista de tarefas está vazia.\n");
    return;
  }

  qsort(lt.tarefas, lt.qtd, sizeof(Tarefa), compararTarefas);

  for (int i = 0; i < lt.qtd; i++) {
    printf("Tarefa %d - Prioridade %d: %s - %s - %d\n", i, lt.tarefas[i].prioridade, lt.tarefas[i].categoria, lt.tarefas[i].descricao, lt.tarefas[i].estado);
  }
}



// Deletar a tarefa através do índice indicado ao listar as tarefas criadas
int deletarTarefa(ListaDeTarefas *lt, int indice) {
  if (indice < 0 || indice >= lt->qtd) {
    printf("Índice inválido. A tarefa não pode ser excluída.\n");
    return 0;
  }

  for (int i = indice; i < lt->qtd - 1; i++) {
    lt->tarefas[i] = lt->tarefas[i + 1];
  }

  lt->qtd--;
  printf("Tarefa excluída com sucesso!\n");
  return 1;
}

// Imprime a tarefa selecionada para ed
void printTarefa(Tarefa *tarefa) {
  printf("Prioridade: %d\n", tarefa->prioridade);
  printf("Categoria: %s\n", tarefa->categoria);
  printf("Descrição: %s\n", tarefa->descricao);
  printf("Estado: %d\n", (int)tarefa->estado);
}

// Editar tarefa
void editarTarefa(ListaDeTarefas *lt, int indice) {
  if (indice >= 0 && indice < lt->qtd) {
    Tarefa *tarefa = &(lt->tarefas[indice]);

    printf("Escolha o campo para editar:\n");
    printf("1. Prioridade\n");
    printf("2. Categoria\n");
    printf("3. Descrição\n");
    printf("4. Estado\n");

    int escolha;
    printf("Digite o número correspondente ao campo desejado: ");
    scanf("%d", &escolha);

    switch (escolha) {
      case 1:
        printf("Digite a nova prioridade da tarefa: ");
        scanf("%d", &tarefa->prioridade);
        break;
      case 2:
        printf("Digite a nova categoria da tarefa: ");
        getchar(); // Limpa o caractere de nova linha pendente
        fgets(tarefa->categoria, sizeof(tarefa->categoria), stdin);
        tarefa->categoria[strlen(tarefa->categoria) - 1] = '\0';
        break;
      case 3:
        printf("Digite a nova descrição da tarefa: ");
        getchar(); // Limpa o caractere de nova linha pendente
        fgets(tarefa->descricao, sizeof(tarefa->descricao), stdin);
        tarefa->descricao[strlen(tarefa->descricao) - 1] = '\0';
        break;
      case 4:
        printf("Digite o novo estado da tarefa (1 para Concluído, 2 para Em Andamento, 3 para Não Concluído): ");
        scanf("%d", (int*)&tarefa->estado);
        break;
      default:
        printf("Escolha inválida. Nenhum campo foi alterado.\n");
        return;
    }

    printf("Tarefa editada com sucesso!\n");
  } else {
    printf("Índice inválido. Não foi possível editar a tarefa.\n");
  }
}
