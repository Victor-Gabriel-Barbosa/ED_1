#ifndef FILA_ENCADEADA_H
#define FILA_ENCADEADA_H 

#include "planetas.h"

typedef struct queue_e Fila_E;

/* Cria e inicializa a fila encadeada */
Fila_E *filaCria_E();

/* Libera a memória alocada para uma fila */
Fila_E *filaLibera_E(Fila_E *Ptf);

/* Verifica se a fila encadeada está vazia */
int filaVazia_E(Fila_E *Ptf);

/* Insere um elemento na fila encadeada */
Fila_E *filaInsere_E(Fila_E *Ptf, Planeta plan);

/* Remove um elemento da fila encadeada */
Fila_E *filaRemove_E(Fila_E *Ptf, Planeta *plan);

/* Consulta um elemento da fila encadeada */
int filaConsulta_E(Fila_E *Ptf, Planeta *plan);

/* Exibe a fila encadeada */
int filaExibe_E(Fila_E *Ptf);

/* Encontra o tamanho da fila encadeada */
int filaTamanho_E(Fila_E *Ptf);

#endif 