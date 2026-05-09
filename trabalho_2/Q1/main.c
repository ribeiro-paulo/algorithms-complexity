#include <stdio.h>
#include "../../shared/arvore.h"

int main(void) {
    // Dados de teste (20 elementos)
    int valores[] = {50, 30, 70, 20, 40, 60, 80,
                     10, 25, 35, 45, 55, 65, 75, 85,
                     5, 15, 27, 33, 48};
    int n = sizeof(valores) / sizeof(valores[0]);
    
    // Cria a árvore vazia
    Arvore arvore = criar_arvore();
    
    // Insere todos os valores
    printf("=== Inserindo %d elementos na BST ===\n\n", n);
    for (int i = 0; i < n; i++) {
        arvore = inserir(arvore, valores[i]);
    }
    
    // Caminhamento em-ordem (saída ordenada)
    printf("Em-ordem (ordenado):\n");
    em_ordem(arvore);
    printf("\n\n");
    
    // Caminhamento pré-ordem
    printf("Pré-ordem:\n");
    pre_ordem(arvore);
    printf("\n\n");
    
    // Caminhamento pós-ordem
    printf("Pós-ordem:\n");
    pos_ordem(arvore);
    printf("\n\n");
    
    // Libera a memória
    liberar_arvore(arvore);
    printf("=== Memória liberada com sucesso ===\n");
    
    return 0;
}
