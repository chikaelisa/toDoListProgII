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
    system("clear");
    printf("\nSuas tarefas:\n");
    consultarTarefas(obtemCaminho(caminhoLogin));
    printf("\n");
    iniciarTarefas(1, usuarioLogin, caminhoLogin);
    return;
  case 1:
    printf("╔════════════════════════════════════════╗\n");
    printf("║                  MENU                  ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("(1) - Listar tarefas\n");
    printf("(2) - Cadastrar tarefa\n");
    printf("(3) - Atualizar tarefa\n");
    printf("(4) - Excluir tarefa\n");
    printf("(5) - Sair\n");
    printf("\nDigite sua opcao: ");
    scanf("%d", &opcao);
    system("clear");
    setbuf(stdin, NULL);
    printf("\n");
    iniciarTarefas(opcao + 1, usuarioLogin, caminhoLogin);
    return;
  case 2:
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║            CONSULTA DE TAREFAS         ║\n");
    printf("╚════════════════════════════════════════╝\n");
    consultarTarefas(obtemCaminho(caminhoLogin));
    printf("\n");
    iniciarTarefas(1, usuarioLogin, caminhoLogin);
    return;
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
  case 4:
    printf("╔════════════════════════════════════════╗\n");
    printf("║            ATUALIZAR TAREFAS           ║\n");
    printf("╚════════════════════════════════════════╝\n");
    consultarTarefas(obtemCaminho(caminhoLogin));
    // alterarTarefa(obtemCaminho(caminhoLogin));
    if (alterarTarefa(obtemCaminho(caminhoLogin))) {
      iniciarTarefas(2, usuarioLogin, caminhoLogin); // se deu tudo certo, consulta novamente as tarefas para mostrar a tarefa marcada como feita
    } else {
      printf("Nao foi possivel alterar a tarefa\n");
      iniciarTarefas(1, usuarioLogin, caminhoLogin); // se ocorreu algum erro, retorna ao menu. 
    };
    return;
  case 5:
    system("clear");
    printf("Você selecionou a opção 4, estamos trabalhando nela! Em breve\n\n");
    iniciarTarefas(1, usuarioLogin, caminhoLogin);
    return;
  case 6:
    system("clear");
    printf("Agradecemos por utilizar o gerenciador de tarefas. Até a próxima!\n\n");
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
  char tarefaAlterar[150];
  int controle = 0, ultimoIndice = 0;
  FILE *caminhoConsultarTarefa = fopen(caminho, "r");

  while (fgets(tarefaAlterar, 150, caminhoConsultarTarefa) != NULL)
  {
    ultimoIndice = obtemUltimoIndiceString(tarefaAlterar);
    if (tarefaAlterar[ultimoIndice] == '0')
      printf("%.*s ( )\n", ultimoIndice - 1, tarefaAlterar);
    if (tarefaAlterar[ultimoIndice] == '1')
      printf("%.*s (X)\n", ultimoIndice - 1, tarefaAlterar);
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
  char tarefaAlterar[150];
  char ultimoId;
  int controle = 0;

  while (fgets(tarefaAlterar, 150, arquivo) != NULL)
  {
    ultimoId = tarefaAlterar[0];
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

int alterarTarefa(char caminho[])
{
  // retorna 0 se houver algum erro no caminho e 1 se a tarefa for alterada com sucesso.
  char tarefaAlterar[150];
  char idBusca;
  int idEncontrado = 0, opcao = 0, linhaAlvo = 0;
  FILE *arquivoTarefas = fopen(caminho, "r");
  FILE *arquivoTemporario;

  if (arquivoTarefas == NULL)
  {
    printf("Houve um problema para abrir o arquivo de tarefas. Tente novamente ou reinicie o programa. \n");
    return 0;
  }

  printf("Digite o numero da tarefa que deseja alterar:\n");

  scanf("%c", &idBusca);

  while (fgets(tarefaAlterar, 150, arquivoTarefas) != NULL)
  {
    if (tarefaAlterar[0] == idBusca)
    {
      idEncontrado = 1;
      break;
    }
    linhaAlvo++;
  }
  if (!idEncontrado)
  {
    printf("Não entramos a tarefa. Tente novamente. \n");
    return 0;
  }
  fclose(arquivoTarefas);

  printf("Essa é a tarefa que você deseja alterar:\n %s\n", tarefaAlterar);

  printf("O que você deseja fazer?\n\n");
  printf("(1) - Marcar como feita\n");
  printf("(2) - Corrigir texto\n");

  printf("\nDigite sua opção: ");

  scanf("%d", &opcao);

  int n = obtemUltimoIndiceString(tarefaAlterar);
  int numLinha = 0;
  char linhaTemp[100];

  switch (opcao)
  {
  case 1:
    if (tarefaAlterar[n] == '0')
    {
      tarefaAlterar[n] = '1';
      arquivoTarefas = fopen(caminho, "r");
      arquivoTemporario = fopen("arqUsuario/temp.txt", "w");

      if (arquivoTemporario == NULL || arquivoTarefas == NULL)
      {
        printf("Erro ao marcar tarefa como feita.\n");
        return 0;
      }

      while (fgets(linhaTemp, 150, arquivoTarefas) != NULL)
      {
        if (numLinha == linhaAlvo)
          fprintf(arquivoTemporario, "%s", tarefaAlterar);
        else
          fprintf(arquivoTemporario, "%s", linhaTemp);

        numLinha++;
      }

      fclose(arquivoTarefas);
      fclose(arquivoTemporario);

      if (remove(caminho) != 0) // apago o arquivo original
      {
        printf("Erro ao apagar arquivo\n");
        return 0;
      }

      if (rename("arqUsuario/temp.txt", caminho) != 0) // renomeio o arquivo temporário para tomar o lugar do anterior
      {
        printf("Erro ao renomear arquivo\n");
        return 0;
      }
    } else {
      printf("Tarefa já está marcada como feita!\n");
      return 1;
    }

  case 2: 
    printf("\n\n !!! Em breve disponibilizaaremos essa opção !!!\n\n");

    Tarefa tarefaCorrigida;
    printf("Digite a nova descrição da tarefa:\n");
    scanf("%s", tarefaCorrigida.descricao);

    tarefaCorrigida.id = tarefaAlterar[0];



    return 0;

  default:
    system("clear");
    printf("Opcao invalida. Tente outra vez.");
    return 0;
  }

  fclose(arquivoTarefas);

  return 1;
}