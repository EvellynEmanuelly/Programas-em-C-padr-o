#include <stdio.h>

int main(void) {
    char nome[100]; // Cria um array para armazenar o nome do usuário

    // Solicita o nome do usuário
    printf("Qual e seu nome? \n");
    // Lê o nome do usuário, limitando a leitura a 99 caracteres para evitar overflow
    scanf("%99s", nome);

    // Exibe uma mensagem de saudação
    printf("Hello, %s \n", nome);

    return 0;
}
