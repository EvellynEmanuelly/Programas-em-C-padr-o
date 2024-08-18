#include <stdio.h>

int luhn_sum(long card_number);

int main(void)
{
    // Solicitar numero de cartao de credito ao usuario
    long card_number;
    printf("Numero: ");
    if (scanf("%ld", &card_number) != 1 || card_number <= 0)
    {
        printf("INVALID\n");
        return 1;
    }

    // Calcular a soma de Luhn
    int sum = luhn_sum(card_number);

    // Verificar se o numero de cartao e valido
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Determinar o numero de digitos no cartao
    int digit_count = 0;
    long temp = card_number;
    while (temp > 0)
    {
        temp /= 10;
        digit_count++;
    }

    // Verificar o tipo de cartao com base nos digitos iniciais
    if (digit_count == 15 && (card_number / 10000000000000 == 34 || card_number / 10000000000000 == 37))
    {
        printf("AMEX\n");
    }
    else if (digit_count == 16 && (card_number / 100000000000000 >= 51 && card_number / 100000000000000 <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((digit_count == 13 || digit_count == 16) && (card_number / 1000000000000 == 4 || card_number / 1000000000000000 == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

// Funcao para calcular a soma do algoritmo de Luhn
int luhn_sum(long card_number)
{
    int sum = 0;
    int digit_count = 0;
    long temp = card_number;

    // Contar o numero de digitos
    while (temp > 0)
    {
        temp /= 10;
        digit_count++;
    }

    // Processar cada digito
    for (int i = 0; i < digit_count; i++)
    {
        int digit = card_number % 10;
        card_number /= 10;

        if (i % 2 == 1)
        {
            int doubled = digit * 2;
            sum += (doubled > 9) ? (doubled - 9) : doubled;
        }
        else
        {
            sum += digit;
        }
    }

    return sum;
}
