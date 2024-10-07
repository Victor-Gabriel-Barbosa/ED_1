#include <stdio.h>
#include <stdlib.h>
#include "fila_encadeada.h"

typedef struct node { // Estrutura do nó da fila
  int data;
  struct node *prox;
} Node;

typedef struct queue { // Estrutura da fila
  Node *inicio;
  Node *fim;
  int N;
} Fila;

/* Cria e inicializa a fila */
Fila *filaCria() {
  Fila *Ptf = (Fila*) malloc(sizeof(Fila));
  if (Ptf != NULL) {
    Ptf->inicio = NULL;
    Ptf->fim = NULL;
    Ptf->N = 0;
  }
  return Ptf;
}

/* Libera a memória alocada para uma fila */
Fila *filaLibera(Fila *Ptf) {
  if (Ptf == NULL) return Ptf;
  Node *temp = Ptf->inicio;
  while (temp!= NULL) {
    Node *proximo = temp->prox;
    free(temp);
    temp = proximo;
  }
  free(Ptf);
  return NULL;
}

/* Verifica se a fila está vazia */
int filaVazia(Fila *Ptf) {
  return (Ptf->N == 0);
}

/* Insere um elemento na fila */
Fila *filaInsere(Fila *Ptf, int elemento) {
  if (Ptf == NULL) return Ptf;
  Node *novo = (Node*) malloc(sizeof(Node));
  if (novo == NULL) return Ptf; 
  novo->data = elemento;
  novo->prox = NULL;
  if (filaVazia(Ptf)) Ptf->inicio = novo; 
  else Ptf->fim->prox = novo; 
  Ptf->fim = novo;
  Ptf->N++;
  return Ptf;
}

/* Remove um elemento da fila */
Fila *filaRemove(Fila *Ptf, int *elemento) {
  if (Ptf == NULL || filaVazia(Ptf)) return Ptf;
  Node *temp = Ptf->inicio;
  *elemento = temp->data;
  Ptf->inicio = temp->prox;
  if (Ptf->inicio == NULL) Ptf->fim = NULL;
  free(temp);
  Ptf->N--;
  return Ptf;
}

/* Consulta o primeiro elemento da fila */
int filaConsulta(Fila *Ptf, int *elemento) {
  if (Ptf == NULL || filaVazia(Ptf)) return 0;
  *elemento = Ptf->inicio->data;
  return 1;
}

/* Exibe a fila */
int filaExibe(Fila *Ptf) {
  if (filaVazia(Ptf)) return 0;
  Node *temp = Ptf->inicio;
  while (temp != NULL) {
    printf("%d ", temp->data);
    temp = temp->prox;
  }
  printf("\n");
  return 1;
}