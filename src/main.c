#include <stdio.h>
#include <string.h>
#include "autenticar.h"
#include "tarefas.h"

int main() {

    char usuarioLogin[50];
    char caminhoLogin[65];

    printf("Ola! Seja bem-vindo(a) ao sistema de tarefas\n");
    inicio(0, usuarioLogin); //Inicia o programa e obtém o usuário logado
    iniciarTarefas(0, usuarioLogin, caminhoLogin); //Após o login, inicia as funcionalidades

    return 0;

}