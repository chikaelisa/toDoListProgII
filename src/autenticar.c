#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autenticar.h"

char caminhoAutenticar[25] = "arqCadastro/logins.txt"; // arquivo que guarda todos os logins
char *username;

void inicio(int opcao, char *usuarioLogin) {
    
    Usuario usuario;
    username = usuarioLogin;

    switch (opcao)
    {  // o programa inicia com essa opção
        case 0:
            printf("Por favor, escolha uma opcao:\n");
            printf("(1) - Cadastro\n");
            printf("(2) - Login\n");
            printf("(3) - Sair\n");
            printf("Digite sua opcao: ");
            scanf("%d", &opcao); 
            setbuf(stdin, NULL);
            printf("\n");
            // recursão: recomeça para essa função com a nova escolha do usuario
            inicio(opcao, username);
            break;
        case 1:
            system("clear"); // limpa o console para deixar mais viável a leitura das novas informações
            printf("╔════════════════════════════════════════╗\n");
            printf("║            CADASTRO DE USUARIO         ║\n");
            printf("╚════════════════════════════════════════╝\n");
            do
            {
                printf("Digite o seu username: ");
                fgets(usuario.username, 50, stdin);
                setbuf(stdin, NULL); // limpa o buffer para não correr o risco de salvar nenhum caracter errado
                removeCaracterString(usuario.username); //remove o \n para poder salvar tudo em uma linha só do arquivo depois
            } while (usuarioEstaCadastrado(usuario)); // fica pedindo um username enquanto não houver um igual no arquivo
            printf("Digite sua senha: ");
            fgets(usuario.senha, 50, stdin);
            removeCaracterString(usuario.senha);
            if (cadastrarUsuario(usuario)) // se ocorreu tudo bem com o cadastro de novo usuário, 
            {
                inicio(0, username); // retorna para essa função com o primeiro menu, pra que a pessoa possa escolher fazer o login
                return;
            }
            break;
        case 2:
            system("clear");
            printf("╔════════════════════════════════════════╗\n");
            printf("║             LOGIN DE USUARIO           ║\n");
            printf("╚════════════════════════════════════════╝\n");
            do
            {
                printf("Digite o seu username: ");
                fgets(usuario.username, 50, stdin);
                removeCaracterString(usuario.username);
                printf("Digite sua senha: ");
                fgets(usuario.senha, 50, stdin);
                setbuf(stdin, NULL);
                // pede usuário e senha enquanto não encontrar um usuário correspondente
            } while (!loginUsuario(usuario)); 
            strcpy(username, usuario.username); // copia o username digitado pelo usuario para a variavel username
            // essa informação será utilizada para criar os arquivos
            return;
            break;
        case 3:
            exit(1); // finaliza o sistema
            break;
        default:
            system("clear");
            printf("Opcao invalida!\n");
            // qualquer caracter diferente retornará para o menu inicial
            inicio(0, username);
            return;
            break;
    }
}

int cadastrarUsuario(Usuario usuario) {

    FILE *cadastro = fopen(caminhoAutenticar, "a");

    if (cadastro == NULL)
    {
        cadastro = fopen(caminhoAutenticar, "w");
        // abre o arquivo em modo de escrita para o caso de ele ainda não existir criar um novo
        cadastro = fopen(caminhoAutenticar, "a");
        // abre o arquivo no modo append para adicionar uma linha ao final do arquivo
        fprintf(cadastro, "%s %s\n", usuario.username, usuario.senha);
        // salva as informações de usuário no arquivo
    }
    else
        // se o arquivo já existir, apenas escreve as informações
        fprintf(cadastro, "%s %s\n", usuario.username, usuario.senha);
    
    fclose(cadastro);

    printf("Cadastro realizado com sucesso!\n\n");

    return 1;
}

int loginUsuario(Usuario usuario)
{
    FILE *usuarios = fopen(caminhoAutenticar, "r");

    if (usuarios == NULL)
    {
        printf("Nao foi possivel encontrar o arquivo de cadastro\n\n");
        inicio(0, username); // caso não encontre o arquivo de login, retorna ao menu principal
        return 2;
    }
    else
    {   // ---------
        char caminhoTarefa[65] = "arqUsuario/";
        strcat(caminhoTarefa, usuario.username);
        strcat(caminhoTarefa, ".txt");
        // ---- esse bloco concatena em uma variável o nome do arquivo com o o caminho da pasta que será salvo
       // isso porque quando uma tarefa for criada ela será salva em um arquivo com o nome do usuario

        char credencial[100];
        strcpy(credencial, usuario.username);
        strcat(credencial, " ");
        strcat(credencial, usuario.senha);
        // --- criamos uma variável com toda a linha que iremos buscar no arquivo

        char linha[100];

        while(fgets(linha, 100, usuarios) != NULL) // enquanto a linha do arquivo não for nula
        {
            if (strcmp(linha, credencial) == 0)  // se essa linha corresponder ao usuaario e senha digitados
            {
                FILE *arquivosUsuario = fopen(caminhoTarefa, "a");

                if (arquivosUsuario == NULL)
                {
                    fprintf(arquivosUsuario, "w");
                    system("clear");
                    printf("Login realizado com sucesso!\n\n");
                    printf("Bem-vindo(a), %s.\n", usuario.username);
                }
                else
                {
                    system("clear");
                    printf("Login realizado com sucesso!\n\n");
                    printf("Bem-vindo(a), %s.\n", usuario.username);
                }         
            
                fclose(arquivosUsuario);

                return 1;   
            }
        }

        printf("Nao foi possivel realizar o login\n\n");
        printf("Verifique suas informacoes e tente novamente\n\n");
        return 0;
    }
}

int usuarioEstaCadastrado(Usuario usuario) {

    FILE *usuarios = fopen(caminhoAutenticar, "r");

    char linha[100];
    // passa por todo o arquivo de login checando se já existe o username 
    while(fgets(linha, 100, usuarios) != NULL)
    {  
        if (strstr(linha, usuario.username) != NULL)
        {
            fclose(usuarios);
            printf("Ja existe um usuario com esse username cadastrado!\n\n");
            return 1;
        }
    }

    fclose(usuarios);

    return 0;
}

void removeCaracterString(char *string)
{
    //Lê a quantidade de caracteres da string
    int n = strlen(string);
    //Remove o \n da string
    if ((n > 0) && (string[n-1] == '\n'))
        string[n-1] = '\0';
}