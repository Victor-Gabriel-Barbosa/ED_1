#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "queue.h"

/**
 * @brief Estrutura do nó da fila.
 * 
 * Cada nó contém um valor `info` e um ponteiro para o próximo nó da fila.
 */
typedef struct nodeQ { 
  int info;
  struct nodeQ *prox;
} NodeQ;
 
/**
 * @brief Estrutura da fila (Queue).
 * 
 * A fila contém um ponteiro para o início (`inicio`), o fim (`fim`), 
 * e um contador de elementos (`N`).
 */
typedef struct queue { 
  NodeQ *head;
  NodeQ *tail;
  int N;
} *Queue;

/**
 * @brief Cria uma nova fila vazia.
 * 
 * Aloca memória para uma nova fila, inicializando os ponteiros de início e fim como `NULL`
 * e o contador de elementos como zero.
 * 
 * @return Queue Um ponteiro para a nova fila criada.
 */
Queue newQueue() {
  Queue qeu = (Queue)malloc(sizeof(struct queue));
  if (qeu != NULL) {
    qeu->head = NULL;
    qeu->tail = NULL;
    qeu->N = 0;
  }
  return qeu;
}

/**
 * @brief Destrói a fila e libera a memória associada.
 * 
 * Remove todos os nós da fila e libera a memória alocada para a estrutura da fila.
 * 
 * @param qeu Um ponteiro para a fila a ser destruída.
 * @return Queue Retorna `NULL` após liberar a memória.
 */
Queue destroyQueue(Queue qeu) {
  if (qeu == NULL) return qeu;
  NodeQ *temp = qeu->head;
  while (temp != NULL) {
    NodeQ *proximo = temp->prox;
    free(temp);
    temp = proximo;
  }
  free(qeu);
  return NULL; 
}

/**
 * @brief Verifica se a fila está vazia.
 * 
 * @param qeu Um ponteiro para a fila a ser verificada.
 * @return int Retorna 1 se a fila estiver vazia, ou 0 caso contrário.
 */
int isEmptyQueue(Queue qeu) {
  return (qeu == NULL || qeu->head == NULL);
}

/**
 * @brief Retorna o número de elementos na fila.
 * 
 * @param qeu Um ponteiro para a fila.
 * @return size_t O número de elementos na fila.
 */
size_t sizeQueue(Queue qeu) {
  if (qeu == NULL) return 0;
  return qeu->N;
}

/**
 * @brief Insere um novo elemento na fila.
 * 
 * Aloca um novo nó contendo o valor passado e o insere no fim da fila.
 * 
 * @param qeu Um ponteiro para a fila onde o elemento será inserido.
 * @param info O valor a ser inserido na fila.
 * @return Queue Retorna a fila após a inserção do novo elemento.
 */
Queue enqueue(Queue qeu, int info) {
  if (qeu == NULL) return qeu;
  NodeQ *novo = (NodeQ*) malloc(sizeof(NodeQ));
  if (novo == NULL) return qeu; 
  novo->info = info;
  novo->prox = NULL;
  if (isEmptyQueue(qeu)) qeu->head = novo; 
  else qeu->tail->prox = novo; 
  qeu->tail = novo;
  qeu->N++;
  return qeu;
} 

/**
 * @brief Remove o primeiro elemento da fila.
 * 
 * Remove o nó que está no início da fila e retorna o valor removido através de um ponteiro.
 * 
 * @param qeu Um ponteiro para a fila de onde o elemento será removido.
 * @param info Um ponteiro para onde o valor removido será armazenado.
 * @return Queue Retorna a fila após a remoção.
 */
Queue dequeue(Queue qeu, int *info) {
  if (qeu == NULL || isEmptyQueue(qeu)) return qeu;
  NodeQ *temp = qeu->head;
  *info = temp->info;
  qeu->head = temp->prox;
  if (qeu->head == NULL) qeu->tail = NULL;
  free(temp);
  qeu->N--;
  return qeu;
}

/**
 * @brief Obtém o valor do primeiro elemento da fila sem removê-lo.
 * 
 * Armazena o valor do primeiro nó da fila no ponteiro `info` passado por parâmetro.
 * 
 * @param qeu Um ponteiro para a fila.
 * @param info Um ponteiro onde o valor será armazenado.
 * @return int Retorna 1 se o valor foi obtido com sucesso, ou 0 se a fila estiver vazia.
 */
int front(Queue qeu, int *info) {
  if (qeu == NULL || isEmptyQueue(qeu)) return 0;
  *info = qeu->head->info;
  return 1;
}

/**
 * @brief Exibe os elementos da fila.
 * 
 * Percorre todos os nós da fila e imprime os valores armazenados.
 * 
 * @param qeu Um ponteiro para a fila a ser exibida.
 * @return int Retorna 1 se a fila foi exibida com sucesso, ou 0 se a fila estiver vazia.
 */
int printQueue(Queue qeu) {
  if (isEmptyQueue(qeu)) return 0;
  NodeQ *temp = qeu->head;
  while (temp != NULL) {
    printf("%d ", temp->info);
    temp = temp->prox;
  }
  return 1;
}