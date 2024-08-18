#include <stdio.h>

int main()
{
    char nome[100];
    char jogarNovamente;

    // Solicitar o nome do usuário
    printf("Digite o seu nome: ");
    scanf("%99s", nome); // Limitar a entrada para evitar overflow
    printf("Ola, %s! Bem-vindo ao jogo!\n", nome);

    do
    {
        int altura;

        // Solicitar altura até que seja fornecido um valor válido
        do
        {
            printf("Digite a altura da piramide (entre 1 e 8): ");
            scanf("%d", &altura);

            if (altura < 1 || altura > 8)
            {
                printf("Por favor, insira um numero entre 1 e 8.\n");
            }
        }
        while (altura < 1 || altura > 8);

        // Imprimir as pirâmides
        for (int i = 0; i < altura; i++)
        {
            // Imprimir espaços à esquerda na pirâmide da esquerda
            for (int j = 0; j < altura - i - 1; j++)
            {
                printf(" ");
            }

            // Imprimir '#' na pirâmide da esquerda
            for (int j = 0; j <= i; j++)
            {
                printf("#");
            }

            // Imprimir espaços entre as pirâmides
            printf("  ");

            // Imprimir '#' na pirâmide da direita
            for (int j = 0; j <= i; j++)
            {
                printf("#");
            }

            // Mover para a próxima linha
            printf("\n");
        }

        // Perguntar ao usuário se deseja jogar novamente
        printf("\nDeseja jogar novamente, %s? (s para sim, n para nao): ", nome);
        scanf(" %c", &jogarNovamente);

        if (jogarNovamente != 's' && jogarNovamente != 'S')
        {
            printf("Que pena, nos vemos na proxima, %s!\n", nome);
        }
    }
    while (jogarNovamente == 's' || jogarNovamente == 'S');

    return 0;
}
