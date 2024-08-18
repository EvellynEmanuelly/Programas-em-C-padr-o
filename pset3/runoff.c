#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>  // Adicione esta linha para usar o tipo bool

// Define o número máximo de candidatos e eleitores
#define MAX_CANDIDATES 9
#define MAX_VOTERS 100

// Define a matriz de preferências global
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Define a estrutura do candidato
typedef struct
{
    char name[50];
    int votes;
    int eliminated;
} candidate;

// Declara a matriz global de candidatos
candidate candidates[MAX_CANDIDATES];

// Declara o número de candidatos e eleitores
int candidate_count;
int voter_count;

// Protótipos das funções
int get_int(const char *prompt);
void get_string(char *buffer, const char *prompt);
bool vote(int voter, int rank, const char *name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, char *argv[])
{
    // Verifica se há um número correto de argumentos
    if (argc < 2)
    {
        printf("Usage: %s candidate1 candidate2 ...\n", argv[0]);
        return 1;
    }

    // Preenche a matriz de candidatos com os nomes fornecidos nos argumentos de linha de comando
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %d\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        strncpy(candidates[i].name, argv[i + 1], sizeof(candidates[i].name) - 1);
        candidates[i].name[sizeof(candidates[i].name) - 1] = '\0';
        candidates[i].votes = 0;
        candidates[i].eliminated = 0;
    }

    // Solicita o número de eleitores
    voter_count = get_int("Number of voters: ");

    // Registra as preferências dos eleitores
    for (int i = 0; i < voter_count; i++)
    {
        printf("Voter %d\n", i + 1);
        for (int j = 0; j < candidate_count; j++)
        {
            char name[50];
            sprintf(name, "Rank %d: ", j + 1);
            char buffer[100];
            get_string(buffer, name);

            // Registra a preferência do eleitor
            if (!vote(i, j, buffer))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        printf("\n");
    }

    // Realiza o segundo turno até que haja um vencedor
    while (true)
    {
        tabulate();
        if (print_winner())
        {
            break;
        }

        int min = find_min();
        if (is_tie(min))
        {
            printf("Tie! No winner.\n");
            break;
        }

        eliminate(min);
    }

    return 0;
}

// Função para obter um número inteiro com prompt
int get_int(const char *prompt)
{
    int value;
    printf("%s", prompt);
    if (scanf("%d", &value) != 1)
    {
        fprintf(stderr, "Error reading integer input.\n");
        exit(1);
    }
    return value;
}

// Função para obter uma string com prompt
void get_string(char *buffer, const char *prompt)
{
    printf("%s", prompt);
    if (scanf("%99s", buffer) != 1)  // Limita a leitura a 99 caracteres
    {
        fprintf(stderr, "Error reading string input.\n");
        exit(1);
    }
}

// Função para registrar um voto
bool vote(int voter, int rank, const char *name)
{
    // Itera sobre os candidatos
    for (int i = 0; i < candidate_count; i++)
    {
        // Verifica se o nome corresponde a um candidato válido e não eliminado
        if (strcmp(name, candidates[i].name) == 0 && !candidates[i].eliminated)
        {
            // Atualiza as preferências do eleitor
            preferences[voter][rank] = i;
            return true;
        }
    }

    // Retorna false se o nome não corresponder a nenhum candidato válido
    return false;
}

// Função para calcular os totais de votos em cada turno
void tabulate(void)
{
    // Zera os votos de todos os candidatos
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }

    // Contabiliza os votos de cada eleitor para o candidato de primeira escolha não eliminado
    for (int i = 0; i < voter_count; i++)
    {
        int top_choice = 0;

        // Encontra o candidato de primeira escolha não eliminado para o eleitor i
        while (candidates[preferences[i][top_choice]].eliminated)
        {
            top_choice++;
        }

        // Incrementa os votos do candidato de primeira escolha
        candidates[preferences[i][top_choice]].votes++;
    }
}

// Função para imprimir o vencedor, se houver
bool print_winner(void)
{
    // Verifica se algum candidato tem mais da metade dos votos
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    // Retorna false se não houver vencedor
    return false;
}

// Função para encontrar o número mínimo de votos entre os candidatos não eliminados
int find_min(void)
{
    int min_votes = voter_count;

    // Encontra o número mínimo de votos entre os candidatos não eliminados
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }

    return min_votes;
}

// Função para verificar se há um empate entre os candidatos não eliminados
bool is_tie(int min)
{
    // Verifica se todos os candidatos não eliminados têm o mesmo número de votos
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }

    return true;
}

// Função para eliminar os candidatos com o número mínimo de votos
void eliminate(int min)
{
    // Elimina os candidatos com o número mínimo de votos
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = 1;
        }
    }
}
