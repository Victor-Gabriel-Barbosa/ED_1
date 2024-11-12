#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char valor;
    struct No* esquerda;
    struct No* direita;
} *Arvore;

Arvore arvoreCria() {
    return NULL;
}

Arvore arvoreInsere(Arvore arv, const char valor) {
    Arvore no = (Arvore)malloc(sizeof(struct No));
    if (no == NULL) return arv;
    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;

    if (arv == NULL) return no;
    Arvore atual = arv;
    Arvore pai = NULL;
    while (atual != NULL) {
        pai = atual;
        if (valor < atual->valor) atual = atual->esquerda;
        else atual = atual->direita;
    }
    if (valor < pai->valor) pai->esquerda = no;
    else pai->direita = no;
    return arv;
}

Arvore arvoreBusca(Arvore arvore, const char valor) {
    Arvore atual = arvore;
    while (atual != NULL) {
        if (valor == atual->valor) return atual;
        else if (valor < atual->valor) atual = atual->esquerda;
        else atual = atual->direita;
    }
    return NULL;
}

void arvorePercursoInfixo(Arvore arv, int *prim) {
    if (arv != NULL) {
        arvorePercursoInfixo(arv->esquerda, prim);
        if (!(*prim)) printf(" ");
        printf("%c", arv->valor);
        *prim = 0;
        arvorePercursoInfixo(arv->direita, prim);
    }
}


void arvorePercursoPrefixo(Arvore arv, int *prim) {
    if (arv != NULL) {
        if (!(*prim)) printf(" ");
        printf("%c", arv->valor);
        *prim = 0;
        arvorePercursoPrefixo(arv->esquerda, prim);
        arvorePercursoPrefixo(arv->direita, prim);
    }
}

void arvorePercursoPosfixo(Arvore arv, int *prim) {
    if (arv != NULL) {
        arvorePercursoPosfixo(arv->esquerda, prim);
        arvorePercursoPosfixo(arv->direita, prim);
        if (!(*prim)) printf(" ");
        printf("%c", arv->valor);
        *prim = 0;
    }
}

int main() {
    Arvore arv = arvoreCria();
    char comando[10];
    char valor;

    while(scanf("%s", comando) != EOF) {
        if (comando[0] == 'I' && comando[1] == '\0') {
            scanf(" %c", &valor);
            arv = arvoreInsere(arv, valor);
        } else if (comando[0] == 'P' && comando[1] == '\0') {
            scanf(" %c", &valor);
            if (arvoreBusca(arv, valor)) printf("%c existe\n", valor);
            else printf("%c nao existe\n", valor);
        } else if (strcmp(comando, "INFIXA") == 0) {
            int prim = 1;
            arvorePercursoInfixo(arv, &prim);
            printf("\n");
        } else if (strcmp(comando, "PREFIXA") == 0) {
            int prim = 1;
            arvorePercursoPrefixo(arv, &prim);
            printf("\n");
        } else if (strcmp(comando, "POSFIXA") == 0) {
            int prim = 1;
            arvorePercursoPosfixo(arv, &prim);
            printf("\n");
        }
    }

    return 0;
}