#ifndef FILA_ENCADEADA_H
#define FILA_ENCADEADA_H 

#include "planetas.h"
 
typedef struct queueEnc FilaEnc;
 
/* Cria e inicializa a fila encadeada */
FilaEnc *filaCriaEnc();  

/* Libera a memória alocada para uma fila */
FilaEnc *filaLiberaEnc(FilaEnc *Ptf);
 
/* Verifica se a fila encadeada está vazia */
int filaVaziaEnc(FilaEnc *Ptf);

/* Insere um elemento na fila encadeada */
FilaEnc *filaInsereEnc(FilaEnc *Ptf, Planeta plan);

/* Remove um elemento da fila encadeada */
FilaEnc *filaRemoveEnc(FilaEnc *Ptf, Planeta *plan);

/* Consulta um elemento da fila encadeada */
int filaConsultaEnc(FilaEnc *Ptf, Planeta *plan); 

/* Exibe a fila encadeada */
int filaExibeEnc(FilaEnc *Ptf);

/* Encontra o tamanho da fila encadeada */
int filaTamanhoEnc(FilaEnc *Ptf);

/* Marca o tempo para inserir planetas na fila encadeada */
long int tempoInsereFilaEnc(FilaEnc *Ptf, const int qtd_p);

/* Marca o tempo para remover planetas na fila encadeada */
long int tempoRemoveFilaEnc(FilaEnc *Ptf, const int qtd_p);

/* Marca o tempo para listar planetas na fila encadeada */
long int tempoExibeFilaEnc(FilaEnc *Ptf, const int qtd_p);

#endif 