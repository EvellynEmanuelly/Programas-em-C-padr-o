#include <stdio.h>

int main(void)
{
    char continuar;
    do
    {
        // Solicitar o tamanho inicial ao usuário
        int tamanho_inicial;
        do
        {
            printf("Tamanho inicial (deve ser pelo menos 9): ");
            scanf("%d", &tamanho_inicial);
        } while (tamanho_inicial < 9);

        // Solicitar o tamanho final ao usuário
        int tamanho_final;
        do
        {
            printf("Tamanho final (deve ser pelo menos igual ao tamanho inicial): ");
            scanf("%d", &tamanho_final);
        } while (tamanho_final < tamanho_inicial);

        // Calcular o número de anos até atingir o limite
        int anos = 0;
        while (tamanho_inicial < tamanho_final)
        {
            tamanho_inicial = tamanho_inicial + (tamanho_inicial / 3) - (tamanho_inicial / 4);
            anos++;
        }

        // Imprimir o número de anos
        printf("Years: %d\n", anos);

        // Solicitar se o usuário deseja continuar
        printf("Deseja continuar? (s para continuar, n para encerrar): ");
        scanf(" %c", &continuar); // Note o espaço antes de %c para consumir a quebra de linha anterior

    } while (continuar == 's' || continuar == 'S');

    return 0;
}
