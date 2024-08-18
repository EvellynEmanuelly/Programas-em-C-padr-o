#include <stdio.h>

int luhn_sum(long card_number);
void get_card_number(long *card_number);
char get_char(const char *prompt);

int main(void)
{
    char continue_check;
    
    do
    {
        // Solicitar número de cartão de crédito ao usuário
        long card_number;
        get_card_number(&card_number);

        // Verificar se o número de cartão é válido
        int digit_count = 0;
        long temp = card_number;
        while (temp > 0)
        {
            temp /= 10;
            digit_count++;
        }

        if (digit_count != 13 && digit_count != 15 && digit_count != 16)
        {
            printf("INVALID\n");
            continue; // Volta para o início do loop
        }

        // Verificar o tipo de cartão
        int digits[digit_count];
        temp = card_number;
        for (int i = 0; i < digit_count; i++)
        {
            digits[i] = temp % 10;
            temp /= 10;
        }

        int sum = 0;
        for (int i = 1; i < digit_count; i += 2)
        {
            int doubled = digits[i] * 2;
            sum += doubled % 10 + doubled / 10;
        }

        for (int i = 0; i < digit_count; i += 2)
        {
            sum += digits[i];
        }

        if (sum % 10 == 0)
        {
            // Verificar o tipo de cartão com base nos dígitos iniciais
            if (digit_count == 15 &&
                (digits[digit_count - 1] == 3 && (digits[digit_count - 2] == 4 || digits[digit_count - 2] == 7)))
            {
                printf("AMEX\n");
            }
            else if (digit_count == 16 &&
                     (digits[digit_count - 1] == 5 && (digits[digit_count - 2] >= 1 && digits[digit_count - 2] <= 5)))
            {
                printf("MASTERCARD\n");
            }
            else if ((digit_count == 13 || digit_count == 16) && digits[digit_count - 1] == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
        
        // Perguntar ao usuário se deseja verificar outro número
        continue_check = get_char("Deseja verificar outro numero? (s/n): ");
        
    }
    while (continue_check == 's' || continue_check == 'S');

    return 0;
}

// Função para calcular a soma do algoritmo de Luhn
int luhn_sum(long card_number)
{
    int sum = 0;
    int digit_count = 0;
    long temp = card_number;

    // Contar o número de dígitos
    while (temp > 0)
    {
        temp /= 10;
        digit_count++;
    }

    // Processar cada dígito
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

// Função para obter um número de cartão do usuário
void get_card_number(long *card_number)
{
    printf("Numero do Cartao: ");
    while (scanf("%ld", card_number) != 1 || *card_number <= 0)
    {
        while (getchar() != '\n') // Limpa o buffer de entrada
            ;
        printf("Numero invalido. Tente novamente: ");
    }
}

// Função para obter um caractere do usuário
char get_char(const char *prompt)
{
    char c;
    printf("%s", prompt);
    while (scanf(" %c", &c) != 1)
    {
        while (getchar() != '\n') // Limpa o buffer de entrada
            ;
        printf("Entrada invalida. %s", prompt);
    }
    return c;
}
