#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../shared/vetor.h"
#include "../shared/lista.h"
#include "../shared/stats.h"

#define N 1000000

int main() {
    srand(time(NULL)); // Inicializa a semente para geração de números aleatórios

    int *vetor = malloc(N * sizeof(int)); // Aloca memória para o vetor
    gerarVetor(vetor, N);

    Lista *lista = criarLista();
    for (int i = 0; i < N; i++)
        inserirLista(lista, vetor[i]);

    int chaves[EXEC];
    for (int i = 0; i < EXEC; i++) {
        if (i < 15)
            chaves[i] = vetor[rand() % N];   /* garantido presente */
        else
            chaves[i] = rand() % 2000000;    /* pode ou não estar presente */
    }

    /* ---------- Busca no Vetor ---------- */
    double temposVetor[EXEC];

    printf("Executando Busca Sequencial no Vetor...\n");
    for (int i = 0; i < EXEC; i++) {
        clock_t inicio = clock();
        buscaSequencial(vetor, N, chaves[i]);
        clock_t fim = clock();

        temposVetor[i] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Vetor - Execução %d: %f\n", i + 1, temposVetor[i]);
    }

    double mediaVetor = calcularMedia(temposVetor);
    printf("Média (Vetor): %f\n\n", mediaVetor);

    /* ---------- Busca na Lista ---------- */
    double temposLista[EXEC];

    printf("Executando Busca Sequencial na Lista Encadeada...\n");
    for (int i = 0; i < EXEC; i++) {
        clock_t inicio = clock();
        buscaSequencialLista(lista, chaves[i]);
        clock_t fim = clock();

        temposLista[i] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Lista - Execução %d: %f\n", i + 1, temposLista[i]);
    }

    double mediaLista = calcularMedia(temposLista);
    printf("Média (Lista): %f\n\n", mediaLista);

    printf("=== Resumo ===\n");
    printf("Média Busca Sequencial - Vetor:          %f s\n", mediaVetor);
    printf("Média Busca Sequencial - Lista Encadeada: %f s\n", mediaLista);


    free(vetor);
    liberarLista(lista);

    return 0;
}
