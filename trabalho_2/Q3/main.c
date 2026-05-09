#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

// Tipos Abstratos de Dados
#include "../../shared/vetor.h"
#include "../../shared/arvore.h"
#include "../../shared/stats.h"

#define N 1000000

// Estrutura para rastreamento de memória
typedef struct {
    long min_memoria_kb;
    long max_memoria_kb;
    long memoria_atual_kb;
} MonitorMemoria;

/*
 * ========================================================================
 * TRABALHO 2 - QUESTÃO 3
 * Comparação de Busca: Árvore Binária de Pesquisa vs Vetor Ordenado
 * 
 * MONITORAMENTO DE MEMÓRIA:
 * Implementa monitoramento interno usando getrusage() para reportar
 * a menor e maior ocupação de memória durante a execução.
 * ========================================================================
 */

/**
 * Obtém o uso de memória atual do processo em KB.
 * @return Uso de memória em kilobytes
 */
long obterMemoriaAtual() {
    struct rusage uso;
    getrusage(RUSAGE_SELF, &uso);
    // ru_maxrss está em KB no Linux, mas em bytes no macOS
    #ifdef __APPLE__
        return uso.ru_maxrss / 1024;
    #else
        return uso.ru_maxrss;
    #endif
}

/**
 * Atualiza o monitor de memória com a medição atual.
 * @param monitor Ponteiro para a estrutura de monitoramento
 * @param fase Descrição da fase atual (para impressão)
 */
void atualizarMemoria(MonitorMemoria *monitor, const char *fase) {
    monitor->memoria_atual_kb = obterMemoriaAtual();
    
    // Primeira medição
    if (monitor->min_memoria_kb == 0) {
        monitor->min_memoria_kb = monitor->memoria_atual_kb;
        monitor->max_memoria_kb = monitor->memoria_atual_kb;
    }
    
    // Atualiza mínimo e máximo
    if (monitor->memoria_atual_kb < monitor->min_memoria_kb) {
        monitor->min_memoria_kb = monitor->memoria_atual_kb;
    }
    if (monitor->memoria_atual_kb > monitor->max_memoria_kb) {
        monitor->max_memoria_kb = monitor->memoria_atual_kb;
    }
    
    printf("      [Memória em %s: %.2f MB]\n", fase, monitor->memoria_atual_kb / 1024.0);
}

/**
 * Executa 30 buscas na árvore binária de pesquisa e calcula o tempo médio.
 */
void executarBuscaArvore(Arvore arvore, int chaves[]) {
    double tempos[EXEC];

    printf("\n=== Busca na Árvore Binária de Pesquisa ===\n");
    
    for (int i = 0; i < EXEC; i++) {
        clock_t inicio = clock();
        buscar_arvore(arvore, chaves[i]);
        clock_t fim = clock();

        tempos[i] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Busca BST - Execução %d: %.9f s\n", i + 1, tempos[i]);
    }

    double media = calcularMedia(tempos);
    double desvio = calcularDesvio(tempos, media);

    printf("Média BST: %.9f s\n", media);
    printf("Desvio padrão BST: %.9f s\n", desvio);
}

/**
 * Executa 30 buscas binárias no vetor ordenado e calcula o tempo médio.
 */
void executarBuscaVetor(int *vetor, int chaves[]) {
    double tempos[EXEC];

    printf("\n=== Busca Binária no Vetor Ordenado ===\n");
    
    for (int i = 0; i < EXEC; i++) {
        clock_t inicio = clock();
        buscaBinaria(vetor, N, chaves[i]);
        clock_t fim = clock();

        tempos[i] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Busca Vetor - Execução %d: %.9f s\n", i + 1, tempos[i]);
    }

    double media = calcularMedia(tempos);
    double desvio = calcularDesvio(tempos, media);

    printf("Média Vetor: %.9f s\n", media);
    printf("Desvio padrão Vetor: %.9f s\n", desvio);
}

int main() {
    srand(time(NULL)); // Inicializa gerador de números aleatórios

    // Inicializa monitor de memória
    MonitorMemoria monitor = {0, 0, 0};

    printf("========================================\n");
    printf("  COMPARAÇÃO: BST vs VETOR ORDENADO\n");
    printf("  Estruturas com %d elementos\n", N);
    printf("========================================\n\n");

    atualizarMemoria(&monitor, "início");

    // ===== FASE 1: Geração e Inserção de Dados =====
    printf("\n[1/5] Gerando vetor com %d elementos...\n", N);
    int *vetor = malloc(N * sizeof(int));
    if (vetor == NULL) {
        fprintf(stderr, "Erro: falha na alocação de memória para o vetor\n");
        return 1;
    }
    
    gerarVetor(vetor, N);
    printf("      Vetor gerado com sucesso!\n");
    atualizarMemoria(&monitor, "pós-alocação do vetor");

    // ===== FASE 2: Construção da Árvore Binária =====
    printf("\n[2/5] Inserindo %d elementos na BST...\n", N);
    Arvore arvore = criar_arvore();
    
    // Insere os mesmos valores do vetor na árvore
    // Nota: Valores são inseridos na ordem aleatória para evitar árvore degenerada
    for (int i = 0; i < N; i++) {
        arvore = inserir(arvore, vetor[i]);
        
        // Progresso a cada 100.000 elementos
        if ((i + 1) % 100000 == 0) {
            printf("      Inseridos %d elementos...\n", i + 1);
        }
    }
    printf("      BST construída com sucesso!\n");
    atualizarMemoria(&monitor, "pós-construção da BST");

    // ===== FASE 3: Ordenação do Vetor =====
    printf("\n[3/5] Ordenando vetor para busca binária...\n");
    ordenarVetor(vetor, N);
    printf("      Vetor ordenado!\n");
    atualizarMemoria(&monitor, "pós-ordenação do vetor");

    // ===== FASE 4: Geração das Chaves de Busca =====
    printf("\n[4/5] Gerando chaves de busca...\n");
    int chaves[EXEC];
    
    for (int i = 0; i < EXEC; i++) {
        if (i < 15) {
            // Primeiras 15 buscas: elementos garantidamente presentes
            chaves[i] = vetor[rand() % N];
        } else {
            // Últimas 15 buscas: elementos aleatórios (podem ou não estar presentes)
            chaves[i] = rand() % 2000000;
        }
    }
    printf("      %d chaves de busca geradas!\n", EXEC);
    printf("      (15 garantidas presentes + 15 aleatórias)\n");

    // ===== FASE 5: Execução das Buscas e Medição =====
    printf("\n[5/5] Executando buscas e medindo tempos...\n");
    
    // Busca na BST
    executarBuscaArvore(arvore, chaves);
    
    // Busca no Vetor
    executarBuscaVetor(vetor, chaves);

    atualizarMemoria(&monitor, "pós-buscas");

    // ===== RESUMO FINAL =====
    printf("\n========================================\n");
    printf("  RESUMO COMPARATIVO\n");
    printf("========================================\n");
    printf("Estrutura de dados: %d elementos inteiros\n", N);
    printf("Número de buscas: %d execuções cada\n", EXEC);
    printf("Chaves de busca: 15 presentes + 15 aleatórias\n");
    printf("\nConsulte as médias acima para comparação de desempenho.\n");
    
    printf("\n========================================\n");
    printf("  UTILIZAÇÃO DE MEMÓRIA\n");
    printf("========================================\n");
    printf("Menor ocupação: %.2f MB (%ld KB)\n", 
           monitor.min_memoria_kb / 1024.0, monitor.min_memoria_kb);
    printf("Maior ocupação: %.2f MB (%ld KB)\n", 
           monitor.max_memoria_kb / 1024.0, monitor.max_memoria_kb);
    printf("Variação: %.2f MB\n", 
           (monitor.max_memoria_kb - monitor.min_memoria_kb) / 1024.0);
    printf("========================================\n");

    // ===== LIMPEZA DE MEMÓRIA =====
    liberar_arvore(arvore);
    free(vetor);
    
    atualizarMemoria(&monitor, "pós-limpeza");

    return 0;
}
