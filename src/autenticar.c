#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autenticar.h"

char caminhoAutenticar[25] = "arqCadastro/logins.txt";
char *username;

void inicio(int opcao, char *usuarioLogin) {
    
    Usuario usuario;
    username = usuarioLogin;

    switch (opcao)
    {
        case 0:
            printf("Por favor, escolha uma opcao:\n");
            printf("(1) - Cadastro\n");
            printf("(2) - Login\n");
            printf("(3) - Sair\n");
            printf("Digite sua opcao: ");
            scanf("%d", &opcao);
            setbuf(stdin, NULL);
            printf("\n");
            inicio(opcao, username);
            break;
        case 1:
            printf("╔════════════════════════════════════════╗\n");
            printf("║            CADASTRO DE USUARIO         ║\n");
            printf("╚════════════════════════════════════════╝\n");
            do
            {
                printf("Digite o seu username: ");
                fgets(usuario.username, 50, stdin);
                setbuf(stdin, NULL);
                removeCaracterString(usuario.username);
            } while (usuarioEstaCadastrado(usuario));
            printf("Digite sua senha: ");
            fgets(usuario.senha, 50, stdin);
            removeCaracterString(usuario.senha);
            if (cadastrarUsuario(usuario))
            {
                inicio(0, username);
                return;
            }
            break;
        case 2:
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
            } while (!loginUsuario(usuario));
            strcpy(username, usuario.username); 
            return;
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("Opcao invalida!\n");
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

        cadastro = fopen(caminhoAutenticar, "a");
        fprintf(cadastro, "%s %s\n", usuario.username, usuario.senha);
    }
    else
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
        inicio(0, username);
        return 2;
    }
    else
    {
        char caminhoTarefa[65] = "arqUsuario/";
        strcat(caminhoTarefa, usuario.username);
        strcat(caminhoTarefa, ".txt");
        
        char credencial[100];
        strcpy(credencial, usuario.username);
        strcat(credencial, " ");
        strcat(credencial, usuario.senha);

        char linha[100];

        while(fgets(linha, 100, usuarios) != NULL)
        {
            if (strcmp(linha, credencial) == 0)
            {
                FILE *arquivosUsuario = fopen(caminhoTarefa, "a");

                if (arquivosUsuario == NULL)
                {
                    fprintf(arquivosUsuario, "w");
                    system("clear");
                    printf("Login realizado com sucesso!\n\n");
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