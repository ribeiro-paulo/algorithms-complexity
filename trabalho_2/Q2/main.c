#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../shared/arvore.h"

#define TOTAL_PACOTES 10000
#define TAXA_RETRANSMISSAO 0.05  // 5%
#define NUM_RETRANSMISSOES ((int)(TOTAL_PACOTES * TAXA_RETRANSMISSAO))

/**
 * Função para embaralhar um array usando o algoritmo Fisher-Yates.
 * Simula a chegada de pacotes em ordem aleatória.
 */
void embaralhar(int* array, int tamanho) {
    for (int i = tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

/**
 * Gera o conteúdo de um pacote.
 */
void gerar_conteudo_pacote(int id, char* buffer, size_t tamanho) {
    snprintf(buffer, tamanho, 
             "Pacote #%d: Trabalho 2 - AED2. Fragmento %d.",
             id, id);
}

int main(void) {
    srand(time(NULL));
    
    printf("=== Simulador de Recepção de Pacotes com BST ===\n");
    printf("Configuração: %d pacotes únicos, %.0f%% de retransmissões\n\n", 
           TOTAL_PACOTES, TAXA_RETRANSMISSAO * 100);
    
    // 1. Criar array de IDs ordenados
    int* ids = (int*) malloc(TOTAL_PACOTES * sizeof(int));
    if (ids == NULL) {
        fprintf(stderr, "Erro: falha na alocação de memória\n");
        return 1;
    }
    
    for (int i = 0; i < TOTAL_PACOTES; i++) {
        ids[i] = i + 1;  // IDs de 1 a 10000
    }
    
    // 2. Embaralhar para simular ordem aleatória de chegada
    printf("Embaralhando ordem de chegada dos pacotes...\n");
    embaralhar(ids, TOTAL_PACOTES);
    
    // 3. Gerar IDs duplicados para simular retransmissões
    int* ids_duplicados = (int*) malloc(NUM_RETRANSMISSOES * sizeof(int));
    if (ids_duplicados == NULL) {
        fprintf(stderr, "Erro: falha na alocação de memória\n");
        free(ids);
        return 1;
    }
    
    for (int i = 0; i < NUM_RETRANSMISSOES; i++) {
        ids_duplicados[i] = (rand() % TOTAL_PACOTES) + 1;
    }
    
    // 4. Criar árvore e simular recepção de pacotes
    printf("Iniciando recepção de pacotes...\n");
    Arvore arvore = criar_arvore();
    char buffer[256];
    int contador_retrans = 0;
    
    // Inserir pacotes originais
    for (int i = 0; i < TOTAL_PACOTES; i++) {
        gerar_conteudo_pacote(ids[i], buffer, sizeof(buffer));
        arvore = inserir_pacote(arvore, ids[i], buffer);
        
        // Progresso a cada 1000 pacotes
        if ((i + 1) % 1000 == 0) {
            printf("  Recebidos %d pacotes...\n", i + 1);
        }
    }
    
    printf("Todos os %d pacotes originais recebidos.\n\n", TOTAL_PACOTES);
    
    // Inserir retransmissões
    printf("Simulando retransmissões...\n");
    for (int i = 0; i < NUM_RETRANSMISSOES; i++) {
        gerar_conteudo_pacote(ids_duplicados[i], buffer, sizeof(buffer));
        arvore = inserir_pacote(arvore, ids_duplicados[i], buffer);
        contador_retrans++;
        
        // Log de algumas retransmissões (não todas para não poluir a saída)
        if (i < 10) {
            printf("  Retransmissão detectada: Pacote ID %d\n", ids_duplicados[i]);
        }
    }
    
    if (NUM_RETRANSMISSOES > 10) {
        printf("  ... (%d retransmissões no total)\n", NUM_RETRANSMISSOES);
    }
    
    printf("\n");
    
    // 5. Montar arquivo de saída com dados ordenados
    printf("Montando arquivo com dados ordenados...\n");
    FILE* arquivo = fopen("trabalho_2/Q2/arquivo_recebido.txt", "w");
    if (arquivo == NULL) {
        // Tentar caminho alternativo (se executado de outro diretório)
        arquivo = fopen("arquivo_recebido.txt", "w");
        if (arquivo == NULL) {
            fprintf(stderr, "Erro: não foi possível criar arquivo de saída\n");
            free(ids);
            free(ids_duplicados);
            liberar_arvore_pacotes(arvore);
            return 1;
        }
    }
    
    escrever_arquivo_ordenado(arvore, arquivo);
    fclose(arquivo);
    
    printf("Arquivo criado com sucesso!\n");
    
    // 6. Exibir estatísticas
    imprimir_estatisticas(arvore);
    
    // 7. Validação rápida
    printf("\n=== Validação ===\n");
    printf("Arquivo: arquivo_recebido.txt\n");
    printf("Verificação: execute 'wc -l arquivo_recebido.txt' para confirmar %d linhas\n", TOTAL_PACOTES);
    
    // 8. Limpeza
    free(ids);
    free(ids_duplicados);
    liberar_arvore_pacotes(arvore);
    
    printf("\n=== Simulação concluída com sucesso! ===\n");
    
    return 0;
}
