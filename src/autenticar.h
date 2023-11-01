#ifndef autenticar // Evitar inclusões múltiplas acidentais
#define autenticar

struct Usuario
{
    char username[50];
    char senha[50];
};
typedef struct Usuario Usuario;

// Protótipo de função
void inicio(int opcao);
int cadastrarUsuario(Usuario usuario);
int loginUsuario(Usuario usuario);
int usuarioEstaCadastrado(Usuario usuario);
void removeCaracterString(char *string);

#endif //autenticar