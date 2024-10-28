#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pilhad.h"

void inicializaPilha(PilhaEstoqueHardware* pilha) {
    pilha->topo = NULL;
}

void insereComponente(PilhaEstoqueHardware* pilha, int numero_serie) {
    Componente* novoComponente = (Componente*)malloc(sizeof(Componente));
    novoComponente->numero_serie = numero_serie;
    novoComponente->proximo = pilha->topo;
    pilha->topo = novoComponente;
}

int removeComponente(PilhaEstoqueHardware* pilha) {
    if (pilha->topo == NULL) {
        printf("Nenhum componente no estoque!\n");
        return -1;
    }
    int numero_serie = pilha->topo->numero_serie;
    Componente* temp = pilha->topo;
    pilha->topo = pilha->topo->proximo;
    free(temp);
    return numero_serie;
}

void imprimeEstoqueHardware(PilhaEstoqueHardware* pilha) {
    Componente* atual = pilha->topo;
    while (atual != NULL) {
        printf("\n %d ", atual->numero_serie);
        atual = atual->proximo;
    }
    printf("\n");
}


