#include "busca.h"

int buscaSequencial(int *v, int n, int chave) {
    for (int i = 0; i < n; i++) {
        if (v[i] == chave)
            return i;
    }
    return -1;
}

int buscaBinaria(int *v, int n, int chave) {
    int ini = 0, fim = n - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;

        if (v[meio] == chave)
            return meio;
        else if (v[meio] < chave)
            ini = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}
