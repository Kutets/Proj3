#ifndef PROJET_1_BIBLIOTECA_H
#define PROJET_1_BIBLIOTECA_H
// Cria três estados das tarefas
typedef enum {
  CONCLUIDO = 1,
  EM_ANDAMENTO = 2,
  NAO_CONCLUIDO = 3
} EstadoTarefa;

// Cria a estrutura de tarefa, dando 3 parâmetros, priroidade, categoria e descrição
typedef struct {
  int prioridade;
  char categoria[100];
  char descricao[300];
  EstadoTarefa estado;
} Tarefa;

// Cria a lista de tarefas
typedef struct {
  Tarefa tarefas[100];
  int qtd;
} ListaDeTarefas;



// Variaveis
void cadastrarTarefa(ListaDeTarefas *lt);
int deletarTarefa(ListaDeTarefas *lt, int indice);
void listarTarefas(ListaDeTarefas lt);
void salvarLista(ListaDeTarefas lt, const char *tarefas);
void carregarLista(ListaDeTarefas *lt, const char *tarefas);
void editarTarefa(ListaDeTarefas *lt, int indice);
void printTarefa(Tarefa *tarefa);
void listarPrioridade(ListaDeTarefas *lt, int prioridade);
#endif // PROJET_1_BIBLIOTECA_H
