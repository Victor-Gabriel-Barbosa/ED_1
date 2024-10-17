#include <stdio.h>
#include <math.h> 
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <typeslib.h>
#include <list.h>
#include <stringlib.h>

/**
 * @brief Estrutura do nó da lista.
 * 
 * Cada nó contém um valor `info` e um ponteiro para o próximo e o anterior nó da lista.
 */
typedef struct nodeL {
  Auto info;
  struct nodeL *prox;
  struct nodeL *ant;
} NodeL;

/**
 * @brief Estrutura da lista (List).
 * 
 * A lista contém um ponteiro para o início (`head`), o fim (`tail`), 
 * um contador de elementos (`N`), o tipo de elementos ('type').
 */
typedef struct list { 
  NodeL *head;
  NodeL *tail;
  size_t N;
} *List;

/**
 * @brief Cria uma nova lista encadeada.
 * 
 * Esta função aloca e inicializa uma nova lista encadeada genérica, que pode armazenar
 * elementos de qualquer tipo. O tipo de dado é definido pelo tamanho do tipo 
 * (retornado por `sizeof`) passado como parâmetro.
 * 
 * @return Retorna um ponteiro para a nova lista encadeada, ou NULL se a alocação falhar.
 *
 */
List listNew() {
  List lst = (List)malloc(sizeof(struct list));
  if (lst == NULL) return lst;
  lst->head = NULL;
  lst->tail = NULL;
  lst->N = 0;
  return lst;
}

/**
 * @brief Destrói a lista encadeada e libera a memória alocada.
 * 
 * @param List Ponteiro para a lista a ser destruída.
 * @return NULL após a liberação da lista.
 */
List listDestroy(List lst) {
  if (lst == NULL) return NULL;
  NodeL *aux = lst->head;
  while (aux != NULL) {
    NodeL *temp = aux;
    aux = aux->prox;
    free(temp->info);
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
  return (lst == NULL || lst->head == NULL);
}

/**
 * @brief Retorna o tamanho da lista.
 * 
 * @param lst Ponteiro para a lista.
 * @return O número de elementos na lista.
 */
size_t listSize(List lst) { 
  return (lst == NULL) ? 0 : lst->N;
}

/**
 * @brief Insere um novo elemento no início da lista.
 * 
 * @param lst Ponteiro para a lista.
 * @param info O valor a ser inserido.
 * @return Ponteiro para a lista após a inserção.
 */
List listAddIni(List lst, const Auto info) {
  if (lst == NULL) return lst;
  NodeL *newNode = (NodeL *)malloc(sizeof(NodeL));
  if (newNode == NULL) return lst; 
  newNode->info = info;
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
List listAddEnd(List lst, const Auto info) {
  if (lst == NULL) return lst;
  NodeL *newNode = (NodeL *)malloc(sizeof(NodeL));
  if (newNode == NULL) return lst;
  newNode->info = info;
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
  if (listIsEmpty(lst) || pos < 0 || pos >= lst->N) return lst;
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
int listSearch(List lst, const int pos, Auto *info) {
  if (listIsEmpty(lst) || pos < 0 || pos >= lst->N) return -1;
  NodeL *aux = lst->head;
  for (int i = 0; i < pos; i++) aux = aux->prox;
  *info = aux->info;
  return 1;
} 

/**
 * @brief Busca o índice de um elemento na lista
 * 
 * @param lst Ponteiro para a lista.
 * @param info Elemento que será usado para encontrar o índice.
 * @return Index de posição do elemento.
 */
int listIndex(List lst, Auto info) {
  if (listIsEmpty(lst)) return -1;
  NodeL *aux = lst->head;
  for (int i = 0; i < lst->N; i++) {
    if (autoCmp(aux->info, info) == 0) return i;
    aux = aux->prox;
  }
  return -1;
}

/**
 * @brief Função auxiliar para trocar dois ponteiros de informações.
 * 
 * @param a Endereço do ponteiro para a primeira informação.
 * @param b Endereço do ponteiro para a segunda informação.
 */
void swap(Auto *a, Auto *b) {
  Auto temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * @brief Função auxiliar do HeapSort para garantir a propriedade de heap.
 * 
 * @param arr Array de nós da lista.
 * @param n Número de elementos no array.
 * @param i Índice do nó atual a ser verificado.
 */
void heapify(NodeL *arr[], int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  if (left < n && autoCmp(arr[left]->info, arr[largest]->info) > 0) largest = left;
  if (right < n && autoCmp(arr[right]->info, arr[largest]->info) > 0) largest = right;
  if (largest != i) {
    swap(&arr[i]->info, &arr[largest]->info);
    heapify(arr, n, largest);
  }
}

/**
 * @brief Função HeapSort para ordenar uma sublista.
 * 
 * @param low Ponteiro para o início da sublista.
 * @param high Ponteiro para o final da sublista.
 */
void heapSort(NodeL *low, NodeL *high) {
  int n = 0;
  NodeL *temp = low;
  while (temp != high->prox) {
    n++;
    temp = temp->prox;
  }
  NodeL *arr[n];
  temp = low;
  for (int i = 0; i < n; i++) {
    arr[i] = temp;
    temp = temp->prox;
  }
  for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
  for (int i = n - 1; i >= 0; i--) {
    swap(&arr[0]->info, &arr[i]->info);
    heapify(arr, i, 0);
  }
}

/**
 * @brief Particiona a sublista para o QuickSort e retorna o pivô.
 * 
 * @param low Ponteiro para o início da sublista.
 * @param high Ponteiro para o final da sublista.
 * @return Ponteiro para o novo pivô.
 */
NodeL *partition(NodeL *low, NodeL *high) {
  Auto pivot = high->info;
  NodeL *i = low->ant;
  for (NodeL *j = low; j != high; j = j->prox) {
    if (autoCmp(j->info, pivot) <= 0) {
      i = (i == NULL) ? low : i->prox;
      swap(&i->info, &j->info);
    }
  } 
  i = (i == NULL) ? low : i->prox;
  swap(&i->info, &high->info);
  return i;
}

/**
 * @brief Função recursiva para realizar o Introsort.
 * 
 * @param low Ponteiro para o início da sublista.
 * @param high Ponteiro para o final da sublista.
 * @param depthLimit Limite de profundidade para alternar para o HeapSort.
 */
void introSort(NodeL *low, NodeL *high, int depthLimit) {
  if (high && low != high && low != high->prox) {
    if (depthLimit == 0) {
      heapSort(low, high);  
      return;
    }
    NodeL *p = partition(low, high);
    introSort(low, p->ant, depthLimit - 1);
    introSort(p->prox, high, depthLimit - 1);
  }
}

/**
 * @brief Função principal para iniciar o Introsort, calculando o limite de profundidade.
 * 
 * @param low Ponteiro para o início da sublista.
 * @param high Ponteiro para o final da sublista.
 */
void quickSort(NodeL *low, NodeL *high) {
  int n = 0;
  NodeL *temp = low;
  while (temp != high->prox) {
    n++;
    temp = temp->prox;
  }
  int depthLimit = 2 * (int)log2(n);  // Limite de profundidade é 2 * log2(n)
  introSort(low, high, depthLimit);
}

/**
 * @brief Função principal para ordenar a lista.
 * 
 * @param lst Ponteiro para a lista.
 * @return A lista ordenada.
 */
List listSort(List lst) {
  if (lst->head == NULL || lst->N <= 1) return lst;
  NodeL *high = lst->tail;
  quickSort(lst->head, high);
  return lst;
} 

/**
 * @brief Mescla duas listas ordenadas em uma nova lista.
 * 
 * @param lst1 Ponteiro para a primeira lista.
 * @param lst2 Ponteiro para a segunda lista.
 * @return Ponteiro para a nova lista mesclada.
 */
List listMerge(List lst1, List lst2) {
  if (lst1 == NULL || lst1->head == NULL) return lst2;
  if (lst2 == NULL || lst2->head == NULL) return lst1;
  List mergedList = listNew(); 
  if (!mergedList) return NULL; 
  NodeL *aux1 = lst1->head;
  NodeL *aux2 = lst2->head;
  while (aux1 != NULL && aux2 != NULL) {
    if (autoCmp(aux1->info, aux2->info) <= 0) {
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
  if (listIsEmpty(lst) || pos < 0 || pos >= lst->N) return NULL;
  NodeL *aux = lst->head;
  for (int i = 0; i < pos; i++) aux = aux->prox;
  return aux->info;
}
 
/** 
* @brief Printa todos os elementos de uma lista.
*
* @param lst Ponteiro para a lista.
* @return 1 se a lista não é vazia, 0 caso contrário.
*/
int listPrint(List lst) {
  if (listIsEmpty(lst)) return 0;
  NodeL *aux = lst->head;
  while (aux != NULL) {
    stringPrint(toString(aux->info));
    printf(" ");
    aux = aux->prox;
  }
  return 1;
}  