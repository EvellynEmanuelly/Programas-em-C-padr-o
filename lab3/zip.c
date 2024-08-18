#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Função para imprimir um array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Função de ordenação: Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        if (min_idx != i) {
            int temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
    }
}

// Função de ordenação: Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Função auxiliar para o Merge Sort: mescla duas submatrizes de arr[]
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Cria arrays temporários
    int L[n1], R[n2];

    // Copia os dados para os arrays temporários L[] e R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Mescla os arrays temporários de volta para arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[], se houver algum
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver algum
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Função de ordenação: Merge Sort
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Ordena a primeira e a segunda metades
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Mescla as metades ordenadas
        merge(arr, l, m, r);
    }
}

// Função para ler números de um arquivo de texto e armazená-los em um array
void readNumbersFromFile(const char *filename, int arr[], int n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s [sort_file] [text_file.txt]\n", argv[0]);
        return 1;
    }

    char *sortFileName = argv[1];
    char *textFileName = argv[2];

    // Lê os números do arquivo de texto
    FILE *textFile = fopen(textFileName, "r");
    if (textFile == NULL) {
        printf("Erro ao abrir o arquivo de texto.\n");
        return 1;
    }
    int n;
    fscanf(textFile, "%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(textFile, "%d", &arr[i]);
    }
    fclose(textFile);

    // Executa a ordenação
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    if (strcmp(sortFileName, "sort1") == 0) {
        selectionSort(arr, n);
    } else if (strcmp(sortFileName, "sort2") == 0) {
        bubbleSort(arr, n);
    } else if (strcmp(sortFileName, "sort3") == 0) {
        mergeSort(arr, 0, n - 1);
    } else {
        printf("Nome do arquivo de classificação inválido.\n");
        return 1;
    }
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Imprime o array ordenado
    // printArray(arr, n);

    // Libera a memória alocada para o array
    free(arr);

    // Imprime o tempo de execução
    printf("Tempo de execução: %f segundos.\n", cpu_time_used);

    return 0;
}
