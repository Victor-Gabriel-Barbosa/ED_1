#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

typedef struct No {
  int dado;
  struct No *direita;
  struct No *esquerda;
} *Arvore;

Arvore arvoreCria() {
  Arvore arvore = (Arvore)malloc(sizeof(struct No));
  if (arvore == NULL) return NULL;
  return arvore;
}

Arvore arvoreInsere(Arvore arvore, const int dado) {
  if (arvore == NULL) return NULL;
  Arvore no = (Arvore)malloc(sizeof(struct No));
  if (no == NULL) return arvore;
  no->dado = dado;
  no->esquerda = NULL;
  no->direita = NULL;
  Arvore atual = arvore;
  int aux = 1;
  while (aux) {
    if (dado < atual->dado) {
      if (atual->esquerda == NULL) {
        atual->esquerda = no;
        aux = 0;
        continue;
      }
      atual = atual->esquerda;
    } else {
      if (atual->direita == NULL) {
        atual->direita = no;
        aux = 0;
        continue;
      }
      atual = atual->direita;
    }
  }
  return arvore;
}

Arvore arvoreRemove(Arvore arvore, const int dado) {
  if (arvore == NULL) return NULL;
  if (dado < arvore->dado) arvore->esquerda = arvoreRemove(arvore->esquerda, dado);
  else if (dado > arvore->dado) arvore->direita = arvoreRemove(arvore->direita, dado);
  else {
    if (arvore->esquerda == NULL && arvore->direita == NULL) {
      free(arvore);
      return NULL;
    } else if (arvore->esquerda == NULL) {
      Arvore temp = arvore;
      arvore = arvore->direita;
      free(temp);
    } else if (arvore->direita == NULL) {
      Arvore temp = arvore;
      arvore = arvore->esquerda;
      free(temp);
    } else {
      Arvore temp = arvore->direita;
      while (temp->esquerda != NULL) temp = temp->esquerda;
      arvore->dado = temp->dado;
      arvore->direita = arvoreRemove(arvore->direita, temp->dado);
    }
  }
  return arvore;
}