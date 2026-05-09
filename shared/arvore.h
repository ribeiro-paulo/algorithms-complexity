#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>

/**
 * Tipo abstrato de dados para Árvore Binária de Busca.
 * A estrutura interna está oculta no arquivo de implementação.
 */
typedef struct No* Arvore;

/**
 * Cria uma árvore vazia.
 * @return NULL (árvore vazia)
 */
Arvore criar_arvore(void);

/**
 * Insere um valor na árvore binária de busca.
 * @param raiz Raiz da árvore (ou subárvore)
 * @param valor Valor a ser inserido
 * @return Ponteiro para a raiz atualizada
 */
Arvore inserir(Arvore raiz, int valor);

/**
 * Busca um valor na árvore binária de busca.
 * @param raiz Raiz da árvore (ou subárvore)
 * @param chave Valor a ser buscado
 * @return 1 se o valor foi encontrado, 0 caso contrário
 */
int buscar_arvore(Arvore raiz, int chave);

/**
 * Caminhamento pré-ordem: Raiz → Esquerda → Direita
 * @param raiz Raiz da árvore
 */
void pre_ordem(Arvore raiz);

/**
 * Caminhamento em-ordem: Esquerda → Raiz → Direita
 * (Produz saída ordenada em BST)
 * @param raiz Raiz da árvore
 */
void em_ordem(Arvore raiz);

/**
 * Caminhamento pós-ordem: Esquerda → Direita → Raiz
 * @param raiz Raiz da árvore
 */
void pos_ordem(Arvore raiz);

/**
 * Libera toda a memória alocada pela árvore.
 * @param raiz Raiz da árvore
 */
void liberar_arvore(Arvore raiz);

/**
 * Calcula a altura da árvore binária de busca.
 * @param raiz Raiz da árvore
 * @return Altura da árvore (número de níveis)
 */
int obter_altura_bst(Arvore raiz);

/* === Funções para Simulador de Pacotes === */

/**
 * Insere um pacote na árvore usando ID como chave.
 * Se o pacote já existe (ID duplicado), incrementa o contador de retransmissões.
 * @param raiz Raiz da árvore (ou subárvore)
 * @param id ID do pacote (chave BST)
 * @param dados Conteúdo do pacote
 * @return Ponteiro para a raiz atualizada
 */
Arvore inserir_pacote(Arvore raiz, int id, const char* dados);

/**
 * Escreve os dados dos pacotes em ordem crescente de ID em um arquivo.
 * Usa caminhamento em-ordem para garantir ordem correta.
 * @param raiz Raiz da árvore
 * @param arquivo Arquivo de saída já aberto
 */
void escrever_arquivo_ordenado(Arvore raiz, FILE* arquivo);

/**
 * Imprime estatísticas sobre os pacotes recebidos.
 * @param raiz Raiz da árvore
 */
void imprimir_estatisticas(Arvore raiz);

/**
 * Libera toda a memória alocada pela árvore de pacotes.
 * Libera também os dados de cada pacote.
 * @param raiz Raiz da árvore
 */
void liberar_arvore_pacotes(Arvore raiz);

/* === Funções para Árvore AVL === */

/**
 * Tipo abstrato de dados para Árvore AVL (auto-balanceada).
 * A estrutura interna está oculta no arquivo de implementação.
 */
typedef struct NoAVL* ArvoreAVL;

/**
 * Cria uma árvore AVL vazia.
 * @return NULL (árvore vazia)
 */
ArvoreAVL criar_arvore_avl(void);

/**
 * Insere um valor na árvore AVL com balanceamento automático.
 * @param raiz Raiz da árvore AVL
 * @param valor Valor a ser inserido
 * @return Ponteiro para a raiz atualizada e balanceada
 */
ArvoreAVL inserir_avl(ArvoreAVL raiz, int valor);

/**
 * Busca um valor na árvore AVL.
 * @param raiz Raiz da árvore AVL
 * @param chave Valor a ser buscado
 * @return 1 se o valor foi encontrado, 0 caso contrário
 */
int buscar_arvore_avl(ArvoreAVL raiz, int chave);

/**
 * Obtém a altura da árvore AVL.
 * @param raiz Raiz da árvore AVL
 * @return Altura da árvore (número de níveis)
 */
int obter_altura(ArvoreAVL raiz);

/**
 * Libera toda a memória alocada pela árvore AVL.
 * @param raiz Raiz da árvore AVL
 */
void liberar_arvore_avl(ArvoreAVL raiz);

#endif
