#ifndef FILA_ESTATICA_H
#define FILA_ESTATICA_H

#include "planetas.h"

#define MAX 999999

typedef struct queueEst FilaEst;

/* Cria e inicializa a fila estática */
FilaEst *filaCriaEst();

/* Libera a memória alocada p/ fila estática */
FilaEst *filaLiberaEst(FilaEst *Ptf);

/* Verifica se a fila estática está vazia */
int filaVaziaEst(FilaEst *Ptf);

/* Insere um elemento na fila estática */
FilaEst *filaInsereEst(FilaEst *Ptf, Planeta plan);
 
/* Remove um elemento da fila estática */
FilaEst *filaRemoveEst(FilaEst *Ptf, Planeta *plan);

/* Consulta um elemento da fila estática */
int filaConsultaEst(FilaEst *Ptf, Planeta *plan);

/* Exibe a fila estática */ 
int filaExibeEst(FilaEst *Ptf);

/* Encontra o tamanho da fila estática */
int filaTamanhoEst(FilaEst *Ptf);

#endif 