#include <stdio.h>
#include <time.h>
#include "pilhae.c"

int main() {
    PilhaEstoqueFabrica pilha;
    inicializaPilha(&pilha);

    clock_t inicio, fim;
    double tempo_decorrido;

    inicio = clock();
    for (int i = 0; i < 1000; i++) {
        insereComponenteEstoque(&pilha, i);
    }
    fim = clock();
    tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de insercao na pilha estatica: %f segundos\n", tempo_decorrido);

    inicio = clock();
    imprimeEstoqueFabrica(&pilha);
    fim = clock();
    tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de impressao na pilha estatica: %f segundos\n", tempo_decorrido);

    inicio = clock();
    for (int i = 0; i < 1000; i++) {
        removeComponenteEstoque(&pilha);
    }
    fim = clock();
    tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de remocao na pilha estatica: %f segundos\n", tempo_decorrido);

    return 0;
}
