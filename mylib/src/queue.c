#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <queue.h>
#include <stringlib.h>

/**
 * @brief Estrutura do nó da fila.
 * 
 * Cada nó contém um valor 'info' e um ponteiro para o próximo nó da fila.
 */
typedef struct nodeQ { 
  obj info;
  struct nodeQ *prox;
} NodeQ;
 
/**
 * @brief Estrutura da fila (queue).
 * 
 * A fila contém um ponteiro para o início ('head'), o fim ('tail'), 
 * e um contador de elementos ('N').
 */
typedef struct queue_t { 
  NodeQ *head;
  NodeQ *tail;
  size_t N;
} *queue;

/**
 * @brief Cria uma nova fila vazia.
 * 
 * Aloca memória para uma nova fila, inicializando os ponteiros de início e fim como 'NULL'
 * e o contador de elementos como zero.
 *  
 * @return queue Um ponteiro para a nova fila criada.
 */
queue queueNew() {
  queue qeu = (queue)malloc(sizeof(struct queue_t));
  if (qeu == NULL) return qeu;
  qeu->head = NULL;
  qeu->tail = NULL;
  qeu->N = 0;
  return qeu;
}

/**
 * @brief Destrói a fila e libera a memória associada.
 * 
 * Remove todos os nós da fila e libera a memória alocada para a estrutura da fila.
 * 
 * @param qeu Um objeto para a fila a ser destruída.
 * @return 'NULL' após liberar a memória.
 */
queue queueDestroy(queue qeu) {
  if (qeu == NULL) return qeu;
  NodeQ *aux = qeu->head;
  while (aux != NULL) {
    NodeQ *temp = aux->prox;
    if (aux->info != NULL) aux->info = objDestroy(aux->info);
    free(aux);
    aux = temp;
  }
  free(qeu);
  return NULL; 
}

/**
 * @brief Verifica se a fila está vazia.
 * 
 * @param qeu Um objeto para a fila a ser verificada.
 * @return int Retorna 1 se a fila estiver vazia, ou 0 caso contrário.
 */
int queueIsEmpty(queue qeu) {
  return (qeu == NULL || qeu->head == NULL);
}

/**
 * @brief Retorna o número de elementos na fila.
 * 
 * @param qeu Um objeto para a fila.
 * @return size_t O número de elementos na fila.
 */
size_t queueSize(queue qeu) {
  return (qeu == NULL) ? 0 : qeu->N;
}

/**
 * @brief Insere um novo elemento na fila.
 * 
 * Aloca um novo nó contendo o valor passado e o insere no fim da fila.
 * 
 * @param qeu Um objeto para a fila onde o elemento será inserido.
 * @param info O valor a ser inserido na fila.
 * @return queue Retorna a fila após a inserção do novo elemento.
 */
queue queueEnqueue(queue qeu, const obj info) {
  if (qeu == NULL) return NULL;
  NodeQ *newNode = (NodeQ *) malloc(sizeof(NodeQ));
  if (newNode == NULL) return qeu; 
  newNode->info = info;
  newNode->prox = NULL;
  if (queueIsEmpty(qeu)) qeu->head = newNode; 
  else qeu->tail->prox = newNode; 
  qeu->tail = newNode;
  qeu->N++;
  return qeu;
} 

/**
 * @brief Remove o primeiro elemento da fila.
 * 
 * Remove o nó que está no início da fila e retorna o valor removido através de um ponteiro.
 * 
 * @param qeu Um objeto para a fila de onde o elemento será removido.
 * @param info Um ponteiro para onde o valor removido será armazenado.
 * @return queue Retorna a fila após a remoção.
 */
queue queueDequeue(queue qeu, obj* info) {
  if (queueIsEmpty(qeu)) return qeu;
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
 * Armazena o valor do primeiro nó da fila no ponteiro 'info' passado por parâmetro.
 * 
 * @param qeu Um objeto para a fila.
 * @param info Um ponteiro onde o valor será armazenado.
 * @return int Retorna 1 se o valor foi obtido com sucesso, ou 0 se a fila estiver vazia.
 */
int queueFront(queue qeu, obj* info) {
  if (queueIsEmpty(qeu)) return 0;
  *info = qeu->head->info;
  return 1;
}

/**
 * Compara duas filas (queues).
 * 
 * @param qeu1 A primeira fila a ser comparada.
 * @param qeu2 A segunda fila a ser comparada.
 * 
 * @return 
 * - 1 se qeu1 for maior que qeu2 (em termos de tamanho ou conteúdo),
 * - -1 se qeu2 for maior que qeu1,
 * - 0 se ambas as filas forem iguais.
 */
int queueCmp(queue qeu1, queue qeu2) {
  if (qeu1 == NULL && qeu2 == NULL) return 0; 
  if (qeu1 == NULL) return -1; 
  if (qeu2 == NULL) return 1; 
  if (qeu1->N > qeu2->N) return 1; 
  if (qeu1->N < qeu2->N) return -1; 
  NodeQ *aux1 = qeu1->head;
  NodeQ *aux2 = qeu2->head;
  while (aux1 != NULL && aux2 != NULL) {
    if (objCmp(aux1->info, aux2->info) != 0) return (objCmp(aux1->info, aux2->info) > 0) ? 1 : -1;
    aux1 = aux1->prox;
    aux2 = aux2->prox;
  }
  return 0;
}

/** 
* @brief Printa todos os elementos de uma fila.
*
* @param qeu Objeto para a fila.
* @return 1 se a fila não é vazia, 0 caso contrário.
*/

/**
 * @brief Converte uma fila para uma string.
 * 
 * @param qeu Fila a ser convertida.
 * @return string da fila convertida.
 */
string queueToString(queue qeu) {
  if (queueIsEmpty(qeu)) return NULL;
  NodeQ *aux = qeu->head;
  string str = stringNew();
  stringAddChar(str, '(');
  while (aux != NULL) {
    string temp = toString(aux->info);
    str = stringAppend(str, temp);
    stringDestroy(temp);
    if (aux->prox != NULL) str = stringCat(str, ", ");
    aux = aux->prox;
  }
  stringAddChar(str, ')');
  return str;
}

/** 
* @brief Exibe todos os elementos de uma fila.
*
* @param qeu Objeto para a fila.
* @return 1 se a fila não é vazia, 0 caso contrário.
*/
int queuePrint(queue qeu) {
  if (queueIsEmpty(qeu)) return 0;
  stringPrint(queueToString(qeu));
  return 1;
}  