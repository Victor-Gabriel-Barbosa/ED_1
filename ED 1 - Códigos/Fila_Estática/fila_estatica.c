#include <stdio.h>
#include <stdlib.h>
#include "fila_estatica.h"

typedef struct queue { // Estrutura p/ armazenar a fila
  int fila[MAX];
  int IF;
  int FF;
  int N;
} Fila;

/* Cria e inicializa a fila */
Fila *filaCria() {
  Fila *Ptf = (Fila*) malloc(sizeof(Fila));
  if (Ptf != NULL) {
    Ptf->IF = 0;
    Ptf->FF = 0;
    Ptf->N = 0;
  }
  return Ptf;
}

/* Libera a memória alocada p/ fila estática */
Fila *filaLibera(Fila *Ptf) {
  if (Ptf == NULL) return Ptf;
  free(Ptf);
  return NULL;
}

/* Verifica se a fila está cheia */
int filaCheia(Fila *Ptf) {
  return (Ptf->N == MAX);
}

/* Verifica se a fila está vazia */
int filaVazia(Fila *Ptf) {
  return (Ptf->N == 0);
}

/* Insere um elemento na fila */
Fila *filaInsere(Fila *Ptf, int elemento) {
  if (Ptf == NULL || filaCheia(Ptf)) return Ptf;
  Ptf->fila[Ptf->FF] = elemento;
  Ptf->FF = (Ptf->FF + 1) % MAX;
  Ptf->N++;
  return Ptf;
}

/* Remove um elemento da fila */
Fila *filaRemove(Fila *Ptf, int *elemento) {
  if (Ptf == NULL || filaVazia(Ptf)) return Ptf;
  *elemento = Ptf->fila[Ptf->IF];
  Ptf->IF = (Ptf->IF + 1) % MAX;
  Ptf->N--;
  return Ptf;
}

/* Consulta um elemento da fila */
int filaConsulta(Fila *Ptf, int *elemento) {
  if (Ptf == NULL || filaVazia(Ptf)) return 0;
  *elemento = Ptf->fila[Ptf->IF];
  return 1;
}

/* Exibe a fila */
int filaExibe(Fila *Ptf) {
  if (filaVazia(Ptf)) return 0;
  for (int i = 0; i < Ptf->N; i++) {  // Percorre todos os elementos presentes na fila
    printf("%d ", Ptf->fila[(Ptf->IF + i) % MAX]); 
  }
  printf("\n");
  return 1;
}

/* Insere o maior elemento entre duas filas */
Fila *filaInsereMaior(Fila *Ptf1, Fila *Ptf2) {
  Fila *Ptf_final = filaCria();
  int elem1, elem2;
  while (!filaVazia(Ptf1) && !filaVazia(Ptf2)) { // Percorre as filas enquanto ambas não forem vazias
    filaConsulta(Ptf1, &elem1);
    filaConsulta(Ptf2, &elem2);
    if (elem1 > elem2) { // Verifica qual elemento é maior
      filaRemove(Ptf1, &elem1);
      filaInsere(Ptf_final, elem1);
    } else {
      filaRemove(Ptf2, &elem2);
      filaInsere(Ptf_final, elem2);
    }
  } 
  while (!filaVazia(Ptf1)) { // Insere os elementos restantes da fila 1
   filaRemove(Ptf1, &elem1);
   filaInsere(Ptf_final, elem1);
  }
  while (!filaVazia(Ptf2)) { // Insere os elementos restantes da fila 2
   filaRemove(Ptf2, &elem2);
   filaInsere(Ptf_final, elem2);
  }
  return Ptf_final;
}