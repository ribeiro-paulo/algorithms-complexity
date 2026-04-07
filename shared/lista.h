#ifndef LISTA_H
#define LISTA_H

typedef struct No {
    int valor;
    struct No *proximo;
} No;

typedef struct {
    No *cabeca;
} Lista;

Lista* criarLista(void);
void inserirLista(Lista *l, int valor);
int buscaSequencialLista(Lista *l, int chave);
void liberarLista(Lista *l);

#endif
