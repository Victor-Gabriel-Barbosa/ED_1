#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
  int valor;
  struct No* esquerda;
  struct No* direita;
} *Arvore;

Arvore arvoreCria() {
  return NULL;
}

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

void arvorePercursoPorNivel(Arvore arv) {
  if (arv == NULL) return;
  Arvore fila[500];
  int inicio = 0, fim = 0;
  fila[fim++] = arv;
  int primeiro = 1;
  while (inicio < fim) {
    Arvore atual = fila[inicio++];
    if (!primeiro) printf(" ");
    printf("%d", atual->valor);
    primeiro = 0;
    if (atual->esquerda) fila[fim++] = atual->esquerda;
    if (atual->direita) fila[fim++] = atual->direita;
  }
}

void arvoreLibera(Arvore arv) {
  if (arv != NULL) {
    arvoreLibera(arv->esquerda);
    arvoreLibera(arv->direita);
    free(arv);
  }
}

int main() {
  int C;
  scanf("%d", &C); 
  for (int i = 1; i <= C; i++) {
    int N;
    scanf("%d", &N); 
    Arvore arv = arvoreCria();
    for (int j = 0; j < N; j++) {
      int valor;
      scanf("%d", &valor);
      arv = arvoreInsere(arv, valor);
    }
    printf("Case %d:\n", i);
    arvorePercursoPorNivel(arv);
    printf("\n\n");
    arvoreLibera(arv);
  }
  return 0;
}
