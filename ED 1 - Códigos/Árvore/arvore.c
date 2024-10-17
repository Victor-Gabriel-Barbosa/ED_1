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