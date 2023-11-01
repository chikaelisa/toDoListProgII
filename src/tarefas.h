#ifndef tarefas // Evitar inclusões múltiplas acidentais
#define tarefas

struct Tarefa
{
    int id;
    char descricao[150];
    int status;
};
typedef struct Tarefa Tarefa;

void iniciarTarefas(int opcao);
void consultarTarefas(int status);
int cadastrarTarefa(Tarefa tarefa);
void retiraCaracterString(char *string);
int obtemUltimoIndiceString(char *string);

#endif //autenticar