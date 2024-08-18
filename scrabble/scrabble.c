#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Pontuações atribuídas a cada letra do alfabeto
int PONTOS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int calcular_pontuacao(const char *palavra);

int main(void)
{
    char palavra1[100];
    char palavra2[100];

    // Obter palavras de ambos os jogadores
    printf("Jogador 1: ");
    fgets(palavra1, sizeof(palavra1), stdin);
    // Remover o caractere de nova linha, se presente
    palavra1[strcspn(palavra1, "\n")] = '\0';

    printf("Jogador 2: ");
    fgets(palavra2, sizeof(palavra2), stdin);
    // Remover o caractere de nova linha, se presente
    palavra2[strcspn(palavra2, "\n")] = '\0';

    // Calcular pontuações para ambas as palavras
    int pontuacao1 = calcular_pontuacao(palavra1);
    int pontuacao2 = calcular_pontuacao(palavra2);

    // Determinar o vencedor
    if (pontuacao1 > pontuacao2)
    {
        printf("Jogador 1 vence!\n");
    }
    else if (pontuacao2 > pontuacao1)
    {
        printf("Jogador 2 vence!\n");
    }
    else
    {
        printf("Empate!\n");
    }

    return 0;
}

int calcular_pontuacao(const char *palavra)
{
    int pontuacao = 0;

    // Iterar por cada caractere na palavra
    for (int i = 0, n = strlen(palavra); i < n; i++)
    {
        // Verificar se o caractere é uma letra
        if (isalpha(palavra[i]))
        {
            // Converter o caractere para maiúsculo e calcular a pontuação
            int indice = toupper(palavra[i]) - 'A';
            pontuacao += PONTOS[indice];
        }
    }

    return pontuacao;
}
