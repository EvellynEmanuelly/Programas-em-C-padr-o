#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool is_valid_key(char key[]);
void encrypt(char plaintext[], char key[]);

int main(int argc, char *argv[])
{
    // Verificar o número correto de argumentos
    if (argc != 2)
    {
        printf("Uso: ./substitution chave\n");
        return 1;
    }

    char *key = argv[1];

    // Verificar a validade da chave
    if (!is_valid_key(key))
    {
        printf("A chave deve conter 26 caracteres alfabéticos únicos.\n");
        return 1;
    }

    // Obter texto simples do usuário
    char plaintext[1000];
    printf("Texto simples: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    
    // Remover a nova linha no final do input
    plaintext[strcspn(plaintext, "\n")] = '\0';

    // Criptografar e imprimir o texto cifrado
    encrypt(plaintext, key);

    return 0;
}

// Verificar se a chave é válida
bool is_valid_key(char key[])
{
    int len = strlen(key);

    // Verificar o comprimento da chave
    if (len != 26)
    {
        return false;
    }

    // Verificar caracteres alfabéticos únicos
    for (int i = 0; i < len; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        for (int j = i + 1; j < len; j++)
        {
            if (key[i] == key[j])
            {
                return false;
            }
        }
    }

    return true;
}

// Criptografar o texto simples usando a chave fornecida
void encrypt(char plaintext[], char key[])
{
    printf("ciphertext: ");
    
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char current_char = plaintext[i];

        // Verificar se o caractere é alfabético
        if (isalpha(current_char))
        {
            // Determinar se o caractere original é maiúsculo ou minúsculo
            bool is_upper = isupper(current_char);

            // Converter para minúsculas para simplificar a comparação
            char normalized_char = tolower(current_char);

            // Encontrar a posição do caractere original na chave
            int index = normalized_char - 'a';

            // Obter o caractere correspondente na chave
            char encrypted_char = key[index];

            // Converter de volta para maiúsculas se o original era maiúsculo
            encrypted_char = is_upper ? toupper(encrypted_char) : encrypted_char;

            printf("%c", encrypted_char);
        }
        else
        {
            // Manter caracteres não alfabéticos inalterados
            printf("%c", current_char);
        }
    }

    printf("\n");
}
