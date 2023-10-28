#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

char caminhoAutenticar[25] = "cadastro\\logins.txt";

void inicio(int opcao) {
    
    Usuario usuario;

    switch (opcao)
    {
        case 0:
            printf("Ola! Seja bem-vindo(a) ao sistema de tarefas\n");
            printf("Por favor, autentique-se:\n");
            printf("1 - Cadastro\n");
            printf("2 - Login\n");
            printf("Digite sua opcao: ");
            scanf("%d", &opcao);
            setbuf(stdin, NULL);
            inicio(opcao);
            break;
        case 1:
            printf("\n** CADASTRO DE USUARIO **\n\n");
            do
            {
                printf("Digite o seu username: ");
                fgets(usuario.username, 50, stdin);
                setbuf(stdin, NULL);
            } while (usuarioEstaCadastrado(usuario));
            printf("Digite sua senha: ");
            fgets(usuario.senha, 50, stdin);
            removeCaracterString(usuario.username);
            if (cadastrarUsuario(usuario))
            {
                inicio(0);
                return;
            }
            break;
        case 2:
            printf("\n** LOGIN DE USUARIO **\n\n");
            do
            {
                printf("Digite o seu username: ");
                fgets(usuario.username, 50, stdin);
                removeCaracterString(usuario.username);
                printf("Digite sua senha: ");
                fgets(usuario.senha, 50, stdin);
                setbuf(stdin, NULL);
            } while (!loginUsuario(usuario));
            break;
        default:
            printf("Opcao invalida!\n");
            inicio(0);
            return;
            break;
    }
}

int cadastrarUsuario(Usuario usuario) {

    FILE *cadastro = fopen(caminhoAutenticar, "a");

    if (caminhoAutenticar == NULL)
    {
        cadastro = fopen(caminhoAutenticar, "w");
        fprintf(cadastro, "%s", "Usuario Senha");
        fclose(cadastro);
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

    char caminhoTarefa[65];
    strcpy(caminhoTarefa, "tarefas\\");
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
                printf("Login realizado com sucesso!\n\n");
            }
            else
            {
                printf("Login realizado com sucesso!\n\n");
                printf("Bem-vindo(a), %s", usuario.username);
            }   
            
            return 1;   
        }
        else
        {
            printf("Nao foi possivel realizar o login\n\n");
            printf("Verifique suas informacoes e tente novamente\n\n");
            return 0;
        }
        
    }

}

int usuarioEstaCadastrado(Usuario usuario) {

    FILE *usuarios = fopen(caminhoAutenticar, "r");

    char linha[50];
    
    while(fgets(linha, 50, usuarios) != NULL)
    {
        if (strcmp(linha, usuario.username) == 1)
        {
            fclose(usuarios);
            printf("Ja existe um usuario com esse username cadastrado!\n\n");
            return 1;
        }
    }

    fclose(usuarios);

    return 0;
}

void tarefas(int opcao)
{

}

void removeCaracterString(char *string)
{
    //Lê a quantidade de caracteres da string
    int n = strlen(string);
    //Remove o \n da string
    if ((n > 0) && (string[n-1] == '\n'))
        string[n-1] = '\0';
}