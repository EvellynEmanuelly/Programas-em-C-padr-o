#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 9

int preferences[MAX][MAX];
typedef struct
{
    int winner;
    int loser;
} pair;

char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
int pair_count;
int candidate_count;

bool vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_loser(void);
bool is_cycle(int winner, int loser, bool visited[]);
void print_preferences(void);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = 0;
        }
    }

    int voter_count;
    printf("Number of voters: ");
    if (scanf("%d", &voter_count) != 1 || voter_count < 0)
    {
        printf("Invalid input.\n");
        return 3;
    }

    // Clear input buffer
    while (getchar() != '\n');

    for (int i = 0; i < voter_count; i++)
    {
        int ranks[candidate_count];

        for (int j = 0; j < candidate_count; j++)
        {
            char name[100];
            printf("Rank %i: ", j + 1);
            if (fgets(name, sizeof(name), stdin) == NULL)
            {
                printf("Error reading input.\n");
                return 4;
            }
            // Remove trailing newline character
            name[strcspn(name, "\n")] = '\0';

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    // Debugging: print preferences matrix
    print_preferences();

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_loser(); // Atualizado para mostrar o perdedor
    return 0;
}

bool vote(int rank, char *name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

int compare_pairs(const void *a, const void *b)
{
    pair *pairA = (pair *)a;
    pair *pairB = (pair *)b;
    return (preferences[pairB->winner][pairB->loser] - preferences[pairA->winner][pairA->loser]);
}

void sort_pairs(void)
{
    qsort(pairs, pair_count, sizeof(pair), compare_pairs);
}

void lock_pairs(void)
{
    bool visited[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        visited[i] = false;
    }

    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (!is_cycle(winner, loser, visited))
        {
            preferences[winner][loser] = 1;
        }
    }
}

bool is_cycle(int winner, int loser, bool visited[])
{
    if (visited[loser])
    {
        return true;
    }
    visited[loser] = true;

    for (int i = 0; i < candidate_count; i++)
    {
        if (preferences[loser][i] == 1)
        {
            if (is_cycle(winner, i, visited))
            {
                return true;
            }
        }
    }

    visited[loser] = false;
    return false;
}

void print_loser(void)
{
    // Inicializa um array para contar o número de derrotas para cada candidato
    int loss_count[MAX] = {0};

    // Conta o número de derrotas para cada candidato
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[j][i] > preferences[i][j])
            {
                loss_count[i]++;
            }
        }
    }

    // Encontra o candidato com o maior número de derrotas (ou seja, o perdedor)
    int loser = 0;
    for (int i = 1; i < candidate_count; i++)
    {
        if (loss_count[i] > loss_count[loser])
        {
            loser = i;
        }
    }

    printf("Loser: %s\n", candidates[loser]);
}

void print_preferences(void)
{
    printf("Preferences matrix:\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d ", preferences[i][j]);
        }
        printf("\n");
    }
}
