#ifndef FILA_ESTATICA_H
#define FILA_ESTATICA_H

#define MAX 10  // Tamanho máximo da fila

typedef struct queue Fila;

/* Cria e inicializa a fila */
Fila *filaCria();

/* Libera a memória alocada p/ fila estática */
Fila *filaLibera(Fila *Ptf);

/* Verifica se a fila está cheia */
int filaCheia(Fila *Ptf);

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

/* Insere o maior elemento entre duas filas */
Fila *filaInsereMaior(Fila *Ptf1, Fila *Ptf2);

#endif