#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No* proximo;
    struct No* anterior;
} No;

typedef struct Lista {
    No* cabeca;
} Lista;

void inicializarLista(Lista* lista) {
    lista->cabeca = NULL;
}

void adicionarNoFinal(Lista* lista, int dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->proximo = NULL;

    if (lista->cabeca == NULL) {
        novoNo->anterior = NULL;
        lista->cabeca = novoNo;
    } else {
        No* ultimo = lista->cabeca;
        while (ultimo->proximo != NULL)
            ultimo = ultimo->proximo;

        ultimo->proximo = novoNo;
        novoNo->anterior = ultimo;
    }
}

void adicionarNoInicio(Lista* lista, int dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->anterior = NULL;
    novoNo->proximo = lista->cabeca;

    if (lista->cabeca != NULL)
        lista->cabeca->anterior = novoNo;

    lista->cabeca = novoNo;
}

void removerNo(Lista* lista, int dado) {
    No* atual = lista->cabeca;

    while (atual != NULL) {
        if (atual->dado == dado) {
            if (atual->anterior != NULL)
                atual->anterior->proximo = atual->proximo;
            else
                lista->cabeca = atual->proximo;

            if (atual->proximo != NULL)
                atual->proximo->anterior = atual->anterior;

            free(atual);
            return;
        }
        atual = atual->proximo;
    }
}

void imprimirLista(Lista* lista) {
    No* no = lista->cabeca;
    while (no != NULL) {
        printf(" %d ", no->dado);
        no = no->proximo;
    }
}

int main() {
    Lista lista;
    inicializarLista(&lista);

    adicionarNoFinal(&lista, 1);
    adicionarNoFinal(&lista, 2);
    adicionarNoFinal(&lista, 3);
    adicionarNoInicio(&lista, 0);

    printf("Lista Duplamente Encadeada criada: ");
    imprimirLista(&lista);

    printf("\nRemovendo o no com dado 2...\n");
    removerNo(&lista, 2);

    printf("Lista Duplamente Encadeada atualizada: ");
    imprimirLista(&lista);

    return 0;
}