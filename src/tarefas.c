#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tarefas.h"
#include "autenticar.h"

void iniciarTarefas(int opcao, char usuarioLogin[], char caminhoLogin[])
{
  Tarefa tarefa;
  strcpy(caminhoLogin, usuarioLogin);

  switch (opcao)
  {
  case 0:
    printf("\nSuas tarefas:\n");
    consultarTarefas(obtemCaminho(caminhoLogin));
    printf("\n");
    iniciarTarefas(1, usuarioLogin, caminhoLogin);
    return;
    break;
  case 1:
    printf("╔════════════════════════════════════════╗\n");
    printf("║                  MENU                  ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("(1) - Listar tarefas\n");
    printf("(2) - Cadastrar tarefa\n");
    printf("(3) - Excluir tarefa\n");
    printf("(4) - Atualizar tarefa\n");
    printf("(5) - Sair\n");
    printf("\nDigite sua opcao: ");
    scanf("%d", &opcao);
    system("clear");
    setbuf(stdin, NULL);
    printf("\n");
    iniciarTarefas(opcao + 1, usuarioLogin, caminhoLogin);
    return;
    break;
  case 2:
    printf("╔════════════════════════════════════════╗\n");
    printf("║            CONSULTA DE TAREFAS         ║\n");
    printf("╚════════════════════════════════════════╝\n");
    consultarTarefas(obtemCaminho(caminhoLogin));
    printf("\n");
    iniciarTarefas(1, usuarioLogin, caminhoLogin);
    return;
    break;
  case 3:
    printf("╔════════════════════════════════════════╗\n");
    printf("║            CADASTRO DE TAREFA          ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\nInforme a descricao da tarefa: ");
    fgets(tarefa.descricao, 150, stdin);
    retiraCaracterString(tarefa.descricao);
    cadastrarTarefa(tarefa, obtemCaminho(caminhoLogin));
    iniciarTarefas(1, usuarioLogin, caminhoLogin);
    return;
    break;
  case 4:

    printf("Você selecionou a opção 3, estamos trabalhando nela! Em breve\n\n");
    iniciarTarefas(1, usuarioLogin, caminhoLogin);
    return;
    break;
  case 5:
    printf("Você selecionou a opção 4, estamos trabalhando nela! Em breve\n\n");
    iniciarTarefas(1, usuarioLogin, caminhoLogin);
    return;
    break;
  case 6:
    exit(1);
  default:
    printf("Opção inválida, por favor, escolha um item do menu\n\n");
    iniciarTarefas(1, usuarioLogin, caminhoLogin);
    break;
  }
}

int cadastrarTarefa(Tarefa tarefa, char caminho[])
{
  tarefa.status = 0;
  FILE *caminhoTarefas = fopen(caminho, "a");
  FILE *ultimaTarefaId = fopen(caminho, "r");
  tarefa.id = obtemUltimoIdTarefas(ultimaTarefaId);
  fprintf(caminhoTarefas, "%c - %s %d\n", tarefa.id, tarefa.descricao, tarefa.status);
  fclose(caminhoTarefas);
  printf("Tarefa cadastrada com sucesso!\n\n");
  return 1;
}

void consultarTarefas(char caminho[])
{
  char linha[150];
  char ultimoId;
  int controle = 0, ultimoIndice = 0;
  FILE *caminhoConsultarTarefa = fopen(caminho, "r");

  while (fgets(linha, 150, caminhoConsultarTarefa) != NULL)
  {
    ultimoIndice = obtemUltimoIndiceString(linha);
    if (linha[ultimoIndice] == '0')
      printf("%.*s ( )\n", ultimoIndice - 1, linha);
    if (linha[ultimoIndice] == '1')
      printf("%.*s (X)\n", ultimoIndice - 1, linha);
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
  // Lê a quantidade de caracteres da string
  int n = strlen(string);
  // Remove o \n da string
  if ((n > 0) && (string[n - 1] == '\n'))
    string[n - 1] = '\0';
}

int obtemUltimoIndiceString(char *string)
{
  int n = strlen(string);

  if (string[n - 1] == '\n')
    n -= 2;
  else
    n -= 1;

  return n;
}

char obtemUltimoIdTarefas(FILE *arquivo)
{
  char linha[150];
  char ultimoId;
  int controle = 0;

  while (fgets(linha, 150, arquivo) != NULL)
  {
    ultimoId = linha[0];
    controle = 1;
  }

  if (!controle)
    return '1';

  return ultimoId + 1;
}

char *obtemCaminho(char *username)
{
  char *caminhoTarefa = (char *)malloc(65 * sizeof(char));
  strcpy(caminhoTarefa, "arqUsuario/");
  strcat(caminhoTarefa, username);
  strcat(caminhoTarefa, ".txt");
  return caminhoTarefa;
}