#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int validate_key(char* key);
void caesar_cipher(char* text, int key, int encrypt);

int main(int argc, char *argv[])
{
    while (1)
    {
        // Verificar se a quantidade de argumentos está correta
        if (argc != 2)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

        // Validar a chave fornecida
        char* key = argv[1];
        if (!validate_key(key))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

        // Converter a chave para um número inteiro
        int k = atoi(key);

        // Solicitar ao usuário escolher criptografar (1) ou descriptografar (0)
        int encrypt;
        printf("Encrypt (1) or Decrypt (0)? ");
        scanf("%d", &encrypt);
        getchar(); // Limpar o newline deixado por scanf

        // Solicitar ao usuário uma string de texto
        char text[256];
        printf("Text (or 'exit' to finish): ");
        fgets(text, sizeof(text), stdin);

        // Remover o newline capturado pelo fgets
        text[strcspn(text, "\n")] = '\0';

        // Verificar se o usuário deseja encerrar o programa
        if (strcmp(text, "exit") == 0)
        {
            printf("Programa encerrado.\n");
            break;
        }

        // Aplicar a cifra de César e imprimir o resultado
        printf("Result: ");
        caesar_cipher(text, k, encrypt);
        printf("\n");
    }

    return 0;
}

// Função para validar a chave
int validate_key(char* key)
{
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (!isdigit(key[i]))
        {
            return 0; // A chave contém um caractere não decimal
        }
    }
    return 1;
}

// Função para aplicar a cifra de César
void caesar_cipher(char* text, int key, int encrypt)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            char base = isupper(text[i]) ? 'A' : 'a';
            int offset = encrypt ? key : -key;
            printf("%c", (text[i] - base + offset + 26) % 26 + base);
        }
        else
        {
            printf("%c", text[i]);
        }
    }
}
