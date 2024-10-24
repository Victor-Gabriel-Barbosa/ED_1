#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stringlib.h>
#include <queue.h>

/**
 * @brief Estrutura que representa um nó em uma fila.
 */
typedef struct nodeQ { 
  obj info;           /**< Informação armazenada na fila */
  struct nodeQ *prox; /**< Ponteiro para o próximo nó da fila */
} NodeQ;
 
/**
 * @brief Estrutura que representa uma fila.
 */
typedef struct queue_t { 
  NodeQ *head; /**< Cabeça da fila */
  NodeQ *tail; /**< Cauda da fila */
  size_t N;    /**< Contador de elementos */
} *queue;

/**
 * @brief Cria uma nova fila vazia.
 * 
 * Esta função aloca memória para uma nova fila e inicializa seus 
 * atributos. A fila criada terá o ponteiro 'head' e 'tail' 
 * configurados como NULL e o tamanho 'N' igual a 0.
 *
 * @return Ponteiro para a nova fila, ou NULL se a alocação de memória falhar.
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
 * @brief Libera a memória utilizada por uma fila.
 * 
 * Esta função percorre todos os nós da fila e libera a memória 
 * associada a cada um deles. Se os nós contiverem objetos, 
 * a função 'objDestroy' é chamada para liberar esses objetos. 
 * Após liberar todos os nós, a fila em si também é liberada.
 *
 * @param qeu Ponteiro para a fila a ser destruída.
 * @return NULL, indicando que a fila foi destruída e não deve mais ser utilizada.
 */
queue queueDestroy(queue qeu) {
  if (qeu == NULL) return qeu;
  NodeQ* aux = qeu->head;
  while (aux != NULL) {
    NodeQ* temp = aux->prox;
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
 * Esta função verifica se a fila é NULL ou se o ponteiro 
 * 'head' da fila está NULL. Se qualquer uma dessas condições 
 * for verdadeira, a fila é considerada vazia.
 *
 * @param qeu Ponteiro para a fila a ser verificada.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int queueIsEmpty(queue qeu) {
  return (qeu == NULL || qeu->head == NULL);
}

/**
 * @brief Retorna o tamanho da fila.
 * 
 * Esta função retorna o número de elementos na fila. Se a fila 
 * for NULL, a função retorna 0, indicando que não há elementos.
 *
 * @param qeu Ponteiro para a fila cuja dimensão será verificada.
 * @return O número de elementos na fila. Retorna 0 se a fila for NULL.
 */
size_t queueSize(queue qeu) {
  return (qeu == NULL) ? 0 : qeu->N;
}

/**
 * @brief Insere um novo elemento na fila.
 * 
 * Esta função cria um novo nó com o valor fornecido e o adiciona 
 * ao final da fila. Se a fila for NULL, a função retorna NULL. Se a 
 * alocação de memória para o novo nó falhar, a fila permanece inalterada.
 *
 * @param qeu Ponteiro para a fila onde o elemento será inserido.
 * @param info O valor a ser inserido na fila.
 * @return Ponteiro para a fila atualizada, ou NULL se a fila for NULL ou a alocação falhar.
 */
queue queueEnqueue(queue qeu, const obj info) {
  if (qeu == NULL) return NULL;
  NodeQ* newNode = (NodeQ*) malloc(sizeof(NodeQ));
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
 * @brief Remove e retorna o elemento do início da fila.
 * 
 * Esta função remove o primeiro elemento da fila e armazena seu 
 * valor no ponteiro fornecido. Se a fila estiver vazia, a função 
 * não faz alterações e retorna a fila inalterada.
 *
 * @param qeu Ponteiro para a fila da qual o elemento será removido.
 * @param info Ponteiro onde o valor do elemento removido será armazenado.
 * @return Ponteiro para a fila atualizada, ou a fila inalterada se estiver vazia.
 */
queue queueDequeue(queue qeu, obj* info) {
  if (queueIsEmpty(qeu)) return qeu;
  NodeQ* temp = qeu->head;
  *info = temp->info;
  qeu->head = temp->prox;
  if (qeu->head == NULL) qeu->tail = NULL;
  free(temp);
  qeu->N--;
  return qeu;
}
 
/**
 * @brief Obtém o elemento do início da fila sem removê-lo.
 * 
 * Esta função armazena o valor do primeiro elemento da fila 
 * no ponteiro fornecido. Se a fila estiver vazia, a função 
 * retorna 0, indicando que não há elementos a serem retornados.
 *
 * @param qeu Ponteiro para a fila da qual o elemento será obtido.
 * @param info Ponteiro onde o valor do elemento do início da fila será armazenado.
 * @return 1 se o elemento foi obtido com sucesso, ou 0 se a fila estiver vazia.
 */
int queueFront(queue qeu, obj* info) {
  if (queueIsEmpty(qeu)) return 0;
  *info = qeu->head->info;
  return 1;
}

/**
 * @brief Compara duas filas.
 * 
 * Esta função compara duas filas com base no número de elementos e 
 * nos valores armazenados em cada um dos nós. Retorna 0 se as filas 
 * forem iguais, -1 se a primeira fila for menor que a segunda, e 1 
 * se a primeira fila for maior que a segunda. Se uma das filas for 
 * NULL, esta será considerada menor.
 *
 * @param qeu1 Ponteiro para a primeira fila a ser comparada.
 * @param qeu2 Ponteiro para a segunda fila a ser comparada.
 * @return 0 se as filas forem iguais, -1 se a primeira fila for menor, 1 se a primeira fila for maior.
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
 * @brief Converte a fila em uma representação de string.
 * 
 * Esta função cria uma string que representa todos os elementos da fila, 
 * formatada entre parênteses e separados por vírgulas. Se a fila estiver 
 * vazia, a função retorna NULL.
 *
 * @param qeu Ponteiro para a fila a ser convertida em string.
 * @return Uma string representando a fila, ou NULL se a fila estiver vazia.
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
 * @brief Imprime a representação da fila na saída padrão.
 * 
 * Esta função converte a fila em uma string e a imprime na 
 * saída padrão. Se a fila estiver vazia, a função retorna 0. 
 * Caso contrário, retorna 1 após a impressão bem-sucedida.
 *
 * @param qeu Ponteiro para a fila a ser impressa.
 * @return 1 se a fila foi impressa com sucesso, ou 0 se a fila estiver vazia.
 */
int queuePrint(queue qeu) {
  if (queueIsEmpty(qeu)) return 0;
  string str = queueToString(qeu);
  stringPrint(str);
  stringDestroy(str);
  return 1; 
}  