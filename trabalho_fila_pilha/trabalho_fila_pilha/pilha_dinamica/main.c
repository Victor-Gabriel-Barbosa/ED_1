#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pilhad.c"

int main() {
    PilhaEstoqueHardware pilha;
    inicializaPilha(&pilha);

    clock_t inicio, fim;
    double tempo_decorrido;

    inicio = clock();
    for (int i = 0; i < 1000; i++) {
        insereComponente(&pilha, i);
    }
    fim = clock();
    tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de insercao na pilha dinamica: %f segundos\n", tempo_decorrido);

    inicio = clock();
    imprimeEstoqueHardware(&pilha);
    fim = clock();
    tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de impressao na pilha dinamica: %f segundos\n", tempo_decorrido);

    inicio = clock();
    for (int i = 0; i < 1000; i++) {
        removeComponente(&pilha);
    }
    fim = clock();
    tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de remocao na pilha dinamica: %f segundos\n", tempo_decorrido);

    return 0;
}
