#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_letters(const char *text);
int count_words(const char *text);
int count_sentences(const char *text);
int calculate_grade(int letters, int words, int sentences);

int main(void)
{
    // Solicitar ao usuário uma string de texto
    char text[1000];
    printf("Texto: ");
    fgets(text, sizeof(text), stdin);

    // Remover o caractere de nova linha, se presente
    text[strcspn(text, "\n")] = '\0';

    // Contar letras, palavras e frases
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Calcular o índice Coleman-Liau e imprimir o resultado
    int grade = calculate_grade(letters, words, sentences);
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

    return 0;
}

// Contar o número de letras no texto
int count_letters(const char *text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

// Contar o número de palavras no texto
int count_words(const char *text)
{
    int count = 1; // Começa em 1 porque a última palavra não é seguida por espaço
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            count++;
        }
    }
    return count;
}

// Contar o número de frases no texto
int count_sentences(const char *text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}

// Calcular o índice Coleman-Liau
int calculate_grade(int letters, int words, int sentences)
{
    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;
    int index = (int) (0.0588 * L - 0.296 * S - 15.8 + 0.5); // Arredondamento para o número inteiro mais próximo
    return index;
}
