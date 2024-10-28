#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filad.c"

int main() {
    FilaComunicacaoEspacial fila;
    inicializaFila(&fila);

    clock_t inicio, fim;
    double tempo_decorrido;

    inicio = clock();
    for (int i = 0; i < 25000; i++) {
        insereComando(&fila, i);
    }
    fim = clock();
    tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de insercao na fila dinamica: %f segundos\n", tempo_decorrido);

    inicio = clock();
    imprimeFilaComunicacao(&fila);
    fim = clock();
    tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de impressao na fila dinamica: %f segundos\n", tempo_decorrido);

    inicio = clock();
    for (int i = 0; i < 25000; i++) {
        removeComando(&fila);
    }
    fim = clock();
    tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    imprimeFilaComunicacao(&fila);
    printf("Tempo de remocao na fila dinamica: %f segundos\n", tempo_decorrido);

    return 0;
}
