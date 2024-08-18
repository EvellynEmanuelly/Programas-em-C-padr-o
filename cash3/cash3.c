#include <stdio.h>
#include <math.h>

int main(void)
{
    char resposta;

    do
    {
        float valorCompra, valorPago;

        // Solicita ao usuário o valor da compra e o valor pago
        do
        {
            printf("Valor da compra: ");
            scanf("%f", &valorCompra);

            if (valorCompra < 0)
            {
                printf("Por favor, insira um valor não negativo.\n");
            }
        } while (valorCompra < 0);

        do
        {
            printf("Valor pago: ");
            scanf("%f", &valorPago);

            if (valorPago < valorCompra)
            {
                printf("O valor pago deve ser maior ou igual ao valor da compra.\n");
            }
        } while (valorPago < valorCompra);

        // Calcula o troco
        float trocoFloat = valorPago - valorCompra;
        int trocoCentavos = round(trocoFloat * 100);

        // Inicializa variáveis para contar o número de notas e moedas
        int notas100 = 0, notas50 = 0, notas20 = 0, notas10 = 0, notas5 = 0, notas2 = 0;
        int moedas1 = 0, moedas50 = 0, moedas25 = 0, moedas10 = 0, moedas5 = 0, moedas01 = 0;

        // Calcula as notas de 100
        notas100 = trocoCentavos / 10000;
        trocoCentavos %= 10000;

        // Calcula as notas de 50
        notas50 = trocoCentavos / 5000;
        trocoCentavos %= 5000;

        // Calcula as notas de 20
        notas20 = trocoCentavos / 2000;
        trocoCentavos %= 2000;

        // Calcula as notas de 10
        notas10 = trocoCentavos / 1000;
        trocoCentavos %= 1000;

        // Calcula as notas de 5
        notas5 = trocoCentavos / 500;
        trocoCentavos %= 500;

        // Calcula as notas de 2
        notas2 = trocoCentavos / 200;
        trocoCentavos %= 200;

        // Calcula as moedas de 1
        moedas1 = trocoCentavos / 100;
        trocoCentavos %= 100;

        // Calcula as moedas de 0.50
        moedas50 = trocoCentavos / 50;
        trocoCentavos %= 50;

        // Calcula as moedas de 0.25
        moedas25 = trocoCentavos / 25;
        trocoCentavos %= 25;

        // Calcula as moedas de 0.10
        moedas10 = trocoCentavos / 10;
        trocoCentavos %= 10;

        // Calcula as moedas de 0.05
        moedas5 = trocoCentavos / 5;
        trocoCentavos %= 5;

        // Calcula as moedas de 0.01
        moedas01 = trocoCentavos;

        // Imprime a quantidade de notas e moedas como troco
        printf("Troco:\n");
        printf("Notas de R$100: %d\n", notas100);
        printf("Notas de R$50: %d\n", notas50);
        printf("Notas de R$20: %d\n", notas20);
        printf("Notas de R$10: %d\n", notas10);
        printf("Notas de R$5: %d\n", notas5);
        printf("Notas de R$2: %d\n", notas2);
        printf("Moedas de R$1: %d\n", moedas1);
        printf("Moedas de R$0.50: %d\n", moedas50);
        printf("Moedas de R$0.25: %d\n", moedas25);
        printf("Moedas de R$0.10: %d\n", moedas10);
        printf("Moedas de R$0.05: %d\n", moedas5);
        printf("Moedas de R$0.01: %d\n", moedas01);

        // Imprime a quantidade total que sairá do caixa
        int totalMoedasNotas = notas100 + notas50 + notas20 + notas10 + notas5 + notas2 + moedas1 + moedas50 + moedas25 + moedas10 + moedas5 + moedas01;
        printf("Total que saira do caixa: %d\n", totalMoedasNotas);

        // Pergunta ao usuário se deseja realizar outra transação
        printf("Deseja realizar outra transacao? (s/n): ");
        scanf(" %c", &resposta);

    } while (resposta == 's' || resposta == 'S');

    return 0;
}
