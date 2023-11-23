#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tarefas.h"
#include "autenticar.h"

void iniciarTarefas(int opcao, char usuarioLogin[], char caminhoLogin[]) 
{
  //usuarioLogin -> usuário está vindo da função de inicio() na main.c
  Tarefa tarefa;
  strcpy(caminhoLogin, usuarioLogin); 

  switch (opcao)
  {
    //O programa inicia nessa opção
    case 0:
      system("clear");
      printf("\nSuas tarefas:\n");
      consultarTarefas(obtemCaminho(caminhoLogin));
      printf("\n");
      iniciarTarefas(1, usuarioLogin, caminhoLogin); // recursão: recomeça para essa função com a nova escolha do usuario
      return; //Usa o return para quebrar a função e não ficar em loop
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
      iniciarTarefas(opcao + 1, usuarioLogin, caminhoLogin); //Soma mais 1 pois o switch case começa em 0
      return; //Condição de parada da recirsovodade 
  case 2:
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║            CONSULTA DE TAREFAS         ║\n");
    printf("╚════════════════════════════════════════╝\n");
    consultarTarefas(obtemCaminho(caminhoLogin));
    printf("\n");
    iniciarTarefas(1, usuarioLogin, caminhoLogin); //Recursão: retorna para o menu principal
    return; //Condição de parada da recirsovodade 
  case 3:
    printf("╔════════════════════════════════════════╗\n");
    printf("║            CADASTRO DE TAREFA          ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\nInforme a descricao da tarefa: ");
    fgets(tarefa.descricao, 150, stdin);
    retiraCaracterString(tarefa.descricao);
    cadastrarTarefa(tarefa, obtemCaminho(caminhoLogin)); //cadastrarTarefa pede o struct Tarefa e passa o caminho (Ex: "arqUsuario/Ennzo.txt")
    iniciarTarefas(1, usuarioLogin, caminhoLogin); // recursão: retorna para o menu principal
    return; // Condição de parada da recursividade
  case 4:
    printf("╔════════════════════════════════════════╗\n");
    printf("║            ATUALIZAR TAREFAS           ║\n");
    printf("╚════════════════════════════════════════╝\n");
    consultarTarefas(obtemCaminho(caminhoLogin));

    if (alterarTarefa(obtemCaminho(caminhoLogin)))
    {
      printf("Tarefa atualizada com sucesso!!!\n");
      iniciarTarefas(2, usuarioLogin, caminhoLogin); // se deu tudo certo, consulta novamente as tarefas para mostrar a tarefa marcada como feita
    }
    else
    {
      printf("Nenhuma tarefa alterada\n");
      iniciarTarefas(1, usuarioLogin, caminhoLogin); // se ocorreu algum erro, retorna ao menu.
    }
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
  tarefa.status = 0; //A tarefa por padrão vai ter o status como pendente (0)
  FILE *caminhoTarefas = fopen(caminho, "a");
  FILE *ultimaTarefaId = fopen(caminho, "r"); //Abre esse arquivo para obter o ultimo ID
  tarefa.id = obtemUltimoIdTarefas(ultimaTarefaId);
  fprintf(caminhoTarefas, "%c - %s %d\n", tarefa.id, tarefa.descricao, tarefa.status); //Cadastrando uma nova tarefa no arquivo
  fclose(caminhoTarefas);
  printf("Tarefa cadastrada com sucesso!\n\n");
  return 1;
}

void consultarTarefas(char caminho[])
{
  //caminho[] -> Caminho passado pela função obtemCaminho
  char tarefaAlterar[150];
  int controle = 0, ultimoIndice = 0;
  FILE *caminhoConsultarTarefa = fopen(caminho, "r"); //Abre o arquivo de tarefas do usuário para leitura

  while (fgets(tarefaAlterar, 150, caminhoConsultarTarefa) != NULL) //Lê linha por linha do arquivo
  {
    ultimoIndice = obtemUltimoIndiceString(tarefaAlterar); //Obtém o status da tarefa
    if (tarefaAlterar[ultimoIndice] == '0')
      printf("%.*s ( )\n", ultimoIndice - 1, tarefaAlterar); //Pede para printar exatamente na posição do numero de status da tarefa no arquivo
    if (tarefaAlterar[ultimoIndice] == '1')
      printf("%.*s (X)\n", ultimoIndice - 1, tarefaAlterar); //Pede para printar exatamente na posição do numero de status da tarefa no arquivo
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
    n -= 2; // Decrementa 2 para obter o ultimo caracter útil (retira da contagem o '\0' e '\n'), o status da tarefa está nessa posição
  else
    n -= 1; // Decrementa 1 para obter o ultimo caracter útil (retira da contagem o '\0'), o status da tarefa está nessa posição

  return n; // Posição do status da tarefa -> Retorna a última posição últil
}

char obtemUltimoIdTarefas(FILE *arquivo)
{
  char tarefaAlterar[150];
  char ultimoId;
  int controle = 0;

  while (fgets(tarefaAlterar, 150, arquivo) != NULL) //Lê linha por linha do arquivo
  {
    ultimoId = tarefaAlterar[0]; //Obtém o ID da tarefa que sempre estará na primeira posição (0)
    controle = 1; //Variável de controle
  }

  if (!controle)
    return '1'; //Retorna '1' caso não foi encontrado nenhum identificador para dar início a sequência

  return ultimoId + 1; //Retorna o ID encontrado e soma mais 1 para dar continuidade a sequência
}

char *obtemCaminho(char *username)
{
  char *caminhoTarefa = (char *)malloc(65 * sizeof(char)); // Aloca dinamicamente o tamanho da string de caminho de arquivo
  strcpy(caminhoTarefa, "arqUsuario/"); //Copia a string "arqUsuario/" para a string caminhoTarefa
  strcat(caminhoTarefa, username); //Concatena o usuário com a string anterior -> Ex: "arqUsuario/Enzo"
  strcat(caminhoTarefa, ".txt"); //Concatena o ".txt" com a string anterior -> Ex: "arqUsuario/Enzo.txt"
  return caminhoTarefa; //Retorna o caminho para encontrar o arquivo de tarefa daquele usuário
}

int alterarTarefa(char caminho[])
{
  // retorna 0 se houver algum erro no caminho e 1 se a tarefa for alterada com sucesso.
  char tarefaAlterar[150];
  char idBusca;
  int idEncontrado = 0, opcao = 0, linhaAlvo = 0;
  FILE *arquivoTarefas = fopen(caminho, "r");
  FILE *arquivoTemporario;

  if (arquivoTarefas == NULL) // Verifica se o arquivo foi aberto corretamente
  {
    printf("Houve um problema para abrir o arquivo de tarefas. Tente novamente ou reinicie o programa. \n");
    return 0;
  }

  printf("\n\nDigite o numero da tarefa que deseja alterar:\n");

  scanf("%c", &idBusca);

  while (fgets(tarefaAlterar, 150, arquivoTarefas) != NULL) // Percorre linha por linha do arquivo
  {
    if (tarefaAlterar[0] == idBusca) // tarefaAlterar[0] -> Corresponde ao ID que sempre estará nessa posição
    {
      idEncontrado = 1;
      break;
    }
    linhaAlvo++; // Incrementa para salvar o número da linha que está o ID
  }
  if (!idEncontrado)
  {
    printf("Não entramos a tarefa. Tente novamente. \n");
    fclose(arquivoTarefas);
    return 0;
  }
  fclose(arquivoTarefas);

  printf("\n\nEssa é a tarefa que você deseja alterar:\n %s\n", tarefaAlterar);

  printf("\n\nO que você deseja fazer?\n\n");
  printf("(1) - Marcar como feita\n");
  printf("(2) - Alterar descrição\n");
  printf("(3) - Voltar\n");

  printf("\nDigite sua opção: ");

  scanf("%d", &opcao);

  getchar(); // para remover o \n do buffer

  // ---- bloco de variáveis que vou usar no switch
  int n = obtemUltimoIndiceString(tarefaAlterar);
  int numLinha = 0;
  char linhaTemp[150];
  Tarefa tarefaCorrigida;
  char tarefaAlterada[150];

  switch (opcao)
  {
  case 1:
    if (tarefaAlterar[n] == '0') // n -> posição da string que contém o status
    {
      tarefaAlterar[n] = '1';
      arquivoTarefas = fopen(caminho, "r");
      arquivoTemporario = fopen("arqUsuario/temp.txt", "w"); // Cria um arquivo temporário que receberá as tarefas existentes

      if (arquivoTemporario == NULL || arquivoTarefas == NULL)
      {
        printf("Erro ao marcar tarefa como feita.\n");
        return 0;
      }

      while (fgets(linhaTemp, 150, arquivoTarefas) != NULL) // Lendo linha por linha do arquivo já existe do usuário e salvando no arquivo temporário
      {
        if (numLinha == linhaAlvo)                         // Se estiver na linha alvo (linha da tarefa que será alterada)
          fprintf(arquivoTemporario, "%s", tarefaAlterar); // Arquivo temporário grava nessa linha a tarefa com o novo status
        else
          fprintf(arquivoTemporario, "%s", linhaTemp); // Arquivo temporário faz uma cópia da linha que está lendo no arquivo original

        numLinha++; // Incrementa o número da linha
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
      return 1;
    }
    else
    { // Se o status da tarefa não for 0, a tarefa está feita
      printf("Tarefa já está marcada como feita!\n");
      return 1;
    }
  case 2:
    printf("Digite a nova descrição da tarefa:\n");
    fgets(tarefaCorrigida.descricao, 150, stdin);
    removeCaracterString(tarefaCorrigida.descricao);

    tarefaCorrigida.id = tarefaAlterar[0]; // copia o id da tarefa selecionada
    tarefaCorrigida.status = 0;

    arquivoTarefas = fopen(caminho, "r");
    arquivoTemporario = fopen("arqUsuario/temp.txt", "w"); // Cria um arquivo temporário que receberá as tarefas existentes

    if (arquivoTemporario == NULL || arquivoTarefas == NULL)
    {
      printf("Erro ao alterar descrição da tarefa.\n");
      return 0;
    }

    while (fgets(linhaTemp, 150, arquivoTarefas) != NULL) // Lendo linha por linha do arquivo já existe do usuário e salvando no arquivo temporário
    {
      if (numLinha == linhaAlvo) // Se estiver na linha alvo (linha da tarefa que será alterada)
        fprintf(arquivoTemporario, "%c - %s %d\n", tarefaCorrigida.id, tarefaCorrigida.descricao, tarefaCorrigida.status);
      else
        fprintf(arquivoTemporario, "%s", linhaTemp); // Arquivo temporário faz uma cópia da linha que está lendo no arquivo original

      numLinha++; // Incrementa o número da linha
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
    return 1; // se chegou até aqui sem falhar, retorna sucesso
  case 3: 
    system("clear");
    return 0;
  default:
    system("clear");
    printf("Opcao invalida. Tente outra vez.");
    return 0;
  }
}