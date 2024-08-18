#include <stdio.h>

int main()
{
    char nome[100];

    // Solicitar o nome do usuário
    printf("Digite o seu nome: ");
    scanf("%99s", nome); // Limitar a entrada para evitar overflow
    printf("Ola, %s! Bem-vindo ao jogo!\n", nome);

    int height;

    // Solicitar e validar o tamanho
    do
    {
        printf("Tamanho: ");
        scanf("%d", &height);

        if (height < 1 || height > 8)
        {
            printf("Por favor, tente novamente e insira um numero entre 1 e 8!\n");
        }
    }
    while (height < 1 || height > 8);

    // Imprimir o padrão de "#" com base no tamanho
    for (int i = 1; i <= height; i++)
    {
        // Imprimir espaços em branco à esquerda
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }

        // Imprimir os "#"
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }

        // Quebrar a linha após imprimir os "#"
        printf("\n");
    }

    return 0;
}
