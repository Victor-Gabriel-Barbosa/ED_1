#include <stdio.h>
#include <time.h>
#include "filae.c"

int main() {
    FilaComandosTerraEstacao fila;
    inicializaFila(&fila);

    clock_t inicio, fim;
    double tempo_decorrido;

    inicio = clock();
    for (int i = 0; i < 1000; i++) {
        insereMensagem(&fila, i);
    }
    fim = clock();
    tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de insercao na fila estatica: %f segundos\n", tempo_decorrido);

    inicio = clock();
    imprimeFilaMensagens(&fila);
    fim = clock();
    tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de impressao na fila estatica: %f segundos\n", tempo_decorrido);

    inicio = clock();
    for (int i = 0; i < 1000; i++) {
        removeMensagem(&fila);
    }
    fim = clock();
    tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de remocao na fila estatica: %f segundos\n", tempo_decorrido);

    return 0;
}
