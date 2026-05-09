#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para medir o tempo de execução CLOCK

// Tipos Abstratos de Dados
#include "../shared/vetor.h"
#include "../shared/stats.h"

#define N 1000000

void executarBuscaSequencial(int *v) {
    double tempos[EXEC];

    for (int i = 0; i < EXEC; i++) {
        int chave;

        if (i < 15)
            chave = v[rand() % N]; // sort valor vai ser encontrado no vetor
        else
            chave = rand() % 2000000; // sort valor pode não ser encontrado no vetor

        clock_t inicio = clock(); //Marca o tempo inicial da execução
        buscaSequencial(v, N, chave);
        clock_t fim = clock(); //Marca o tempo final da execução

        tempos[i] = ((double)(fim - inicio)) / CLOCKS_PER_SEC; //Calcula tempo de execução em segundos
        printf("Busca Sequencial - Execução %d: %f\n", i + 1, tempos[i]);
    }

    double media = calcularMedia(tempos);
    double desvio = calcularDesvio(tempos, media);

    printf("Média: %f\n", media);
    printf("Desvio padrão: %f\n\n", desvio);
}

void executarBuscaBinaria(int *v) {
    double tempos[EXEC];

    for (int i = 0; i < EXEC; i++) {
        int chave;

        if (i < 15)
            chave = v[rand() % N];
        else
            chave = rand() % 2000000;

        clock_t inicio = clock();
        buscaBinaria(v, N, chave);
        clock_t fim = clock();

        tempos[i] = ((double)(fim - inicio)) / CLOCKS_PER_SEC; //unidades de clock equivalem a 1 segundo
        printf("Busca Binária - Execução %d: %f\n", i + 1, tempos[i]);
    }

    double media = calcularMedia(tempos);
    double desvio = calcularDesvio(tempos, media);

    printf("Média: %f\n", media);
    printf("Desvio padrão: %f\n\n", desvio);
}

int main() {
    srand(time(NULL)); //Inicializa números aleatórios diferentes'

    // Aloca memória para vetor inteiro
    int *vetor = malloc(N * sizeof(int)); 

    gerarVetor(vetor, N);

    printf("Executando Busca Sequencial...\n");
    executarBuscaSequencial(vetor);

    printf("Ordenando vetor...\n");
    ordenarVetor(vetor, N);

    printf("Executando Busca Binária...\n");
    executarBuscaBinaria(vetor);

    free(vetor);

    return 0;
}
