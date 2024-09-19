#ifndef FILA_ENCADEADA_H
#define FILA_ENCADEADA_H

typedef struct queue Fila;

/* Cria e inicializa a fila */
Fila *filaCria();

/* Libera a memória alocada para uma fila */
Fila *filaLibera(Fila *Ptf);

/* Verifica se a fila está vazia */
int filaVazia(Fila *Ptf);

/* Insere um elemento na fila */
Fila *filaInsere(Fila *Ptf, int elemento);

/* Remove um elemento da fila */
Fila *filaRemove(Fila *Ptf, int *elemento);

/* Consulta um elemento da fila */
int filaConsulta(Fila *Ptf, int *elemento);

/* Exibe a fila */
int filaExibe(Fila *Ptf);

#endif 