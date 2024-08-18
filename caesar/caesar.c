#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Corrigindo o tipo de dado "string" para "char*"
int validate_key(char* key);
void encrypt_text(char* text, int key);

int main(int argc, char *argv[])
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

    // Solicitar ao usuário uma string de texto simples
    char plaintext[256];
    printf("plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    // Remover o newline que pode ser capturado pelo fgets
    plaintext[strcspn(plaintext, "\n")] = '\0';

    // Criptografar e imprimir o resultado
    printf("ciphertext: ");
    encrypt_text(plaintext, k);
    printf("\n");

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

// Função para criptografar o texto
void encrypt_text(char* text, int key)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            char base = isupper(text[i]) ? 'A' : 'a';
            printf("%c", (text[i] - base + key) % 26 + base);
        }
        else
        {
            printf("%c", text[i]);
        }
    }
}
