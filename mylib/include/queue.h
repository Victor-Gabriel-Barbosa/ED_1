#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

// Estrutura para representar uma fila
typedef struct queue *Queue;
 
/** 
 * Cria uma nova fila vazia. 
 * 
 * @return Um ponteiro para uma nova fila.
 */
Queue newQueue();

/** 
 * Libera a memória alocada para a fila.
 * 
 * @param Queue Ponteiro para a fila a ser liberada.
 * @return Um ponteiro nulo após a liberação da fila.
 */
Queue destroyQueue(Queue Queue);

/** 
 * Verifica se a fila está vazia.
 * 
 * @param Ptq Ponteiro para a fila.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int isEmptyQueue(Queue Ptq);

/** 
 * Obtém o tamanho da fila.
 * 
 * @param Ptq Ponteiro para a fila.
 * @return O tamanho da fila.
 */
size_t sizeQueue(Queue Ptq);

/** 
 * Insere um novo elemento no início da fila.
 * 
 * @param Ptq Ponteiro para a fila.
 * @param info Os dados a serem inseridos na fila.
 * @return Um ponteiro para a fila atualizada.
 */
Queue enqueue(Queue Ptq, const int info);

/** 
 * Remove um elemento da fila.
 * 
 * @param Ptq Ponteiro para a fila.
 * @param info Ponteiro para um elemento da fila.
 * @return Um ponteiro para a fila atualizada.
 */
Queue dequeue(Queue Ptq, int *info);

/** 
 * Busca por um elemento da fila.
 * 
 * @param Ptq Ponteiro para a fila.
 * @param posi A posição do elemento a ser buscado.
 * @param info Ponteiro para armazenar os dados encontrados.
 * @return 1 se o elemento for encontrado, 0 caso contrário.
 */
int peek(Queue Ptq, int *info); 

/** 
 * Imprime a fila.
 * 
 * @param Ptq Ponteiro para a fila.
 * @return 1 se a impressão for bem-sucedida, 0 caso contrário.
 */
int showQueue(Queue Ptq); 
                                             
#endif
