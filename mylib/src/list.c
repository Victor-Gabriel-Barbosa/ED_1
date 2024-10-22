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
 */
typedef struct nodeL {
  obj info;           /**< Informação armazenada na lista */
  struct nodeL* prox; /**< Ponteiro para o próximo nó da lista */
  struct nodeL* ant;  /**< Ponteiro para o nó anterior da lista */
} NodeL;

/**
 * @brief Estrutura da lista (list).
 */
typedef struct list_t { 
  NodeL* head; /**< Cabeça da lista */
  NodeL* tail; /**< Cauda da lista */
  size_t N;    /**< Contador de elementos */
} *list;

/**
 * @brief Cria uma nova lista duplamente encadeada e inicializa seus campos.
 * 
 * @return Retorna um ponteiro para a nova lista. Se a alocação falhar, retorna NULL.
 * 
 * A lista criada tem os ponteiros 'head' e 'tail' (início e fim) inicialmente nulos
 * e o tamanho (N) é definido como 0.
 */
list listNew() {
  list lst = (list)malloc(sizeof(struct list_t));
  if (lst == NULL) return NULL; 
  lst->head = NULL;
  lst->tail = NULL; 
  lst->N = 0;
  return lst;
}

/**
 * @brief Libera toda a memória alocada para a lista e seus elementos.
 * 
 * @param lst Ponteiro para a lista a ser destruída.
 * 
 * @return Retorna NULL após a destruição da lista.
 * 
 * A função percorre a lista do início ao fim, liberando cada nó e sua
 * informação (caso o campo 'info' esteja alocado). No final, também
 * libera a estrutura da lista em si.
 */
list listDestroy(list lst) {
  if (lst == NULL) return NULL; // Verifica se a lista existe
  NodeL* aux = lst->head; 
  while (aux != NULL) { 
    NodeL* temp = aux; 
    aux = aux->prox;
    if (temp->info != NULL) temp->info = objDestroy(temp->info); 
    free(temp); 
    temp = NULL;
  }
  free(lst);
  return NULL;
}

/**
 * @brief Verifica se a lista está vazia.
 * 
 * @param lst Lista a ser verificada.
 * @return 1 se a lista estiver vazia, caso contrário, 0.
 */
int listIsEmpty(list lst) {
  return (lst == NULL || lst->head == NULL); 
}

/**
 * @brief Retorna o tamanho da lista.
 * 
 * @param lst Lista.
 * @return O número de elementos na lista.
 */
size_t listSize(list lst) { 
  return (lst == NULL) ? 0 : lst->N;
}

/**
 * @brief Insere um novo elemento no início da lista.
 * 
 * @param lst Lista.
 * @param info O valor a ser inserido (obj).
 * @return Lista após a inserção.
 */
list listAddIni(list lst, const obj info) {
  if (lst == NULL) return NULL; 
  NodeL* newNode = (NodeL*)malloc(sizeof(NodeL));
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
 * @param lst Lista.
 * @param info O valor a ser inserido (obj).
 * @return Lista após a inserção.
 */
list listAddEnd(list lst, const obj info) {
  if (lst == NULL) return NULL;
  NodeL* newNode = (NodeL*)malloc(sizeof(NodeL));
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
 * @param lst Lista.
 * @param pos Posição do elemento a ser removido.
 * @return Lista após a remoção.
 */
list listRemove(list lst, const int pos) {
  if (listIsEmpty(lst) || pos < 0 || pos >= lst->N) return lst;  
  NodeL* aux;
  if (pos == 0) {
    aux = lst->head;
    lst->head = aux->prox;
    (lst->head != NULL) ? (lst->head->ant = NULL) : (lst->tail = NULL);
  } else if (pos == lst->N - 1) {
    aux = lst->tail;
    lst->tail = aux->ant;
    (lst->tail != NULL) ? (lst->tail->prox = NULL) : (lst->head = NULL);
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
 * @param lst Lista.
 * @param pos Posição do elemento a ser buscado.
 * @param info Objeto para armazenar o dado encontrado (obj).
 * @return 1 se encontrado, -1 se não encontrado.
 */
int listSearch(list lst, const int pos, obj* info) {
  if (listIsEmpty(lst) || pos < 0 || pos >= lst->N || info == NULL) return -1;
  NodeL* aux;
  if (pos <= lst->N / 2) {
    aux = lst->head;
    for (int i = 0; i < pos; i++) aux = aux->prox;
  } else {
    aux = lst->tail;
    for (int i = lst->N - 1; i > pos; i--) aux = aux->ant;
  }
  *info = aux->info;
  return 1; 
}

/**
 * @brief Busca e retorna um elemento na lista na posição especificada.
 * 
 * @param lst Lista.
 * @param pos Posição do elemento a ser buscado.
 * @return O elemento buscado (obj).
 */
obj listGet(list lst, const int pos) {
  if (listIsEmpty(lst) || pos < 0 || pos >= lst->N) return NULL;
  NodeL* aux = lst->head;
  for (int i = 0; i < pos; i++) aux = aux->prox;
  return aux->info;
}

/**
 * @brief Busca o índice de um elemento na lista
 * 
 * @param lst Lista.
 * @param info Elemento que será usado para encontrar o índice (obj).
 * @return Index de posição do elemento.
 */
int listIndex(list lst, obj info) {
  if (listIsEmpty(lst)) return -1;
  NodeL* aux = lst->head;
  for (int i = 0; i < lst->N; i++) {
    if (objCmp(aux->info, info) == 0) return i;
    aux = aux->prox;
  }
  return -1;
}

/**
 * Compara duas listas.
 * 
 * @param lst1 A primeira lista a ser comparada.
 * @param lst2 A segunda lista a ser comparada.
 * 
 * @return 
 * - 1 se lst1 for maior que lst2,
 * - -1 se lst2 for maior que lst1,
 * - 0 se ambas as listas forem iguais (tanto em tamanho quanto em conteúdo).
 */
int listCmp(list lst1, list lst2) {
  if (lst1 == NULL && lst2 == NULL) return 0; 
  if (lst1 == NULL) return -1; 
  if (lst2 == NULL) return 1; 
  if (lst1->N > lst2->N) return 1; 
  if (lst1->N < lst2->N) return -1; 
  NodeL* aux1 = lst1->head;
  NodeL* aux2 = lst2->head;
  while (aux1 != NULL && aux2 != NULL) {
    if (objCmp(aux1->info, aux2->info) != 0) return (objCmp(aux1->info, aux2->info) > 0) ? 1 : -1; 
    aux1 = aux1->prox;
    aux2 = aux2->prox;
  }
  return 0;
}

/**
 * @brief Função auxiliar para trocar dois ponteiros de informações (obj).
 * 
 * @param a Endereço do obj para a primeira informação.
 * @param b Endereço do obj para a segunda informação.
 * @return 1 se a troca foi feita com sucesso, 0 caso contrário
 */
int swap(obj* a, obj* b) {
  if (a == NULL || b == NULL) return 0; 
  obj temp = *a;
  *a = *b;
  *b = temp;
  return 1;
}

/**
 * @brief Função auxiliar do HeapSort para garantir a propriedade de heap.
 * 
 * @param arr Array de nós da lista.
 * @param n Número de elementos no array.
 * @param i Índice do nó atual a ser verificado.
 */
void heapify(NodeL** arr, int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  if (left < n && objCmp(arr[left]->info, arr[largest]->info) > 0) largest = left;
  if (right < n && objCmp(arr[right]->info, arr[largest]->info) > 0) largest = right;
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
 * @return 0 se bem-sucedido, -1 se falhar.
 */
int heapSort(NodeL* low, NodeL* high) {
  int n = 0;
  NodeL* temp = low;
  while (temp != high->prox) {
    n++;
    temp = temp->prox;
  }
  NodeL** arr = malloc(n * sizeof(NodeL*));
  if (arr == NULL) return -1;
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
  free(arr);
  return 0;
}

/**
 * @brief Particiona a sublista para o QuickSort e retorna o pivô.
 * 
 * @param low Ponteiro para o início da sublista.
 * @param high Ponteiro para o final da sublista.
 * @return Ponteiro para o novo pivô.
 */
NodeL* partition(NodeL* low, NodeL* high) {
  obj pivot = high->info;
  NodeL* i = low->ant;
  for (NodeL* j = low; j != high; j = j->prox) {
    if (objCmp(j->info, pivot) <= 0) {
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
 * @return 0 se bem-sucedido, -1 se falhar.
 */
int introSort(NodeL* low, NodeL* high, int depthLimit) {
  if (high && low != high && low != high->prox) {
    if (depthLimit == 0) return (heapSort(low, high) != 0) ? -1 : 0;
    NodeL* p = partition(low, high);
    if (introSort(low, p->ant, depthLimit - 1) != 0) return -1;
    if (introSort(p->prox, high, depthLimit - 1) != 0) return -1;
  }
  return 0; 
}

/**
 * @brief Função principal para iniciar o Introsort, calculando o limite de profundidade.
 * 
 * @param low Ponteiro para o início da sublista.
 * @param high Ponteiro para o final da sublista.
 * @return 0 se bem-sucedido, -1 se falhar.
 */
int quickSort(NodeL* low, NodeL* high) {
  int n = 0;
  NodeL* temp = low;
  while (temp != high->prox) {
    n++;
    temp = temp->prox;
  }
  int depthLimit = 2 * (int)log2(n);  // Limite de profundidade é 2 * log2(n)
  if (introSort(low, high, depthLimit) != 0) return -1;
  return 0;  
}

/**
 * @brief Função principal para ordenar a lista.
 * 
 * Ordena usando o mecanismo de ordenação Intro Sort.
 * Complexidade (Pior Caso): O(NlogN).
 * 
 * @param lst Lista.
 * @return A lista ordenada.
 */
list listSort(list lst) {
  if (listIsEmpty(lst) || lst->N <= 1) return lst;
  NodeL* high = lst->tail;
  if (quickSort(lst->head, high) != 0) fprintf(stderr, "Error: listSort failed");
  return lst;
} 

/**
 * @brief Mescla duas listas ordenadas em uma nova lista.
 * 
 * @param lst1 Objeto para a primeira lista.
 * @param lst2 Objeto para a segunda lista.
 * @return Objeto para a nova lista mesclada.
 */
list listMerge(list lst1, list lst2) {
  if (lst1 == NULL || lst1->head == NULL) return lst2;
  if (lst2 == NULL || lst2->head == NULL) return lst1;
  list mergedList = listNew(); 
  if (!mergedList) return NULL; 
  NodeL* aux1 = lst1->head;
  NodeL* aux2 = lst2->head;
  while (aux1 != NULL && aux2 != NULL) {
    if (objCmp(aux1->info, aux2->info) <= 0) {
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
 * @brief Converte uma lista para uma string.
 * 
 * @param lst Lista a ser convertida.
 * @return string da lista convertida.
 */
string listToString(list lst) {
  if (listIsEmpty(lst)) return NULL;
  NodeL* aux = lst->head;
  string str = stringNew();
  stringAddChar(str, '[');
  while (aux != NULL) {
    string temp = toString(aux->info);
    str = stringAppend(str, temp);
    stringDestroy(temp);
    if (aux->prox != NULL) str = stringCat(str, ", ");
    aux = aux->prox;
  }
  stringAddChar(str, ']');
  return str;
}

/** 
* @brief Exibe todos os elementos de uma lista.
*
* @param lst Lista.
* @return 1 se a lista não é vazia, 0 caso contrário.
*/
int listPrint(list lst) {
  if (listIsEmpty(lst)) return 0;
  string str = listToString(lst);
  stringPrint(str);
  stringDestroy(str);
  return 1;
}  