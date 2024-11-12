#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
} *Arvore;

// Função para criar uma árvore vazia
Arvore arvoreCria() {
    return NULL;
}

// Função para inserir um elemento na árvore
Arvore arvoreInsere(Arvore arv, const int valor) {
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

Arvore arvoreMaximo(Arvore arv){
    while (arv->direita != NULL) arv = arv->direita;
    return arv;
}

Arvore arvoreRemove(Arvore arv, const int valor) {
    if (arv == NULL) return NULL;
    if (valor < arv->valor) arv->esquerda = arvoreRemove(arv->esquerda, valor);
    else if (valor > arv->valor) arv->direita = arvoreRemove(arv->direita, valor);
    else {
        if (arv->esquerda == NULL) {
            Arvore temp = arv->direita;
            free(arv);
            return temp;
        } else if (arv->direita == NULL) {
            Arvore temp = arv->esquerda;
            free(arv);
            return temp;
        }
        Arvore temp = arvoreMaximo(arv->esquerda);
        arv->valor = temp->valor;
        arv->esquerda = arvoreRemove(arv->esquerda, temp->valor);
    }
    return arv;
}

// Função para buscar um elemento na árvore
Arvore arvoreBusca(Arvore arvore, const int valor) {
    Arvore atual = arvore;
    while (atual != NULL) {
        if (valor == atual->valor) return atual;
        else if (valor < atual->valor) atual = atual->esquerda;
        else atual = atual->direita;
    }
    return NULL;
}

// Percurso infixo (in-ordem) com controle de espaços
void arvorePercursoInfixo(Arvore arv, int *primeiro) {
    if (arv != NULL) {
        arvorePercursoInfixo(arv->esquerda, primeiro);

        if (!(*primeiro)) {
            printf(" ");
        }
        printf("%d", arv->valor);
        *primeiro = 0;

        arvorePercursoInfixo(arv->direita, primeiro);
    }
}

// Percurso prefixo (pré-ordem) com controle de espaços
void arvorePercursoPrefixo(Arvore arv, int *primeiro) {
    if (arv != NULL) {
        if (!(*primeiro)) {
            printf(" ");
        }
        printf("%d", arv->valor);
        *primeiro = 0;

        arvorePercursoPrefixo(arv->esquerda, primeiro);
        arvorePercursoPrefixo(arv->direita, primeiro);
    }
}

// Percurso posfixo (pós-ordem) com controle de espaços
void arvorePercursoPosfixo(Arvore arv, int *primeiro) {
    if (arv != NULL) {
        arvorePercursoPosfixo(arv->esquerda, primeiro);
        arvorePercursoPosfixo(arv->direita, primeiro);

        if (!(*primeiro)) {
            printf(" ");
        }
        printf("%d", arv->valor);
        *primeiro = 0;
    }
}

int main() {
    Arvore arv = arvoreCria();
    char comando[10];
    int valor;

    while(scanf("%s", comando) != EOF) {
        if (comando[0] == 'I' && comando[1] == '\0') {  // Inserir elemento
            scanf(" %d", &valor);
            arv = arvoreInsere(arv, valor);
        } else if (comando[0] == 'P' && comando[1] == '\0') {  // Pesquisar elemento
            scanf(" %d", &valor);
            if (arvoreBusca(arv, valor)) printf("%d existe\n", valor);
            else printf("%d nao existe\n", valor);
        } else if (strcmp(comando, "INFIXA") == 0) {  // Percurso infixo
            int primeiro = 1;
            arvorePercursoInfixo(arv, &primeiro);
            printf("\n");
        } else if (strcmp(comando, "PREFIXA") == 0) {  // Percurso prefixo
            int primeiro = 1;
            arvorePercursoPrefixo(arv, &primeiro);
            printf("\n");
        } else if (strcmp(comando, "POSFIXA") == 0) {  // Percurso posfixo
            int primeiro = 1;
            arvorePercursoPosfixo(arv, &primeiro);
            printf("\n");
        } else if (comando[0] == 'R' && comando[1] == '\0') {
            scanf(" %d", &valor);
            arv = arvoreRemove(arv, valor);
        }
    }

    return 0;
}