#include <stdio.h>
#include <time.h>
#include "filae.h"

void inicializaFila(FilaComandosTerraEstacao* fila) {
    fila->inicio = 0;
    fila->fim = 0;
}

void insereMensagem(FilaComandosTerraEstacao* fila, int mensagem) {
    if ((fila->fim + 1) % MAX == fila->inicio) {
        printf("Fila de comandos cheia!\n");
        return;
    }
    fila->mensagens[fila->fim] = mensagem;
    fila->fim = (fila->fim + 1) % MAX;
}

int removeMensagem(FilaComandosTerraEstacao* fila) {
    if (fila->inicio == fila->fim) {
        printf("Nenhuma mensagem na fila!\n");
        return -1;
    }
    int mensagem = fila->mensagens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX;
    return mensagem;
}

void imprimeFilaMensagens(FilaComandosTerraEstacao* fila) {
    int i = fila->inicio;
    while (i != fila->fim) {
        printf("\n %d ", fila->mensagens[i]);
        i = (i + 1) % MAX;
    }
    printf("\n");
}