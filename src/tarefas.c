#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tarefas.h"

void iniciarTarefas(int opcao)
{

    Tarefa tarefa;
  
    consultarTarefas(0);

    switch (opcao)
    {
      case 0:
        printf("\nO que voce deseja fazer?\n");
        printf("1 - Listar tarefas\n");
        printf("2 - Cadastrar tarefa\n");
        printf("3 - Excluir tarefa\n");
        printf("4 - Atualizar tarefa\n");
        printf("5 - Fechar programa\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        setbuf(stdin, NULL);
        iniciarTarefas(opcao);
        return;
        break;
      case 1:
        printf("\n** CONSULTA DE TAREFA **\n\n");
        printf("Digite o tipo de status da tarefa: ");
        scanf("%d", &opcao);
        consultarTarefas(opcao);
        iniciarTarefas(0);
        return;
        break;
      case 2:
        printf("\n** CADASTRO DE TAREFA **\n\n");
        printf("Informe um ID para a tarefa (numero): ");
        scanf("%d", &tarefa.id);
        setbuf(stdin, NULL);
        printf("Informe a descricao da tarefa: ");
        fgets(tarefa.descricao, 150, stdin);
        retiraCaracterString(tarefa.descricao);
        cadastrarTarefa(tarefa);
        iniciarTarefas(0);
        return;
        break;
      case 4:
      case 5:
        exit(1);
        break;
      default:
        break;
    }
}

int cadastrarTarefa(Tarefa tarefa)
{
    char caminho[65];
    tarefa.status = 0;
    strcpy(caminho, "arqUsuario\\Enzo.txt");
    FILE *caminhoTarefas = fopen(caminho, "a");
    fprintf(caminhoTarefas, "%d - %s %d\n", tarefa.id, tarefa.descricao, tarefa.status);
    fprintf(caminhoTarefas, "");
    fclose(caminhoTarefas);
    printf("Tarefa cadastrada com sucesso!\n");
    return 1;
}

void consultarTarefas(int status)
{
    char caminho[65];
    char linha[150];
    int controle = 0;
    strcpy(caminho, "arqUsuario\\Enzo.txt");
    FILE *caminhoConsultarTarefa = fopen(caminho, "r");

    while(fgets(linha, 150, caminhoConsultarTarefa) != NULL)
    {
        int ultimoIndice = obtemUltimoIndiceString(linha);
        if (status == 0)
        {
            if (linha[ultimoIndice] == '0')
              printf("%.*s ( )\n", ultimoIndice-1, linha);
        }
        else
        {
            if (linha[ultimoIndice] == '1')
              printf("%.*s ( X )\n", ultimoIndice-1, linha);
        }
        controle = 1;
    }

    if (!controle)
    {
        printf("Nao ha tarefas cadastradas!\n");
        fclose(caminhoConsultarTarefa);
        return;
    }

    fclose(caminhoConsultarTarefa);
}

void retiraCaracterString(char *string)
{
    //Lê a quantidade de caracteres da string
    int n = strlen(string);
    //Remove o \n da string
    if ((n > 0) && (string[n-1] == '\n'))
        string[n-1] = '\0';
}

int obtemUltimoIndiceString(char *string)
{
    int n = strlen(string);

    if (string[n-1] == '\n')
      n -= 2;
    else 
      n -= 1;

    return n;
}

/*
char* obtemCaminho(char *usuario)
{
    char *caminhoTarefa = (char*) malloc(65 * sizeof(char));
    strcpy(caminhoTarefa, "arqUsuario\\");
    strcat(caminhoTarefa, usuario);
    strcat(caminhoTarefa, ".txt");
    return caminhoTarefa;
}
*/