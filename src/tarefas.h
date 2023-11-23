#ifndef tarefas // Evitar inclusões múltiplas acidentais
#define tarefas

struct Tarefa
{
    char id;
    char descricao[150];
    int status;
};
typedef struct Tarefa Tarefa;

void iniciarTarefas(int opcao, char usuarioLogin[], char caminhoLogin[]);
void consultarTarefas(char caminho[]);
int cadastrarTarefa(Tarefa tarefa, char caminho[]);
void retiraCaracterString(char *string);
int obtemUltimoIndiceString(char *string);
char obtemUltimoIdTarefas(FILE *arquivo);
char* obtemCaminho(char *username);
int alterarTarefa(char caminho[]);
int excluirTarefa(char caminho[]);

#endif //autenticar