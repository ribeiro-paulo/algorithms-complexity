#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../shared/vetor.h"

//TODO: Organizar por classe vetor, organizado, entender a complexidade

#define N       100000
#define RODADAS 10

typedef void (*FuncOrdenacao)(int *, int); // Define um tipo de função para os algoritmos de ordenação.

static const char *nomes[] = {
    "Bubble Sort",
    "Insertion Sort",
    "Selection Sort",
    "Quicksort",
    "Merge Sort"
};

static FuncOrdenacao algoritmos[] = {
    bubbleSort,
    insertionSort,
    selectionSort,
    quickSort,
    mergeSort
};

// descobrir o tamanho do vetor, sem precisar contar manualmente.
#define N_ALGO 5

int main(void) {
    // inicializa o gerador de números aleatórios com base no horário atual.
    srand((unsigned)time(NULL));

    int *original = malloc(N * sizeof(int));
    int *copia    = malloc(N * sizeof(int)); // é uma copia garantindo que todos ordenem os mesmos dados.

    double tempos[N_ALGO][RODADAS];

    printf("Executando %d rodadas com vetor de %d elementos...\n\n",
           RODADAS, N);

    for (int r = 0; r < RODADAS; r++) {
        gerarVetor(original, N); 

        for (int a = 0; a < N_ALGO; a++) {
            //memcpy copia dados de uma área de memória para outra.
            memcpy(copia, original, N * sizeof(int));

            clock_t inicio = clock();
            algoritmos[a](copia, N);
            clock_t fim = clock();

            tempos[a][r] = (double)(fim - inicio) / CLOCKS_PER_SEC;
        }
    }

    free(copia);
    free(original);

    
    for (int a = 0; a < N_ALGO; a++) {
        printf("Algoritmo: %s\n", nomes[a]);

        double soma = 0.0;
        for (int r = 0; r < RODADAS; r++) {
            printf("  Execução %2d: tempo = %.6f s\n", r + 1, tempos[a][r]);
            soma += tempos[a][r];
        }

        printf("  Média: %.6f s\n\n", soma / RODADAS);
    }

    return 0;
}
