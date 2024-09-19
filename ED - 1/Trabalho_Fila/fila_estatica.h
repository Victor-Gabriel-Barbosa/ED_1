#ifndef FILA_ESTATICA_H
#define FILA_ESTATICA_H

#include "planetas.h"

#define MAX 999999

typedef struct queue_s Fila_S;

/* Cria e inicializa a fila estática */
Fila_S *filaCria_S();

/* Libera a memória alocada p/ fila estática */
Fila_S *filaLibera_S(Fila_S *Ptf);

/* Verifica se a fila estática está vazia */
int filaVazia_S(Fila_S *Ptf);

/* Insere um elemento na fila estática */
Fila_S *filaInsere_S(Fila_S *Ptf, Planeta plan);
 
/* Remove um elemento da fila estática */
Fila_S *filaRemove_S(Fila_S *Ptf, Planeta *plan);

/* Consulta um elemento da fila estática */
int filaConsulta_S(Fila_S *Ptf, Planeta *plan);

/* Exibe a fila estática */
int filaExibe_S(Fila_S *Ptf);

/* Encontra o tamanho da fila estática */
int filaTamanho_S(Fila_S *Ptf);

#endif 