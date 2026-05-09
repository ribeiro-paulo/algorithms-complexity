#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Estrutura interna do nó da árvore (oculta do usuário).
 * Encapsula os detalhes de implementação conforme TAD.
 */
struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
    
    // Campos para simulador de pacotes
    int pacote_id;
    char* dados;
    int tentativas;
};

/**
 * Cria uma árvore vazia.
 */
Arvore criar_arvore(void) {
    return NULL;
}

/**
 * Insere um valor na árvore binária de busca (recursivo).
 * Regras BST:
 *   - Valores menores vão para a esquerda
 *   - Valores maiores ou iguais vão para a direita
 */
Arvore inserir(Arvore raiz, int valor) {
    // Caso base: posição encontrada para inserção
    if (raiz == NULL) {
        struct No* novo = (struct No*) malloc(sizeof(struct No));
        if (novo == NULL) {
            fprintf(stderr, "Erro: falha na alocação de memória\n");
            exit(1);
        }
        novo->valor = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    
    // Recursão: navega pela árvore
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else {
        raiz->direita = inserir(raiz->direita, valor);
    }
    
    return raiz;
}

/**
 * Busca um valor na árvore binária de busca (recursivo).
 * Regras BST:
 *   - Se o valor procurado é menor, busca na subárvore esquerda
 *   - Se o valor procurado é maior, busca na subárvore direita
 *   - Se igual, valor encontrado
 */
int buscar_arvore(Arvore raiz, int chave) {
    // Caso base: árvore vazia ou valor não encontrado
    if (raiz == NULL) {
        return 0;
    }
    
    // Valor encontrado
    if (raiz->valor == chave) {
        return 1;
    }
    
    // Recursão: navega pela árvore
    if (chave < raiz->valor) {
        return buscar_arvore(raiz->esquerda, chave);
    } else {
        return buscar_arvore(raiz->direita, chave);
    }
}

/**
 * Caminhamento pré-ordem: Raiz → Esquerda → Direita
 */
void pre_ordem(Arvore raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        pre_ordem(raiz->esquerda);
        pre_ordem(raiz->direita);
    }
}

/**
 * Caminhamento em-ordem: Esquerda → Raiz → Direita
 * Em uma BST, este caminhamento produz os valores em ordem crescente.
 */
void em_ordem(Arvore raiz) {
    if (raiz != NULL) {
        em_ordem(raiz->esquerda);
        printf("%d ", raiz->valor);
        em_ordem(raiz->direita);
    }
}

/**
 * Caminhamento pós-ordem: Esquerda → Direita → Raiz
 */
void pos_ordem(Arvore raiz) {
    if (raiz != NULL) {
        pos_ordem(raiz->esquerda);
        pos_ordem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

/**
 * Libera toda a memória alocada pela árvore (recursivo).
 * Usa pós-ordem para garantir que os filhos sejam liberados antes do pai.
 */
void liberar_arvore(Arvore raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esquerda);
        liberar_arvore(raiz->direita);
        free(raiz);
    }
}

/**
 * Função auxiliar para calcular o máximo entre dois inteiros (BST).
 */
static int max_bst(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * Calcula a altura da árvore binária de busca (recursivo).
 * Altura = número máximo de arestas da raiz até uma folha.
 */
int obter_altura_bst(Arvore raiz) {
    if (raiz == NULL) {
        return 0;
    }
    
    int altura_esq = obter_altura_bst(raiz->esquerda);
    int altura_dir = obter_altura_bst(raiz->direita);
    
    return 1 + max_bst(altura_esq, altura_dir);
}

/* === Implementação das Funções para Simulador de Pacotes === */

/**
 * Insere um pacote na árvore usando ID como chave.
 * Se o pacote já existe (ID duplicado), incrementa o contador de retransmissões.
 */
Arvore inserir_pacote(Arvore raiz, int id, const char* dados) {
    // Caso base: posição encontrada para inserção
    if (raiz == NULL) {
        struct No* novo = (struct No*) malloc(sizeof(struct No));
        if (novo == NULL) {
            fprintf(stderr, "Erro: falha na alocação de memória\n");
            exit(1);
        }
        novo->pacote_id = id;
        novo->dados = (char*) malloc(strlen(dados) + 1);
        if (novo->dados == NULL) {
            fprintf(stderr, "Erro: falha na alocação de memória para dados\n");
            free(novo);
            exit(1);
        }
        strcpy(novo->dados, dados);
        novo->tentativas = 1;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->valor = 0;  // Não usado no contexto de pacotes
        return novo;
    }
    
    // Pacote duplicado: incrementa contador de tentativas
    if (id == raiz->pacote_id) {
        raiz->tentativas++;
        return raiz;
    }
    
    // Recursão: navega pela árvore
    if (id < raiz->pacote_id) {
        raiz->esquerda = inserir_pacote(raiz->esquerda, id, dados);
    } else {
        raiz->direita = inserir_pacote(raiz->direita, id, dados);
    }
    
    return raiz;
}

/**
 * Escreve os dados dos pacotes em ordem crescente de ID em um arquivo.
 * Usa caminhamento em-ordem para garantir ordem correta.
 */
void escrever_arquivo_ordenado(Arvore raiz, FILE* arquivo) {
    if (raiz != NULL) {
        escrever_arquivo_ordenado(raiz->esquerda, arquivo);
        if (raiz->dados != NULL) {
            fprintf(arquivo, "%s\n", raiz->dados);
        }
        escrever_arquivo_ordenado(raiz->direita, arquivo);
    }
}

/**
 * Função auxiliar para contar pacotes únicos.
 */
static int contar_pacotes(Arvore raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contar_pacotes(raiz->esquerda) + contar_pacotes(raiz->direita);
}

/**
 * Função auxiliar para contar total de retransmissões.
 */
static int contar_retransmissoes(Arvore raiz) {
    if (raiz == NULL) {
        return 0;
    }
    // Retransmissões = tentativas - 1 (primeira transmissão não é retransmissão)
    int retrans_no = (raiz->tentativas > 1) ? (raiz->tentativas - 1) : 0;
    return retrans_no + contar_retransmissoes(raiz->esquerda) + contar_retransmissoes(raiz->direita);
}

/**
 * Função auxiliar para encontrar pacote com mais retransmissões.
 */
static void encontrar_max_retransmissoes(Arvore raiz, int* max_tentativas, int* pacote_id_max) {
    if (raiz == NULL) {
        return;
    }
    
    if (raiz->tentativas > *max_tentativas) {
        *max_tentativas = raiz->tentativas;
        *pacote_id_max = raiz->pacote_id;
    }
    
    encontrar_max_retransmissoes(raiz->esquerda, max_tentativas, pacote_id_max);
    encontrar_max_retransmissoes(raiz->direita, max_tentativas, pacote_id_max);
}

/**
 * Imprime estatísticas sobre os pacotes recebidos.
 */
void imprimir_estatisticas(Arvore raiz) {
    int total_pacotes = contar_pacotes(raiz);
    int total_retrans = contar_retransmissoes(raiz);
    int max_tentativas = 0;
    int pacote_id_max = 0;
    
    encontrar_max_retransmissoes(raiz, &max_tentativas, &pacote_id_max);
    
    printf("\n=== Estatísticas de Transmissão ===\n");
    printf("Total de pacotes únicos: %d\n", total_pacotes);
    printf("Total de retransmissões detectadas: %d\n", total_retrans);
    if (max_tentativas > 1) {
        printf("Pacote com mais retransmissões: ID %d (%d tentativas, %d retransmissões)\n",
               pacote_id_max, max_tentativas, max_tentativas - 1);
    }
    printf("====================================\n");
}

/**
 * Libera toda a memória alocada pela árvore de pacotes.
 * Libera também os dados de cada pacote.
 */
void liberar_arvore_pacotes(Arvore raiz) {
    if (raiz != NULL) {
        liberar_arvore_pacotes(raiz->esquerda);
        liberar_arvore_pacotes(raiz->direita);
        if (raiz->dados != NULL) {
            free(raiz->dados);
        }
        free(raiz);
    }
}

/* === Implementação da Árvore AVL === */

/**
 * Estrutura interna do nó da árvore AVL (oculta do usuário).
 * Inclui campo de altura para balanceamento eficiente.
 */
struct NoAVL {
    int valor;
    int altura;
    struct NoAVL* esquerda;
    struct NoAVL* direita;
};

/**
 * Retorna a altura de um nó (0 para nó NULL).
 */
static int obter_altura_no(struct NoAVL* no) {
    return (no == NULL) ? 0 : no->altura;
}

/**
 * Retorna o máximo entre dois inteiros.
 */
static int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * Atualiza a altura de um nó baseado nas alturas dos filhos.
 */
static void atualizar_altura(struct NoAVL* no) {
    if (no != NULL) {
        no->altura = 1 + max(obter_altura_no(no->esquerda), obter_altura_no(no->direita));
    }
}

/**
 * Calcula o fator de balanceamento de um nó.
 * FB = altura(esquerda) - altura(direita)
 * FB > 1: desbalanceado à esquerda
 * FB < -1: desbalanceado à direita
 */
static int obter_fator_balanceamento(struct NoAVL* no) {
    return (no == NULL) ? 0 : obter_altura_no(no->esquerda) - obter_altura_no(no->direita);
}

/**
 * Rotação simples à direita.
 *       y                    x
 *      / \                  / \
 *     x   T3    -->        T1  y
 *    / \                      / \
 *   T1  T2                   T2  T3
 */
static struct NoAVL* rotacao_direita(struct NoAVL* y) {
    struct NoAVL* x = y->esquerda;
    struct NoAVL* T2 = x->direita;
    
    // Executa rotação
    x->direita = y;
    y->esquerda = T2;
    
    // Atualiza alturas
    atualizar_altura(y);
    atualizar_altura(x);
    
    return x;  // Nova raiz
}

/**
 * Rotação simples à esquerda.
 *     x                        y
 *    / \                      / \
 *   T1  y        -->         x   T3
 *      / \                  / \
 *     T2  T3               T1  T2
 */
static struct NoAVL* rotacao_esquerda(struct NoAVL* x) {
    struct NoAVL* y = x->direita;
    struct NoAVL* T2 = y->esquerda;
    
    // Executa rotação
    y->esquerda = x;
    x->direita = T2;
    
    // Atualiza alturas
    atualizar_altura(x);
    atualizar_altura(y);
    
    return y;  // Nova raiz
}

/**
 * Cria uma árvore AVL vazia.
 */
ArvoreAVL criar_arvore_avl(void) {
    return NULL;
}

/**
 * Insere um valor na árvore AVL com balanceamento automático.
 */
ArvoreAVL inserir_avl(ArvoreAVL raiz, int valor) {
    // 1. Inserção BST padrão
    if (raiz == NULL) {
        struct NoAVL* novo = (struct NoAVL*) malloc(sizeof(struct NoAVL));
        if (novo == NULL) {
            fprintf(stderr, "Erro: falha na alocação de memória\n");
            exit(1);
        }
        novo->valor = valor;
        novo->altura = 1;  // Nó folha tem altura 1
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    
    if (valor < raiz->valor) {
        raiz->esquerda = inserir_avl(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir_avl(raiz->direita, valor);
    } else {
        // Valor duplicado: não insere
        return raiz;
    }
    
    // 2. Atualiza altura do nó atual
    atualizar_altura(raiz);
    
    // 3. Verifica balanceamento e executa rotações se necessário
    int fb = obter_fator_balanceamento(raiz);
    
    // Caso Esquerda-Esquerda (LL)
    if (fb > 1 && valor < raiz->esquerda->valor) {
        return rotacao_direita(raiz);
    }
    
    // Caso Direita-Direita (RR)
    if (fb < -1 && valor > raiz->direita->valor) {
        return rotacao_esquerda(raiz);
    }
    
    // Caso Esquerda-Direita (LR)
    if (fb > 1 && valor > raiz->esquerda->valor) {
        raiz->esquerda = rotacao_esquerda(raiz->esquerda);
        return rotacao_direita(raiz);
    }
    
    // Caso Direita-Esquerda (RL)
    if (fb < -1 && valor < raiz->direita->valor) {
        raiz->direita = rotacao_direita(raiz->direita);
        return rotacao_esquerda(raiz);
    }
    
    return raiz;
}

/**
 * Busca um valor na árvore AVL (idêntico à busca em BST).
 */
int buscar_arvore_avl(ArvoreAVL raiz, int chave) {
    if (raiz == NULL) {
        return 0;
    }
    
    if (raiz->valor == chave) {
        return 1;
    }
    
    if (chave < raiz->valor) {
        return buscar_arvore_avl(raiz->esquerda, chave);
    } else {
        return buscar_arvore_avl(raiz->direita, chave);
    }
}

/**
 * Obtém a altura da árvore AVL.
 */
int obter_altura(ArvoreAVL raiz) {
    return obter_altura_no(raiz);
}

/**
 * Libera toda a memória alocada pela árvore AVL.
 */
void liberar_arvore_avl(ArvoreAVL raiz) {
    if (raiz != NULL) {
        liberar_arvore_avl(raiz->esquerda);
        liberar_arvore_avl(raiz->direita);
        free(raiz);
    }
}

