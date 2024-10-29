#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

typedef struct No {
  int dado;
  struct No *direita;
  struct No *esquerda;
  int altura;
} *Arvore;

int max(int a, int b) {
  return (a > b) ? a : b;
}

int altura(Arvore no) {
  return (no == NULL) ? -1 : no->altura;
}

int fatorBalanceamento(Arvore no) {
  return (no == NULL) ? 0 : altura(no->esquerda) - altura(no->direita);
}

Arvore rotacaoDireita(Arvore y) {
  Arvore x = y->esquerda;
  Arvore T2 = x->direita;
  x->direita = y;
  y->esquerda = T2;
  y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
  x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
  return x;
}

Arvore rotacaoEsquerda(Arvore x) {
  Arvore y = x->direita;
  Arvore T2 = y->esquerda;
  y->esquerda = x;
  x->direita = T2;
  x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
  y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
  return y;
}

Arvore balancearNo(Arvore no) {
  int balance = fatorBalanceamento(no);
  if (balance > 1 && fatorBalanceamento(no->esquerda) >= 0) return rotacaoDireita(no);
  if (balance > 1 && fatorBalanceamento(no->esquerda) < 0) {
    no->esquerda = rotacaoEsquerda(no->esquerda);
    return rotacaoDireita(no);
  }
  if (balance < -1 && fatorBalanceamento(no->direita) <= 0) return rotacaoEsquerda(no);
  if (balance < -1 && fatorBalanceamento(no->direita) > 0) {
    no->direita = rotacaoDireita(no->direita);
    return rotacaoEsquerda(no);
  }
  return no;
}

Arvore arvoreCria() {
  return NULL;
}

Arvore arvoreInsere(Arvore arvore, const int dado) {
  if (arvore == NULL) {
    Arvore no = (Arvore)malloc(sizeof(struct No));
    if (no == NULL) return NULL;
    no->dado = dado;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 0;
    return no;
  }
  if (dado < arvore->dado) arvore->esquerda = arvoreInsere(arvore->esquerda, dado);
  else if (dado > arvore->dado) arvore->direita = arvoreInsere(arvore->direita, dado);
  else return arvore;
  arvore->altura = 1 + max(altura(arvore->esquerda), altura(arvore->direita));
  return balancearNo(arvore);
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
  arvore->altura = 1 + max(altura(arvore->esquerda), altura(arvore->direita));
  return balancearNo(arvore);
}

Arvore arvoreLibera(Arvore arvore) {
  if (arvore != NULL) {
    arvoreLibera(arvore->esquerda);
    arvoreLibera(arvore->direita);
    free(arvore);
  }
  return NULL;
}

int arvoreExibe(Arvore arvore, int espaco) {
  if (arvore == NULL) return 0;
  espaco += 10;
  arvoreExibe(arvore->direita, espaco);
  printf("\n");
  for (int i = 10; i < espaco; i++) printf(" ");
  printf("%d\n", arvore->dado);
  arvoreExibe(arvore->esquerda, espaco);
}