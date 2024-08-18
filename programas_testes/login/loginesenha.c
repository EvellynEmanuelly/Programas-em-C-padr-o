#include <stdio.h>
#include <string.h>

// Função para verificar o login e senha
int verificarLogin(const char *usuario, const char *senha) {
    // Substitua 'Evellyn' e '2005' pelos valores desejados
    return (strcmp(usuario, "Evellyn") == 0 && strcmp(senha, "2005") == 0);
}

int main() {
    char usuario[50];
    char senha[50];

    // Solicitar nome de usuário e senha
    printf("Digite o nome de usuario: ");
    scanf("%49s", usuario); // Limitar a entrada para evitar overflow
    printf("Digite a senha: ");
    scanf("%49s", senha); // Limitar a entrada para evitar overflow

    // Verificar login e senha
    if (verificarLogin(usuario, senha)) {
        printf("Login bem-sucedido! Seja bem-vindo(a)!\n");
    } else {
        printf("Login falhou. Verifique seu nome de usuario/senha e tente novamente.\n");
    }

    return 0;
}
