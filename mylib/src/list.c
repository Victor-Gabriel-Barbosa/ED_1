#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "list.h"

/**
 * @brief Estrutura do nó da lista.
 * 
 * Cada nó contém um valor `info` e um ponteiro para o próximo e e anterior nó da lista.
 */
typedef struct nodeL {
  int info;
  struct nodeL *prox;
  struct nodeL *ant;
} NodeL;

/**
 * @brief Estrutura da lista (List).
 * 
 * A lista contém um ponteiro para o início (`inicio`), o fim (`fim`), 
 * e um contador de elementos (`N`).
 */
typedef struct list { 
  NodeL *head;
  NodeL *tail;
  size_t N;
} *List;

/**
 * @brief Cria uma nova lista encadeada.
 * @return Um ponteiro para a nova lista criada.
 */
List newList() {
  List lst = (List)malloc(sizeof(struct list));
  if (lst != NULL) {
    lst->head = NULL;
    lst->tail = NULL;
    lst->N = 0;
  }
  return lst;
}

/**
 * @brief Destrói a lista encadeada e libera a memória alocada.
 * 
 * @param list Ponteiro para a lista a ser destruída.
 * @return NULL após a liberação da lista.
 */
List destroyList(List lst) {
  if (lst == NULL) return NULL;
  NodeL *aux = lst->head;
  while (aux!= NULL) {
    NodeL *temp = aux;
    aux = aux->prox;
    free(temp);
  }
  free(lst);
  return NULL;
}

/**
 * @brief Verifica se a lista está vazia.
 * 
 * @param lst Ponteiro para a lista a ser verificada.
 * @return 1 se a lista estiver vazia, caso contrário, 0.
 */
int isEmptyList(List lst) {
  if (lst == NULL || lst->head == NULL) return 1;
  return 0;
}

/**
 * @brief Retorna o tamanho da lista.
 * 
 * @param lst Ponteiro para a lista.
 * @return O número de elementos na lista.
 */
size_t sizeList(List lst) { 
  if (lst == NULL) return 0;  
  return lst->N;
}

/**
 * @brief Insere um novo elemento no início da lista.
 * 
 * @param lst Ponteiro para a lista.
 * @param info O valor a ser inserido.
 * @return Ponteiro para a lista após a inserção.
 */
List insertAtBegin(List lst, const int info) {
  NodeL *novo = (NodeL *)malloc(sizeof(NodeL)); 
  if (novo == NULL) return lst; 
  novo->info = info;
  novo->prox = lst->head;
  novo->ant = NULL;
  if (lst->head != NULL) lst->head->ant = novo; 
  lst->head = novo;
  if (lst->tail == NULL) lst->tail = novo; 
  lst->N++;
  return lst;
}

/**
 * @brief Insere um novo elemento no final da lista.
 * 
 * @param lst Ponteiro para a lista.
 * @param info O valor a ser inserido.
 * @return Ponteiro para a lista após a inserção.
 */
List insertAtEnd(List lst, const int info) {
  NodeL *novo = (NodeL *)malloc(sizeof(NodeL));
  if (novo == NULL) return lst;
  novo->info = info;
  novo->prox = NULL;
  novo->ant = lst->tail;
  if (lst->tail != NULL) lst->tail->prox = novo;
  lst->tail = novo;
  if (lst->head == NULL) lst->head = novo;
  lst->N++;
  return lst;
}

/**
 * @brief Remove um elemento da lista na posição especificada.
 * 
 * @param lst Ponteiro para a lista.
 * @param pos Posição do elemento a ser removido.
 * @return Ponteiro para a lista após a remoção.
 */
List removeAt(List lst, const int pos) {
  if (lst == NULL || lst->head == NULL || pos < 0 || pos >= lst->N) return lst;
  NodeL *atual = lst->head;
  if (pos == 0) {
    lst->head = atual->prox;
    if (lst->head != NULL) lst->head->ant = NULL;
    else lst->tail = NULL;
    free(atual);
  } else {
    NodeL *anterior = atual;
    for (int i = 0; i < pos; i++) {
      anterior = anterior->prox;
    }
    NodeL *proximo = anterior->prox;
    anterior->prox = proximo->prox;
    if (proximo->prox != NULL) proximo->prox->ant = anterior;
    else lst->tail = anterior;
    free(proximo);
  }
  lst->N--;
  return lst; 
}

/**
 * @brief Busca um elemento na lista na posição especificada.
 * 
 * @param lst Ponteiro para a lista.
 * @param pos Posição do elemento a ser buscado.
 * @param info Ponteiro onde o valor encontrado será armazenado.
 * @return 0 se encontrado, -1 se não encontrado.
 */
int searchAt(List lst, const int pos, int *info) {
  if (lst == NULL || lst->head == NULL || pos < 0 || pos >= lst->N) return -1;
  NodeL *atual = lst->head;
  for (int i = 0; i < pos; i++) {
    atual = atual->prox;
  }
  *info = atual->info;
  return 0;
}

/**
 * @brief Exibe todos os elementos da lista.
 * 
 * @param lst Ponteiro para a lista.
 * @return 1 se a lista foi exibida com sucesso, 0 se estiver vazia.
 */
int printList(List lst) {
  if (lst == NULL || lst->head == NULL) return 0;
  int cont = 0;
  NodeL *atual = lst->head;
  while (atual != NULL) { 
    printf("%d ", atual->info);
    atual = atual->prox;
  }
  return 1;
} 