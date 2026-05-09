#ifndef VETOR_H
#define VETOR_H

// Geração e ordenação básica
void gerarVetor(int *v, int n);
void ordenarVetor(int *v, int n);

// Algoritmos de busca
int buscaSequencial(int *v, int n, int chave);
int buscaBinaria(int *v, int n, int chave);

// Algoritmos de ordenação
void bubbleSort(int *v, int n);
void insertionSort(int *v, int n);
void selectionSort(int *v, int n);
void quickSort(int *v, int n);
void mergeSort(int *v, int n);

#endif
