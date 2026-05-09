#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Tipos Abstratos de Dados
#include "../../shared/arvore.h"
#include "../../shared/stats.h"

#define N 1000000
#define NUM_ARVORES 10

/*
 * ========================================================================
 * TRABALHO 2 - QUESTÃO 4
 * Comparação de Desempenho: Árvore AVL vs Árvore Binária de Pesquisa
 * 
 * Compara tempo de criação, altura e tempo de busca entre árvores AVL
 * e árvores binárias de pesquisa com 1.000.000 de elementos.
 * 
 * MONITORAMENTO DE MEMÓRIA:
 * Para verificar o uso de memória durante a execução, utilize:
 *   /usr/bin/time -v ./programa 2>&1 | grep "Maximum resident"
 * 
 * Ou para ver todas as estatísticas de memória:
 *   /usr/bin/time -v ./programa
 * ========================================================================
 */

/**
 * Executa 30 buscas em uma árvore BST e retorna o tempo médio.
 */
double executarBuscaBST(Arvore arvore, int chaves[]) {
    double tempos[EXEC];
    
    for (int i = 0; i < EXEC; i++) {
        clock_t inicio = clock();
        buscar_arvore(arvore, chaves[i]);
        clock_t fim = clock();
        tempos[i] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }
    
    return calcularMedia(tempos);
}

/**
 * Executa 30 buscas em uma árvore AVL e retorna o tempo médio.
 */
double executarBuscaAVL(ArvoreAVL arvore, int chaves[]) {
    double tempos[EXEC];
    
    for (int i = 0; i < EXEC; i++) {
        clock_t inicio = clock();
        buscar_arvore_avl(arvore, chaves[i]);
        clock_t fim = clock();
        tempos[i] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }
    
    return calcularMedia(tempos);
}

int main() {
    srand(42);  // Seed fixo para reprodutibilidade

    printf("========================================================================\n");
    printf("  COMPARAÇÃO: ÁRVORE AVL vs ÁRVORE BINÁRIA DE PESQUISA (BST)\n");
    printf("  Dataset: %d elementos | Execuções: %d árvores de cada tipo\n", N, NUM_ARVORES);
    printf("========================================================================\n\n");

    // ===== FASE 1: Geração do Dataset =====
    printf("[1/6] Gerando dataset com %d elementos...\n", N);
    int *dataset = malloc(N * sizeof(int));
    if (dataset == NULL) {
        fprintf(stderr, "Erro: falha na alocação de memória para o dataset\n");
        return 1;
    }
    
    // Gera valores aleatórios únicos
    for (int i = 0; i < N; i++) {
        dataset[i] = rand();
    }
    printf("      Dataset gerado com sucesso!\n");

    // ===== FASE 2: Criação das Árvores BST =====
    printf("\n[2/6] Criando %d árvores BST...\n", NUM_ARVORES);
    
    Arvore arvores_bst[NUM_ARVORES];
    double tempos_criacao_bst[NUM_ARVORES];
    int alturas_bst[NUM_ARVORES];
    
    for (int exec = 0; exec < NUM_ARVORES; exec++) {
        printf("      Criando BST #%d...\n", exec + 1);
        
        clock_t inicio = clock();
        arvores_bst[exec] = criar_arvore();
        
        for (int i = 0; i < N; i++) {
            arvores_bst[exec] = inserir(arvores_bst[exec], dataset[i]);
        }
        
        clock_t fim = clock();
        tempos_criacao_bst[exec] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        alturas_bst[exec] = obter_altura_bst(arvores_bst[exec]);
        
        printf("        Tempo: %.6f s | Altura: %d\n", 
               tempos_criacao_bst[exec], alturas_bst[exec]);
    }

    // ===== FASE 3: Criação das Árvores AVL =====
    printf("\n[3/6] Criando %d árvores AVL...\n", NUM_ARVORES);
    
    ArvoreAVL arvores_avl[NUM_ARVORES];
    double tempos_criacao_avl[NUM_ARVORES];
    int alturas_avl[NUM_ARVORES];
    
    for (int exec = 0; exec < NUM_ARVORES; exec++) {
        printf("      Criando AVL #%d...\n", exec + 1);
        
        clock_t inicio = clock();
        arvores_avl[exec] = criar_arvore_avl();
        
        for (int i = 0; i < N; i++) {
            arvores_avl[exec] = inserir_avl(arvores_avl[exec], dataset[i]);
        }
        
        clock_t fim = clock();
        tempos_criacao_avl[exec] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        alturas_avl[exec] = obter_altura(arvores_avl[exec]);
        
        printf("        Tempo: %.6f s | Altura: %d\n", 
               tempos_criacao_avl[exec], alturas_avl[exec]);
    }

    // ===== FASE 4: Geração das Chaves de Busca =====
    printf("\n[4/6] Gerando chaves de busca...\n");
    int chaves[EXEC];
    
    for (int i = 0; i < EXEC; i++) {
        if (i < 15) {
            // Primeiras 15 buscas: elementos garantidamente presentes
            chaves[i] = dataset[rand() % N];
        } else {
            // Últimas 15 buscas: elementos aleatórios (podem ou não estar presentes)
            chaves[i] = rand();
        }
    }
    printf("      %d chaves geradas (15 presentes + 15 aleatórias)\n", EXEC);

    // ===== FASE 5: Medição de Tempo de Busca BST =====
    printf("\n[5/6] Medindo tempo de busca nas BST...\n");
    
    double tempos_busca_bst[NUM_ARVORES];
    for (int exec = 0; exec < NUM_ARVORES; exec++) {
        tempos_busca_bst[exec] = executarBuscaBST(arvores_bst[exec], chaves);
        printf("      BST #%d - Média de busca: %.9f s\n", 
               exec + 1, tempos_busca_bst[exec]);
    }

    // ===== FASE 6: Medição de Tempo de Busca AVL =====
    printf("\n[6/6] Medindo tempo de busca nas AVL...\n");
    
    double tempos_busca_avl[NUM_ARVORES];
    for (int exec = 0; exec < NUM_ARVORES; exec++) {
        tempos_busca_avl[exec] = executarBuscaAVL(arvores_avl[exec], chaves);
        printf("      AVL #%d - Média de busca: %.9f s\n", 
               exec + 1, tempos_busca_avl[exec]);
    }

    // ===== ANÁLISE ESTATÍSTICA =====
    printf("\n========================================================================\n");
    printf("  RESULTADOS COMPARATIVOS\n");
    printf("========================================================================\n\n");

    // Calcular estatísticas manualmente para arrays de tamanho NUM_ARVORES
    // (A função calcularMedia usa EXEC=30, mas temos NUM_ARVORES=10)
    
    // Estatísticas de criação BST
    double soma_criacao_bst = 0.0;
    int altura_min_bst = alturas_bst[0], altura_max_bst = alturas_bst[0];
    for (int i = 0; i < NUM_ARVORES; i++) {
        soma_criacao_bst += tempos_criacao_bst[i];
        if (alturas_bst[i] < altura_min_bst) altura_min_bst = alturas_bst[i];
        if (alturas_bst[i] > altura_max_bst) altura_max_bst = alturas_bst[i];
    }
    double media_criacao_bst = soma_criacao_bst / NUM_ARVORES;
    
    double soma_quad_bst = 0.0;
    for (int i = 0; i < NUM_ARVORES; i++) {
        double diff = tempos_criacao_bst[i] - media_criacao_bst;
        soma_quad_bst += diff * diff;
    }
    double desvio_criacao_bst = sqrt(soma_quad_bst / NUM_ARVORES);
    
    printf("=== CRIAÇÃO DE ÁRVORES BST ===\n");
    printf("Tempo médio de criação: %.6f s\n", media_criacao_bst);
    printf("Desvio padrão: %.6f s\n", desvio_criacao_bst);
    printf("Altura mínima: %d | Altura máxima: %d\n", altura_min_bst, altura_max_bst);
    
    // Estatísticas de criação AVL
    double soma_criacao_avl = 0.0;
    int altura_min_avl = alturas_avl[0], altura_max_avl = alturas_avl[0];
    for (int i = 0; i < NUM_ARVORES; i++) {
        soma_criacao_avl += tempos_criacao_avl[i];
        if (alturas_avl[i] < altura_min_avl) altura_min_avl = alturas_avl[i];
        if (alturas_avl[i] > altura_max_avl) altura_max_avl = alturas_avl[i];
    }
    double media_criacao_avl = soma_criacao_avl / NUM_ARVORES;
    
    double soma_quad_avl = 0.0;
    for (int i = 0; i < NUM_ARVORES; i++) {
        double diff = tempos_criacao_avl[i] - media_criacao_avl;
        soma_quad_avl += diff * diff;
    }
    double desvio_criacao_avl = sqrt(soma_quad_avl / NUM_ARVORES);
    
    printf("\n=== CRIAÇÃO DE ÁRVORES AVL ===\n");
    printf("Tempo médio de criação: %.6f s\n", media_criacao_avl);
    printf("Desvio padrão: %.6f s\n", desvio_criacao_avl);
    printf("Altura mínima: %d | Altura máxima: %d\n", altura_min_avl, altura_max_avl);
    
    // Estatísticas de busca BST
    double soma_busca_bst = 0.0;
    for (int i = 0; i < NUM_ARVORES; i++) {
        soma_busca_bst += tempos_busca_bst[i];
    }
    double media_busca_bst = soma_busca_bst / NUM_ARVORES;
    
    double soma_quad_busca_bst = 0.0;
    for (int i = 0; i < NUM_ARVORES; i++) {
        double diff = tempos_busca_bst[i] - media_busca_bst;
        soma_quad_busca_bst += diff * diff;
    }
    double desvio_busca_bst = sqrt(soma_quad_busca_bst / NUM_ARVORES);
    
    printf("\n=== BUSCA EM ÁRVORES BST ===\n");
    printf("Tempo médio de busca: %.9f s\n", media_busca_bst);
    printf("Desvio padrão: %.9f s\n", desvio_busca_bst);
    
    // Estatísticas de busca AVL
    double soma_busca_avl = 0.0;
    for (int i = 0; i < NUM_ARVORES; i++) {
        soma_busca_avl += tempos_busca_avl[i];
    }
    double media_busca_avl = soma_busca_avl / NUM_ARVORES;
    
    double soma_quad_busca_avl = 0.0;
    for (int i = 0; i < NUM_ARVORES; i++) {
        double diff = tempos_busca_avl[i] - media_busca_avl;
        soma_quad_busca_avl += diff * diff;
    }
    double desvio_busca_avl = sqrt(soma_quad_busca_avl / NUM_ARVORES);
    
    printf("\n=== BUSCA EM ÁRVORES AVL ===\n");
    printf("Tempo médio de busca: %.9f s\n", media_busca_avl);
    printf("Desvio padrão: %.9f s\n", desvio_busca_avl);

    // Comparação direta
    printf("\n========================================================================\n");
    printf("  COMPARAÇÃO DIRETA\n");
    printf("========================================================================\n");
    printf("Criação AVL vs BST: %.2fx %s lenta\n", 
           media_criacao_avl / media_criacao_bst,
           (media_criacao_avl > media_criacao_bst) ? "mais" : "menos");
    printf("Altura AVL vs BST: %.2f%% da altura BST\n", 
           (100.0 * altura_max_avl) / altura_max_bst);
    printf("Busca AVL vs BST: %.2fx %s rápida\n", 
           media_busca_bst / media_busca_avl,
           (media_busca_avl < media_busca_bst) ? "mais" : "menos");
    
    printf("\n========================================================================\n");
    printf("  RESUMO\n");
    printf("========================================================================\n");
    printf("Dataset: %d elementos inteiros\n", N);
    printf("Execuções: %d árvores de cada tipo\n", NUM_ARVORES);
    printf("Buscas por árvore: %d consultas\n", EXEC);
    printf("\nPara análise de memória, execute:\n");
    printf("  /usr/bin/time -v ./programa\n");
    printf("========================================================================\n");

    // ===== LIMPEZA DE MEMÓRIA =====
    for (int i = 0; i < NUM_ARVORES; i++) {
        liberar_arvore(arvores_bst[i]);
        liberar_arvore_avl(arvores_avl[i]);
    }
    free(dataset);

    return 0;
}
