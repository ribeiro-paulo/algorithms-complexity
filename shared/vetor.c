#include <stdlib.h>
#include <string.h>
#include "vetor.h"

// Compara dois inteiros para ordenação
static int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void gerarVetor(int *v, int n) {
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 1000000; // Gera números aleatórios entre 0 e 999999
    }
}

void ordenarVetor(int *v, int n) {
    qsort(v, n, sizeof(int), cmp);  //qsort usa função cmp para ordenar o vetor automaticamente.
}

// ========== Algoritmos de Busca ==========

int buscaSequencial(int *v, int n, int chave) {
    for (int i = 0; i < n; i++) {
        if (v[i] == chave)
            return i;
    }
    return -1;
}

int buscaBinaria(int *v, int n, int chave) {
    int ini = 0, fim = n - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;

        if (v[meio] == chave)
            return meio;
        else if (v[meio] < chave)
            ini = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

// ========== Algoritmos de Ordenação ==========

void bubbleSort(int *v, int n) {
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                int tmp = v[j];
                v[j]   = v[j + 1];
                v[j + 1] = tmp;
                trocou = 1;
            }
        }
        if (!trocou) break; 
    }
}

void insertionSort(int *v, int n) {
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

void selectionSort(int *v, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[minIdx])
                minIdx = j;
        }
        if (minIdx != i) {
            int tmp  = v[i];
            v[i]     = v[minIdx];
            v[minIdx] = tmp;
        }
    }
}


static void quickSortRec(int *v, int esq, int dir) {
    if (esq >= dir) return;

    int meio = esq + (dir - esq) / 2;
    int t = v[meio]; v[meio] = v[dir]; v[dir] = t;

    int pivo = v[dir];
    int i = esq - 1;
    for (int j = esq; j < dir; j++) {
        if (v[j] <= pivo) {
            i++;
            int tmp = v[i]; v[i] = v[j]; v[j] = tmp;
        }
    }
    
    int tmp = v[i + 1]; v[i + 1] = v[dir]; v[dir] = tmp;
    int p = i + 1;

    quickSortRec(v, esq, p - 1);
    quickSortRec(v, p + 1, dir);
}

void quickSort(int *v, int n) {
    if (n > 1)
        quickSortRec(v, 0, n - 1);
}


static void mergeSortRec(int *v, int *tmp, int esq, int dir) {
    if (esq >= dir) return;
    int meio = esq + (dir - esq) / 2;
    mergeSortRec(v, tmp, esq, meio);
    mergeSortRec(v, tmp, meio + 1, dir);

    int n = dir - esq + 1;
    memcpy(tmp + esq, v + esq, n * sizeof(int));
    int i = esq, j = meio + 1, k = esq;
    while (i <= meio && j <= dir)
        v[k++] = (tmp[i] <= tmp[j]) ? tmp[i++] : tmp[j++];
    while (i <= meio) v[k++] = tmp[i++];
    while (j <= dir)  v[k++] = tmp[j++];
}

void mergeSort(int *v, int n) {
    if (n <= 1) return;
    int *tmp = malloc(n * sizeof(int));
    mergeSortRec(v, tmp, 0, n - 1);
    free(tmp);
}
