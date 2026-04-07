#include <stdlib.h>
#include "vetor.h"

static int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void gerarVetor(int *v, int n) {
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 1000000;
    }
}

void ordenarVetor(int *v, int n) {
    qsort(v, n, sizeof(int), cmp);
}
