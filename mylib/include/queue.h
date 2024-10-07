#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

/**
 * @brief Estrutura para representar uma fila
 */
typedef struct queue *Queue;
 
/** 
 * @brief Cria uma nova fila vazia. 
 * 
 * @return Um ponteiro para uma nova fila.
 */
Queue newQueue();

/** 
 * @brief  Libera a memória alocada para a fila.
 * 
 * @param qeu Ponteiro para a fila a ser liberada.
 * @return Um ponteiro nulo após a liberação da fila.
 */
Queue destroyQueue(Queue qeu);

/** 
 * @brief Verifica se a fila está vazia.
 * 
 * @param qeu Ponteiro para a fila.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int isEmptyQueue(Queue qeu);

/** 
 * @brief Obtém o tamanho da fila.
 * 
 * @param qeu Ponteiro para a fila.
 * @return O tamanho da fila.
 */
size_t sizeQueue(Queue qeu);

/** 
 * @brief Insere um novo elemento no início da fila.
 * 
 * @param qeu Ponteiro para a fila.
 * @param info Os dados a serem inseridos na fila.
 * @return Um ponteiro para a fila atualizada.
 */
Queue enqueue(Queue qeu, const int info);

/** 
 * @brief Remove um elemento da fila.
 * 
 * @param qeu Ponteiro para a fila.
 * @param info Ponteiro para um elemento da fila.
 * @return Um ponteiro para a fila atualizada.
 */
Queue dequeue(Queue qeu, int *info);

/** 
 * @brief Busca por um elemento da fila.
 * 
 * @param qeu Ponteiro para a fila.
 * @param posi A posição do elemento a ser buscado.
 * @param info Ponteiro para armazenar os dados encontrados.
 * @return 1 se o elemento for encontrado, 0 caso contrário.
 */
int front(Queue qeu, int *info); 

/** 
 * @brief Imprime a fila.
 * 
 * @param qeu Ponteiro para a fila.
 * @return 1 se a impressão for bem-sucedida, 0 caso contrário.
 */
int printQueue(Queue qeu); 
                                             
#endif
