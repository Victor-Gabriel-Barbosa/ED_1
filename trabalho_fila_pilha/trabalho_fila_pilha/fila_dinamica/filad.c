#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filad.h"

void inicializaFila(FilaComunicacaoEspacial* fila) {
    fila->primeiro = NULL;
    fila->ultimo = NULL;
}

void insereComando(FilaComunicacaoEspacial* fila, int mensagem) {
    Comando* novoComando = (Comando*)malloc(sizeof(Comando));
    novoComando->mensagem = mensagem;
    novoComando->proximo = NULL;
    if (fila->ultimo != NULL) {
        fila->ultimo->proximo = novoComando;
    }
    fila->ultimo = novoComando;
    if (fila->primeiro == NULL) {
        fila->primeiro = novoComando;
    }
}

int removeComando(FilaComunicacaoEspacial* fila) {
    if (fila->primeiro == NULL) {
        printf("Nenhuma mensagem na fila de comunicacao!\n");
        return -1;
    }
    int mensagem = fila->primeiro->mensagem;
    Comando* temp = fila->primeiro;
    fila->primeiro = fila->primeiro->proximo;
    if (fila->primeiro == NULL) {
        fila->ultimo = NULL;
    }
    free(temp);
    return mensagem;
}

void imprimeFilaComunicacao(FilaComunicacaoEspacial* fila) {
    Comando* atual = fila->primeiro;
    while (atual != NULL) {
        printf("\n %d ", atual->mensagem);
        atual = atual->proximo;
    }
    printf("\n");
}