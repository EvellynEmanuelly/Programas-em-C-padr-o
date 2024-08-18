#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    float troco;

    // Solicita ao usuário o valor do troco até que seja fornecido um valor válido
    while (1)
    {
        printf("Troco devido (em reais): ");

        if (scanf("%f", &troco) != 1)
        {
            // Se a entrada não for numérica, limpa o buffer de entrada
            while (getchar() != '\n')
                ;
            printf("Por favor, insira um valor numérico válido.\n");
        }
        else if (troco < 0)
        {
            // Se a entrada for negativa, solicita novamente
            printf("Por favor, insira um valor não negativo.\n");
        }
        else
        {
            // Se a entrada for válida, sai do loop
            break;
        }
    }

    // Converte os reais em centavos e arredonda para o centavo mais próximo
    int centavos = round(troco * 100);

    // Inicializa variáveis para contar o número mínimo de moedas
    int moedas = 0;

    // Conta as moedas de 50 centavos
    moedas += centavos / 50;
    centavos %= 50;

    // Conta as moedas de 25 centavos
    moedas += centavos / 25;
    centavos %= 25;

    // Conta as moedas de 10 centavos
    moedas += centavos / 10;
    centavos %= 10;

    // Conta as moedas de 5 centavos
    moedas += centavos / 5;
    centavos %= 5;

    // Conta as moedas de 1 centavo
    moedas += centavos;

    // Imprime o número mínimo de moedas necessárias
    printf("Número mínimo de moedas: %d\n", moedas);

    return 0;
}
