#include <stdlib.h>
#include "lista.h"

Lista* criarLista(void) {
    Lista *l = malloc(sizeof(Lista)); // Aloca memória para a lista
    l->cabeca = NULL;
    return l;
}

void inserirLista(Lista *l, int valor) {
    No *novo = malloc(sizeof(No)); // Aloca memória para o novo nó
    novo->valor = valor;
    novo->proximo = l->cabeca;
    l->cabeca = novo;
}

int buscaSequencialLista(Lista *l, int chave) {
    No *atual = l->cabeca;
    while (atual != NULL) {
        if (atual->valor == chave)
            return 1;
        atual = atual->proximo;
    }
    return -1;
}

void liberarLista(Lista *l) {
    No *atual = l->cabeca;
    while (atual != NULL) {
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(l);
}
