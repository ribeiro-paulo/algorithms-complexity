#include <math.h>
#include "stats.h"

double calcularMedia(double tempos[]) {
    double soma = 0;
    for (int i = 0; i < EXEC; i++)
        soma += tempos[i];
    return soma / EXEC;
}

double calcularDesvio(double tempos[], double media) {
    double soma = 0;
    for (int i = 0; i < EXEC; i++)
        soma += pow(tempos[i] - media, 2);
    return sqrt(soma / EXEC);
}
