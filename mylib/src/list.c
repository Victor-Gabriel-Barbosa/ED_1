#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "list.h"
#include "stringlib.h"

/**
 * @brief Estrutura do nó da lista.
 * 
 * Cada nó contém um valor `info` e um ponteiro para o próximo nó e o anterior da lista.
 */
typedef struct nodeL {
  void *info;
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
  size_t sizeTip; 
} *List;

/**
 * @brief Cria uma nova lista encadeada.
 * 
 * Esta função aloca e inicializa uma nova lista encadeada genérica, que pode armazenar
 * elementos de qualquer tipo. O tipo de dado é definido pelo tamanho do tipo 
 * (retornado por `sizeof`) passado como parâmetro.
 * 
 * @param sizeTip O tamanho do tipo de dado que será armazenado na lista (usualmente obtido com `sizeof(tipo)`).
 * @return Retorna um ponteiro para a nova lista encadeada, ou NULL se a alocação falhar.
 *
 */
List listNew(size_t sizeTip) {
  List lst = (List)malloc(sizeof(struct list));
  if (lst != NULL) {
    lst->head = NULL;
    lst->tail = NULL;
    lst->N = 0;
    lst->sizeTip = sizeTip; 
  }
  return lst;
}

/**
 * @brief Destrói a lista encadeada e libera a memória alocada.
 * 
 * @param list Ponteiro para a lista a ser destruída.
 * @return NULL após a liberação da lista.
 */
List listDestroy(List lst) {
  if (lst == NULL) return NULL;
  NodeL *aux = lst->head;
  while (aux!= NULL) {
    NodeL *temp = aux;
    aux = aux->prox;
    if (temp->info != NULL) free(temp->info);
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
int listIsEmpty(List lst) {
  if (lst == NULL || lst->head == NULL) return 1;
  return 0;
}

/**
 * @brief Retorna o tamanho da lista.
 * 
 * @param lst Ponteiro para a lista.
 * @return O número de elementos na lista.
 */
size_t listSize(List lst) { 
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
List listAddIni(List lst, const void *info) {
  NodeL *newNode = (NodeL *)malloc(sizeof(NodeL));
  if (newNode == NULL) return lst; 
  newNode->info = malloc(lst->sizeTip);
  if (newNode->info == NULL) { 
    free(newNode); 
    return lst;
  }
  memcpy(newNode->info, info, lst->sizeTip);
  newNode->prox = lst->head;
  newNode->ant = NULL;
  if (lst->head != NULL) lst->head->ant = newNode;
  lst->head = newNode;
  if (lst->tail == NULL) lst->tail = newNode;
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
List listAddEnd(List lst, const void *info) {
  NodeL *newNode = (NodeL *)malloc(sizeof(NodeL));
  if (newNode == NULL) return lst;
  newNode->info = malloc(lst->sizeTip);
  if (newNode->info == NULL) { 
    free(newNode); 
    return lst;
  }
  memcpy(newNode->info, info, lst->sizeTip);
  newNode->prox = NULL;
  newNode->ant = lst->tail;
  if (lst->tail != NULL) lst->tail->prox = newNode;
  lst->tail = newNode;
  if (lst->head == NULL) lst->head = newNode;
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
List listRemove(List lst, const int pos) {
  if (lst == NULL || lst->head == NULL || pos < 0 || pos >= lst->N) return lst;
  NodeL *aux;
  if (pos == 0) {
    aux = lst->head;
    lst->head = aux->prox;
    if (lst->head != NULL) lst->head->ant = NULL;
    else lst->tail = NULL;
  } else if (pos == lst->N - 1) {
    aux = lst->tail;
    lst->tail = aux->ant;
    lst->tail->prox = NULL;
  } else {
    if (pos <= lst->N / 2) {
      aux = lst->head;
      for (int i = 0; i < pos; i++) aux = aux->prox;
    } else {
      aux = lst->tail;
      for (int i = lst->N - 1; i > pos; i--) aux = aux->ant;
    }
    aux->ant->prox = aux->prox;
    aux->prox->ant = aux->ant;
  }
  free(aux);
  lst->N--;  
  return lst;
}

/**
 * @brief Busca um elemento na lista na posição especificada.
 * 
 * @param lst Ponteiro para a lista.
 * @param pos Posição do elemento a ser buscado.
 * @param info Ponteiro onde o valor encontrado será armazenado.
 * @return 1 se encontrado, -1 se não encontrado.
 */
int listSearch(List lst, const int pos, void *info) {
  if (lst == NULL || lst->head == NULL || pos < 0 || pos >= lst->N) return -1;
  NodeL *aux = lst->head;
  for (int i = 0; i < pos; i++) aux = aux->prox;
  memcpy(info, aux->info, lst->sizeTip);
  return 1;
} 

/**
 * @brief Busca o índice de um elemento na lista
 * 
 * @param lst Ponteiro para a lista.
 * @param info Elemento que será usado para encontrar o índice.
 * @return Index de posição do elemento.
 */
int listIndex(List lst, void *info) {
  if (lst == NULL || lst->head == NULL) return -1;
  NodeL *aux = lst->head;
  for (int i = 0; i < lst->N; i++) {
    if (memcmp(info, aux->info, lst->sizeTip) == 0) return i;
    aux = aux->prox;
  }
  return -1;
}

/**
 * @brief Função para dividir a lista em duas metades.
 * 
 * @param head Ponteiro para o nó inicial da lista.
 * @return Ponteiro para o nó do meio (segunda metade da lista).
 */
NodeL* divide(NodeL* head) {
  NodeL* slow = head;
  NodeL* fast = head;
  while (fast->prox != NULL && fast->prox->prox != NULL) {
    slow = slow->prox;
    fast = fast->prox->prox;
  }
  NodeL* secondHalf = slow->prox;
  slow->prox = NULL;  // Divide a lista em duas partes
  return secondHalf;
}

/**
 * @brief Mescla duas sublistas ordenadas.
 * 
 * @param first Ponteiro para o início da primeira sublista.
 * @param second Ponteiro para o início da segunda sublista.
 * @param sizeTip Tamanho do tipo de dados armazenado.
 * @return Ponteiro para o início da lista mesclada.
 */
NodeL* merge(NodeL* first, NodeL* second, size_t sizeTip) {
  if (!first) return second;
  if (!second) return first;
  if (memcmp(first->info, second->info, sizeTip) <= 0) {
    first->prox = merge(first->prox, second, sizeTip);
    if (first->prox) first->prox->ant = first;
    return first;
  } else {
    second->prox = merge(first, second->prox, sizeTip);
    if (second->prox) second->prox->ant = second;
    return second;
  }
}

/**
 * @brief Ordena a lista encadeada usando Merge Sort.
 * 
 * @param head Ponteiro para o primeiro nó da lista.
 * @param sizeTip Tamanho do tipo de dados armazenado.
 * @return Ponteiro para o início da lista ordenada.
 */
NodeL* mergeSort(NodeL* head, size_t sizeTip) {
  if (!head || !head->prox) return head;
  NodeL* secondHalf = divide(head);
  head = mergeSort(head, sizeTip);
  secondHalf = mergeSort(secondHalf, sizeTip);
  return merge(head, secondHalf, sizeTip);
}

/**
 * @brief Função principal para ordenar a lista.
 * 
 * @param lst Ponteiro para a lista.
 * @return 1 se a lista foi ordenada com sucesso, 0 se houver erro.
 */
int listSort(List lst) {
  if (lst == NULL || lst->head == NULL || lst->N <= 1) return 0;
  lst->head = mergeSort(lst->head, lst->sizeTip);
  NodeL* aux = lst->head;
  while (aux->prox != NULL) aux = aux->prox;
  lst->tail = aux;
  return 1; 
}

/**
 * @brief Mescla duas listas ordenadas em uma nova lista.
 * 
 * @param lst1 Ponteiro para a primeira lista.
 * @param lst2 Ponteiro para a segunda lista.
 * @return Ponteiro para a nova lista mesclada.
 */
List listMerge(List lst1, List lst2) {
  if (!lst1 || lst1->head == NULL) return lst2;
  if (!lst2 || lst2->head == NULL) return lst1;
  List mergedList = listNew(lst1->sizeTip); 
  if (!mergedList) return NULL; 
  NodeL *aux1 = lst1->head;
  NodeL *aux2 = lst2->head;
  while (aux1 != NULL && aux2 != NULL) {
    if (memcmp(aux1->info, aux2->info, lst1->sizeTip) <= 0) {
      listAddEnd(mergedList, aux1->info);
      aux1 = aux1->prox;
    } else {
      listAddEnd(mergedList, aux2->info);
      aux2 = aux2->prox;
    }
  }
  while (aux1 != NULL) {
    listAddEnd(mergedList, aux1->info);
    aux1 = aux1->prox;
  }
  while (aux2 != NULL) {
    listAddEnd(mergedList, aux2->info);
    aux2 = aux2->prox;
  }
  return mergedList;
}

/**
 * @brief Busca e retorna um elemento na lista na posição especificada.
 * 
 * @param lst Ponteiro para a lista.
 * @param pos Posição do elemento a ser buscado.
 * @return O elemento buscado.
 */
void *listGet(List lst, const int pos) {
  if (lst == NULL || lst->head == NULL || pos < 0 || pos >= lst->N) return NULL;
  NodeL *aux = lst->head;
  for (int i = 0; i < pos; i++) aux = aux->prox;
  return aux->info;
}

/** 
* @brief Simula o printf usando o tipo List.
*
* @param str Ponteiro para a List.
* @return 1 se a List não é vazia, 0 caso contrário.
*/
int listPrint(List lst) {
  if (lst == NULL || lst->head == NULL) return 0;
  NodeL *aux = lst->head;
  while (aux != NULL) {
    stringPrint(toString(aux->info, lst->sizeTip));
    printf(" ");
    aux = aux->prox;
  }
  return 1;
}  