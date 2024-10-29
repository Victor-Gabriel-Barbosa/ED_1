#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

typedef struct No {
  int dado;
  struct No *direita;
  struct No *esquerda;
} *Arvore;

Arvore arvoreCria() {
  return NULL;
}

Arvore arvoreLibera(Arvore arvore) {
  if (arvore != NULL) {
    arvoreLibera(arvore->esquerda);
    arvoreLibera(arvore->direita);
    free(arvore);
  }
  return NULL;
}

Arvore arvoreInsere(Arvore arvore, const int dado) {
  if (arvore == NULL) {
    Arvore no = (Arvore)malloc(sizeof(struct No));
    if (no == NULL) return NULL;
    no->dado = dado;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
  }
  Arvore atual = arvore;
  while (1) {
    if (dado < atual->dado) {
      if (atual->esquerda == NULL) {
        Arvore no = (Arvore)malloc(sizeof(struct No));
        if (no == NULL) return arvore;
        no->dado = dado;
        no->esquerda = NULL;
        no->direita = NULL;
        atual->esquerda = no;
        break;
      }
      atual = atual->esquerda;
    } else {
      if (atual->direita == NULL) {
        Arvore no = (Arvore)malloc(sizeof(struct No));
        if (no == NULL) return arvore;
        no->dado = dado;
        no->esquerda = NULL;
        no->direita = NULL;
        atual->direita = no;
        break;
      }
      atual = atual->direita;
    }
  }
  return arvore;
}

Arvore encontraMinimo(Arvore arvore) {
  while (arvore != NULL && arvore->esquerda != NULL) arvore = arvore->esquerda;
  return arvore;
}

Arvore arvoreRemove(Arvore arvore, const int dado) {
  if (arvore == NULL) return NULL;
  if (dado < arvore->dado) arvore->esquerda = arvoreRemove(arvore->esquerda, dado);
  else if (dado > arvore->dado) arvore->direita = arvoreRemove(arvore->direita, dado);
  else {
    if (arvore->esquerda == NULL) {
      Arvore temp = arvore->direita;
      free(arvore);
      return temp;
    } else if (arvore->direita == NULL) {
      Arvore temp = arvore->esquerda;
      free(arvore);
      return temp;
    } else {
      Arvore temp = encontraMinimo(arvore->direita);
      arvore->dado = temp->dado;
      arvore->direita = arvoreRemove(arvore->direita, temp->dado);
    }
  }
  return arvore;
}