#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h> 
#include <string.h>
#include "typeslib.h"
#include "stringlib.h"
#include "list.h"

/**
 * @brief Estrutura que representa um nó em uma lista duplamente encadeada.
 */
typedef struct nodeL {
  obj info;           /**< Informação armazenada na lista */
  struct nodeL* prox; /**< Ponteiro para o próximo nó da lista */
  struct nodeL* ant;  /**< Ponteiro para o nó anterior da lista */
} NodeL;

/**
 * @brief Estrutura que representa uma lista duplamente encadeada.
 */
typedef struct list_t { 
  NodeL* head; /**< Cabeça da lista */
  NodeL* tail; /**< Cauda da lista */
  size_t N;    /**< Contador de elementos */
} *list;

/**
 * @brief Calcula o tamanho em bytes da estrutura de dados 'list_t'.
 * 
 * Esta função utiliza o operador 'sizeof' para retornar o tamanho em bytes da estrutura
 * 'list_t', que representa um nó ou elemento da lista. Ela não retorna o número de 
 * elementos presentes na lista, mas sim a quantidade de memória que um único elemento 
 * dessa estrutura ocupa.
 * 
 * @return size_t O tamanho em bytes da estrutura 'list_t'.
 */
size_t sizeofList() {
  return sizeof(struct list_t);
}

/**
 * @brief Cria uma nova lista duplamente encadeada e inicializa seus campos.
 * 
 * A lista criada tem os ponteiros 'head' e 'tail' (início e fim) inicialmente nulos
 * e o tamanho (N) é definido como 0.
 * 
 * @return Um ponteiro para a nova lista, ou NULL se a alocação de memória falhar.
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
 * A função percorre a lista do início ao fim, liberando cada nó e sua
 * informação (caso o campo 'info' esteja alocado). No final, também
 * libera a estrutura da lista em si.
 * 
 * @param lst Ponteiro para a lista a ser destruída.
 * @return NULL após a destruição da lista.
 */
list listFree(list lst) {
  if (lst == NULL) return NULL; 
  NodeL* aux = lst->head; 
  while (aux != NULL) { 
    NodeL* temp = aux; 
    aux = aux->prox;
    if (temp->info != NULL) temp->info = objFree(temp->info); 
    free(temp); 
  }
  free(lst);
  return NULL;
}

/**
 * @brief Verifica se uma lista encadeada está vazia.
 *
 * A função verifica se a lista é nula ou se a cabeça da lista é nula, 
 * indicando que a lista não contém elementos. Retorna 1 se a lista estiver 
 * vazia e 0 caso contrário.
 *
 * @param lst A lista a ser verificada.
 * @return 1 se a lista estiver vazia, 0 caso contrário.
 */
int listIsEmpty(const list lst) {
  return (lst == NULL || lst->head == NULL); 
}

/**
 * @brief Retorna o número de elementos na lista.
 *
 * A função verifica se a lista é nula e, se for, retorna 0. Caso contrário, retorna
 * o número de nós armazenados na lista.
 *
 * @param lst A lista da qual se deseja obter o tamanho.
 * @return O número de nós na lista ou 0 se a lista for nula.
 */
size_t listSize(const list lst) { 
  return (lst == NULL) ? 0 : lst->N;
}

/**
 * @brief Adiciona um novo nó no início da lista.
 *
 * A função cria um novo nó com o valor 'info' e o adiciona no início da lista.
 * Os ponteiros da lista são ajustados para garantir que o novo nó se torne a nova
 * cabeça da lista. Se a lista estava vazia, o novo nó também se torna a cauda.
 *
 * @param lst A lista onde o novo nó será adicionado.
 * @param info O objeto a ser armazenado no novo nó.
 * @return A lista atualizada com o novo nó no início.
 */
list listPushFront(list lst, const obj info) {
  if (lst == NULL || info == NULL) return NULL; 
  NodeL* newNode = (NodeL*)malloc(sizeof(NodeL));
  if (newNode == NULL) return lst; 
  newNode->info = objCopy(info); 
  newNode->prox = lst->head; 
  newNode->ant = NULL; 
  if (lst->head != NULL) lst->head->ant = newNode; 
  lst->head = newNode;
  if (lst->tail == NULL) lst->tail = newNode;
  lst->N++; 
  return lst;
}

/**
 * @brief Adiciona um novo nó ao final da lista.
 *
 * A função cria um novo nó com o valor 'info' e o adiciona no final da lista.
 * Se a lista estiver vazia, o novo nó se torna tanto a cabeça quanto a cauda.
 * Ajusta os ponteiros da lista de acordo com a nova estrutura.
 *
 * @param lst A lista onde o novo nó será adicionado.
 * @param info O objeto a ser armazenado no novo nó.
 * @return A lista atualizada com o novo nó no final.
 */
list listPushBack(list lst, const obj info) {
  if (lst == NULL || info == NULL) return NULL;
  NodeL* newNode = (NodeL*)malloc(sizeof(NodeL));
  if (newNode == NULL) return lst;  
  newNode->info = objCopy(info);
  newNode->prox = NULL;
  newNode->ant = lst->tail;  
  if (lst->tail != NULL) lst->tail->prox = newNode;
  lst->tail = newNode;
  if (lst->head == NULL) lst->head = newNode;
  lst->N++;
  return lst;
}

/**
 * @brief Substitui a primeira ocorrência de um objeto em uma lista.
 *
 * Esta função percorre a lista fornecida e substitui a primeira ocorrência
 * do objeto a pelo objeto b.
 *
 * @param lst A lista onde será feita a substituição. Não pode estar vazia.
 * @param info1 O objeto que será procurado na lista.
 * @param info2 O objeto que substituirá o objeto a.
 * @return A lista após a substituição. Se a lista estiver vazia, ou se a, ou b forem NULL, retorna a lista original.
 */
list listReplace(list lst, const obj info1, const obj info2) {
  if (listIsEmpty(lst) || info1 == NULL || info2 == NULL) return lst;
  NodeL* aux = lst->head;
  while (aux != NULL) {
    if (objCmp(aux->info, info1) == 0) {
      objFree(aux->info);
      aux->info = objCopy(info2);
      return lst;
    }
    aux = aux->prox;
  }
  return lst;
}

/**
 * @brief Substitui todas as ocorrências de um objeto em uma lista.
 *
 * Esta função percorre a lista fornecida e substitui todas as ocorrências
 * do objeto a pelo objeto b, contando quantas substituições foram feitas.
 *
 * @param lst A lista onde serão feitas as substituições. Não pode estar vazia.
 * @param info1 O objeto que será procurado na lista.
 * @param info2 O objeto que substituirá o objeto a.
 * @return O número de substituições realizadas. Se a lista estiver vazia, ou se a, ou b forem NULL, retorna 0.
 */
size_t listReplaceAll(list lst, const obj info1, const obj info2) {
  if (listIsEmpty(lst) || info1 == NULL || info2 == NULL) return 0;
  size_t count = 0;
  NodeL* aux = lst->head;
  while (aux != NULL) {
    if (objCmp(aux->info, info1) == 0) {
      objFree(aux->info);
      aux->info = objCopy(info2);
      count++;
    }
    aux = aux->prox;
  }
  return count;
}

/**
 * @brief Remove um nó da lista em uma posição específica.
 *
 * A função remove o nó da lista na posição 'pos' e ajusta os ponteiros de
 * acordo com a nova estrutura da lista após a remoção. Ela trata três casos:
 * remoção na cabeça, remoção na cauda e remoção de nós no meio da lista.
 *
 * @param lst A lista da qual o nó será removido.
 * @param pos A posição do nó a ser removido (de 0 a N-1).
 * @return A lista após a remoção do nó.
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
  if (aux->info != NULL) aux->info = objFree(aux->info);
  free(aux);
  lst->N--;
  return lst;
}

/**
 * @brief Remove e retorna o primeiro elemento da lista.
 *
 * A função remove e retorna o primeiro objeto da lista.
 * 
 * @param lst A lista da qual o nó será removido.
 * @param obj Ponteiro para armazenar o objeto encontrado.
 * @return A lista após a remoção do primeiro objeto.
 */
list listPopFront(list lst, obj* info) {
  if (listIsEmpty(lst) || info == NULL) return lst;
  NodeL* aux = lst->head;
  *info = objCopy(aux->info);
  lst->head = aux->prox;
  (lst->head != NULL) ? (lst->head->ant = NULL) : (lst->tail = NULL);
  if (aux->info != NULL) aux->info = objFree(aux->info);
  free(aux);
  lst->N--;
  return lst;
}

/**
 * @brief Remove e retorna o último elemento da lista.
 *
 * A função remove e retorna o último objeto da lista.
 * 
 * @param lst A lista da qual o nó será removido.
 * @param obj Ponteiro para armazenar o objeto encontrado.
 * @return A lista após a remoção do último nó.
 */
list listPopBack(list lst, obj* info) {
  if (listIsEmpty(lst) || info == NULL) return lst;
  NodeL* aux = lst->tail;
  *info = objCopy(aux->info);
  lst->tail = aux->ant;
  (lst->tail!= NULL) ? (lst->tail->prox = NULL) : (lst->head = NULL);
  if (aux->info!= NULL) aux->info = objFree(aux->info);
  free(aux);
  lst->N--;
  return lst;
}

/**
 * @brief Remove a primeira as ocorrência de um objeto em uma lista.
 *
 * Esta função percorre a lista fornecida e remove a primeira ocorrências do objeto info.
 *
 * @param lst A lista da qual os objetos serão removidos.
 * @param info O objeto que será removido da lista.
 * @return A lista após as remoções.
 */
list listRemoveIf(list lst, const obj info) {
  if (listIsEmpty(lst) || info == NULL) return lst;
  NodeL* aux = lst->head;
  NodeL* prev = NULL;
  while (aux != NULL) {
    if (objCmp(aux->info, info) == 0) {
      if (prev == NULL) lst->head = aux->prox;
      else prev->prox = aux->prox;
      if (aux->prox!= NULL) aux->prox->ant = prev;
      else lst->tail = prev;
      objFree(aux->info);
      free(aux);
      lst->N--;
      return lst;
    }
    prev = aux;
    aux = aux->prox;
  }
  return lst;
}

/**
 * @brief Remove todas as ocorrências de um objeto em uma lista e retorna a quantidade de elementos removidos.
 *
 * Esta função percorre a lista fornecida e remove todas as ocorrências do objeto info, contando quantas remoções foram feitas.
 *
 * @param lst A lista da qual os objetos serão removidos.
 * @param info O objeto que será removido da lista.
 * @return O número de elementos removidos.
 */
size_t listRemoveAllIf(list lst, const obj info) {
  if (listIsEmpty(lst) || info == NULL) return 0;
  size_t count = 0;
  NodeL* aux = lst->head;
  NodeL* prev = NULL;
  while (aux != NULL) {
    if (objCmp(aux->info, info) == 0) {
      NodeL* next = aux->prox;
      objFree(aux->info);
      free(aux);
      if (prev == NULL) lst->head = next;
      else prev->prox = next;
      aux = next;
      lst->N--;
      count++;
    } else {
      prev = aux;
      aux = aux->prox;
    }
  }
  return count;
}


/**
 * @brief Busca um objeto em uma posição específica da lista.
 *
 * A função percorre a lista em busca do objeto na posição 'pos' e retorna
 * o objeto encontrado através do ponteiro 'info'. Se a posição estiver
 * mais próxima da cabeça, a lista será percorrida a partir da cabeça. Caso contrário,
 * a lista será percorrida a partir da cauda para otimizar a busca.
 *
 * @param lst A lista onde será realizada a busca.
 * @param pos A posição do objeto a ser buscado (de 0 a N-1).
 * @param info Ponteiro para armazenar o objeto encontrado.
 * @return 1 se o objeto for encontrado e armazenado com sucesso,
 * ou -1 se a lista estiver vazia, a posição for inválida, ou o ponteiro 'info' for nulo.
 */
int listSearch(const list lst, const int pos, obj* info) {
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
 * @brief Retorna o objeto armazenado em uma posição específica da lista.
 *
 * A função acessa o nó na posição 'pos' da lista e retorna o objeto armazenado
 * nesse nó. Se a lista estiver vazia ou a posição for inválida, a função retorna NULL.
 *
 * @param lst A lista da qual se deseja obter o objeto.
 * @param pos A posição do nó de onde o objeto será obtido (de 0 a N-1).
 * @return O objeto armazenado no nó na posição especificada ou NULL se a posição for inválida.
 */
obj listGet(const list lst, const int pos) {
  if (listIsEmpty(lst) || pos < 0 || pos >= lst->N) return NULL;
  NodeL* aux = lst->head;
  for (int i = 0; i < pos; i++) aux = aux->prox;
  return aux->info;
}

/**
 * @brief Retorna o índice da primeira ocorrência de um objeto na lista.
 *
 * A função percorre a lista procurando o primeiro nó que contém um objeto 
 * igual ao 'info' (comparado usando 'objCmp'). Se o objeto for encontrado, 
 * a função retorna o índice (posição) desse nó. Se o objeto não for encontrado
 * ou a lista estiver vazia, a função retorna -1.
 *
 * @param lst A lista onde o objeto será procurado.
 * @param info O objeto a ser comparado com os elementos da lista.
 * @return O índice do primeiro nó contendo o objeto ou -1 se o objeto não for encontrado.
 */
int listIndex(const list lst, const obj info) {
  if (listIsEmpty(lst)) return -1;
  NodeL* aux = lst->head;
  for (int i = 0; i < lst->N; i++) {
    if (objCmp(aux->info, info) == 0) return i;
    aux = aux->prox;
  }
  return -1;
}

/**
 * @brief Cria uma cópia de uma lista encadeada.
 *
 * @param lst A lista a ser copiada.
 * @return Uma cópia da lista, ou NULL se a alocação de memória falhar.
 */
list listCopy(const list lst) {
  if (lst == NULL) return NULL;
  list newList = listNew();
  NodeL* aux = lst->head;
  while (aux != NULL) {
    newList = listAdd(newList, objCopy(aux->info));
    aux = aux->prox;
  }
  return newList;
}

/**
 * @brief Compara duas listas elemento por elemento.
 *
 * A função compara duas listas 'lst1' e 'lst2' levando em consideração o número 
 * de elementos e o conteúdo de cada nó. Se as listas forem idênticas em tamanho e 
 * conteúdo, a função retorna 0. Caso contrário, retorna 1 se 'lst1' for maior ou 
 * -1 se 'lst2' for maior. A comparação dos objetos é feita usando a função 'objCmp'.
 *
 * @param lst1 A primeira lista a ser comparada.
 * @param lst2 A segunda lista a ser comparada.
 * @return 0 se as listas forem iguais, 1 se 'lst1' for maior, -1 se 'lst2' for maior.
 */
int listCmp(const list lst1, const list lst2) {
  if (lst1 == NULL && lst2 == NULL) return 0; 
  if (lst1 == NULL) return -1; 
  if (lst2 == NULL) return 1; 
  if (lst1->N > lst2->N) return 1; 
  if (lst1->N < lst2->N) return -1; 
  NodeL* aux1 = lst1->head;
  NodeL* aux2 = lst2->head;
  while (aux1 != NULL && aux2 != NULL) {
    int cmp = objCmp(aux1->info, aux2->info);
    if (cmp != 0) return cmp;
    aux1 = aux1->prox;
    aux2 = aux2->prox;
  }
  return 0;
}

/**
 * @brief Ordena uma pequena lista usando o algoritmo Insertion Sort.
 *
 * Este método é mais eficiente para pequenos subconjuntos de dados devido ao
 * baixo overhead e ao desempenho superior em arrays pequenos em comparação
 * com o Quick Sort.
 *
 * @param low O primeiro nó da lista a ser ordenada.
 * @param high O último nó da lista a ser ordenada.
 */
void insertionSort(NodeL* low, NodeL* high) {
  for (NodeL* i = low->prox; i != high->prox; i = i->prox) {
    obj key = i->info;
    NodeL* j = i->ant;
    while (j != NULL && objCmp(j->info, key) > 0) {
      j->prox->info = j->info;
      j = j->ant;
    }
    if (j == NULL) low->info = key;
    else j->prox->info = key;
  }
}

/**
 * @brief Reorganiza uma subárvore para manter a propriedade do heap.
 *
 * A função ajusta uma subárvore com raiz no índice 'i' de um array de nós 
 * para garantir que a propriedade do heap (máximo ou mínimo) seja mantida.
 * Isso é feito comparando o nó atual com seus filhos e trocando os valores
 * quando necessário. A função é recursiva e continuará a ajustar o heap
 * até que a propriedade seja restabelecida.
 *
 * @param arr O array de nós a ser reorganizado.
 * @param n O tamanho do array.
 * @param i O índice do nó que será ajustado.
 */
void heapify(NodeL** arr, int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  if (left < n && objCmp(arr[left]->info, arr[largest]->info) > 0) largest = left;
  if (right < n && objCmp(arr[right]->info, arr[largest]->info) > 0) largest = right;
  if (largest != i) {
    objSwap(&arr[i]->info, &arr[largest]->info);
    heapify(arr, n, largest);
  }
}

/**
 * @brief Ordena uma lista encadeada usando o algoritmo Heap Sort.
 *
 * A função primeiro converte a parte da lista entre 'low' e 'high' em um array
 * de ponteiros para nós. Em seguida, aplica o algoritmo Heap Sort para organizar
 * os elementos do array, trocando as informações dos nós. Após a ordenação, o
 * array de ponteiros é liberado. Se houver falha na alocação de memória, a função
 * retorna -1; caso contrário, retorna 0 ao final do processo.
 *
 * @param low O primeiro nó da lista que será ordenada.
 * @param high O último nó da lista que será ordenada.
 * @return 0 se a ordenação for bem-sucedida ou -1 se ocorrer um erro de alocação de memória.
 */
void heapSort(NodeL* low, NodeL* high) {
  int n = 0;
  NodeL* temp = low;
  while (temp != high->prox) {
    n++;
    temp = temp->prox;
  }
  NodeL** arr = malloc(n * sizeof(NodeL*));
  if (arr == NULL) return; 
  temp = low;
  for (int i = 0; i < n; i++) {
    arr[i] = temp;
    temp = temp->prox;
  }
  for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
  for (int i = n - 1; i >= 0; i--) {
    objSwap(&arr[0]->info, &arr[i]->info);
    heapify(arr, i, 0);
  }
  free(arr);
}

/**
 * @brief Escolhe o pivô usando a "mediana de três" para melhorar o particionamento.
 *
 * Este método reduz a chance de escolher pivôs ruins ao ordenar, 
 * o que poderia causar um desempenho degenerado.
 *
 * @param low O primeiro nó da lista.
 * @param high O último nó da lista.
 * @return O ponteiro para o pivô escolhido.
 */
NodeL* medianOfThree(NodeL* low, NodeL* high) {
  NodeL* mid = low;
  int size = 0;
  for (NodeL* temp = low; temp != high; temp = temp->prox) size++;
  for (int i = 0; i < size / 2; i++) mid = mid->prox;
  if (objCmp(low->info, mid->info) > 0) objSwap(&low->info, &mid->info);
  if (objCmp(low->info, high->info) > 0) objSwap(&low->info, &high->info);
  if (objCmp(mid->info, high->info) > 0) objSwap(&mid->info, &high->info);
  return mid;
}

/**
 * @brief Particiona a lista encadeada em torno de um pivô.
 *
 * A função realiza a partição da lista encadeada entre os nós 'low' e 'high'
 * utilizando o valor do nó 'high' como pivô. Os nós são reorganizados de modo
 * que os elementos menores ou iguais ao pivô fiquem à esquerda e os maiores à direita.
 * O ponteiro para o novo pivô (posição final do pivô) é retornado.
 *
 * @param low O primeiro nó da lista a ser particionada.
 * @param high O último nó da lista a ser particionado (pivô).
 * @return O ponteiro para o novo pivô após a partição.
 */
NodeL* partition(NodeL* low, NodeL* high) {
  NodeL* pivot = medianOfThree(low, high);
  obj pivotValue = pivot->info;
  objSwap(&pivot->info, &high->info);   
  NodeL* i = low->ant;  
  for (NodeL* j = low; j != high; j = j->prox) {
    if (objCmp(j->info, pivotValue) <= 0) {
      i = (i == NULL) ? low : i->prox;
      objSwap(&i->info, &j->info);
    }
  }
  i = (i == NULL) ? low : i->prox;
  objSwap(&i->info, &high->info);
  return i;
}

/**
 * @brief Realiza a ordenação introspectiva de uma lista encadeada.
 *
 * A função utiliza uma combinação de Quick Sort e Heap Sort para ordenar a lista
 * encadeada entre os nós 'low' e 'high'. A profundidade da recursão é limitada por
 * 'depthLimit'. Quando o limite é atingido, a função recorre ao Heap Sort para
 * completar a ordenação. Se ocorrer um erro durante a ordenação, a função retorna -1;
 * caso contrário, retorna 0 ao final do processo.
 *
 * @param low O primeiro nó da lista a ser ordenada.
 * @param high O último nó da lista a ser ordenada.
 * @param depthLimit O limite de profundidade para a recursão.
 * @return 0 se a ordenação for bem-sucedida ou -1 se ocorrer um erro.
 */
void introSort(NodeL* low, NodeL* high, int depthLimit) {
  const int insertionLimit = 16;
  while (high && low != high && low != high->prox) {
    int size = 0;
    for (NodeL* temp = low; temp != high->prox; temp = temp->prox) size++;
    if (size < insertionLimit) {
      insertionSort(low, high);
      return;
    }
    if (depthLimit == 0) {
      heapSort(low, high);
      return;
    }
    NodeL* p = partition(low, high);
    depthLimit--;
    introSort(low, p->ant, depthLimit);
    low = p->prox;
  }
}

/**
 * @brief Ordena uma lista encadeada usando o algoritmo Quick Sort.
 *
 * A função calcula o número de elementos na lista encadeada entre os nós 
 * 'low' e 'high', e determina um limite de profundidade para a recursão 
 * com base no número de elementos. Em seguida, chama a função 'introSort'
 * para realizar a ordenação. Se a ordenação falhar, a função retorna -1;
 * caso contrário, retorna 0 ao final do processo.
 *
 * @param low O primeiro nó da lista a ser ordenada.
 * @param high O último nó da lista a ser ordenada.
 * @return 0 se a ordenação for bem-sucedida ou -1 se ocorrer um erro.
 */
int quickSort(NodeL* low, NodeL* high) {
  int n = 0;
  for (NodeL* temp = low; temp != high->prox; temp = temp->prox) n++;
  int depthLimit = 2 * (int)log2(n); 
  introSort(low, high, depthLimit);
  return 0;  
}

/**
 * @brief Ordena uma lista encadeada usando o algoritmo Quick Sort.
 *
 * A função verifica se a lista está vazia ou contém um único elemento. 
 * Se a lista tiver um número válido de elementos, a função obtém o último 
 * nó (tail) e chama a função 'quickSort' para ordenar a lista encadeada 
 * entre o primeiro nó (head) e o último nó (tail). Se a ordenação falhar, 
 * uma mensagem de erro é exibida no stderr.
 *
 * @param lst A lista a ser ordenada.
 * @return A lista ordenada, ou a mesma lista se estiver vazia ou contendo um único elemento.
 */
list listSort(list lst) {
  if (listIsEmpty(lst) || lst->N <= 1) return lst;
  NodeL* high = lst->tail;
  if (quickSort(lst->head, high) != 0) fprintf(stderr, "</>A ordenação falhou</>\n");
  return lst;
} 

/**
 * @brief Mescla duas listas encadeadas ordenadas em uma única lista ordenada.
 *
 * A função verifica se uma das listas está vazia e, se estiver, retorna a outra 
 * lista. Caso ambas as listas estejam preenchidas, uma nova lista é criada para 
 * armazenar os elementos mesclados. A função percorre as duas listas, comparando 
 * os elementos e adicionando-os à lista resultante em ordem. Após adicionar todos 
 * os elementos de uma lista, o restante dos elementos da outra lista também é 
 * adicionado à lista mesclada.
 *
 * @param lst1 A primeira lista a ser mesclada.
 * @param lst2 A segunda lista a ser mesclada.
 * @return A lista mesclada ordenada, ou NULL se a alocação de memória falhar.
 */
list listMerge(const list lst1, const list lst2) {
  if (lst1 == NULL || lst1->head == NULL) return lst2;
  if (lst2 == NULL || lst2->head == NULL) return lst1;
  list mergedList = listNew(); 
  if (mergedList == NULL) return NULL; 
  NodeL* aux1 = lst1->head;
  NodeL* aux2 = lst2->head;
  while (aux1 != NULL && aux2 != NULL) {
    if (objCmp(aux1->info, aux2->info) <= 0) {
      listPushBack(mergedList, aux1->info);
      aux1 = aux1->prox;
    } else {
      listPushBack(mergedList, aux2->info);
      aux2 = aux2->prox;
    }
  }
  while (aux1 != NULL) {
    listPushBack(mergedList, aux1->info);
    aux1 = aux1->prox;
  }
  while (aux2 != NULL) {
    listPushBack(mergedList, aux2->info);
    aux2 = aux2->prox;
  }
  return mergedList;
}
 
/**
 * @brief Converte uma lista encadeada em uma representação de string.
 *
 * A função verifica se a lista está vazia e, se estiver, retorna NULL. 
 * Caso contrário, ela inicializa uma nova string e adiciona um colchete 
 * de abertura. A função percorre a lista, convertendo cada elemento 
 * em uma string e adicionando-os à string resultante, separados por vírgulas.
 * Quando todos os elementos foram processados, um colchete de fechamento 
 * é adicionado. A string resultante representa a lista encadeada em um formato 
 * legível.
 *
 * @param lst A lista a ser convertida em string.
 * @return A representação de string da lista, ou NULL se a lista estiver vazia.
 */
string listToString(const list lst) {
  if (listIsEmpty(lst)) return NULL;
  NodeL* aux = lst->head;
  string str = stringNew();
  stringAddChar(str, '[');
  while (aux != NULL) {
    string temp = objToString(aux->info);
    str = stringAppend(str, temp);
    stringFree(temp);
    if (aux->prox != NULL) str = stringCat(str, ", ");
    aux = aux->prox;
  }
  stringAddChar(str, ']');
  return str;
}

/**
 * @brief Exibe a representação em string de uma lista encadeada.
 *
 * A função verifica se a lista está vazia e, se estiver, retorna 0. 
 * Caso contrário, a função chama 'listToString' para obter a representação 
 * da lista em forma de string e, em seguida, utiliza 'stringPrint' para 
 * exibi-la. Após a impressão, a string resultante é destruída para liberar 
 * a memória. Se a impressão for bem-sucedida, a função retorna 1.
 *
 * @param lst A lista a ser exibida.
 * @return 1 se a impressão foi bem-sucedida ou 0 se a lista estiver vazia.
 */
int listPrint(const list lst) {
  if (listIsEmpty(lst)) return 0;
  string str = listToString(lst);
  if (str == NULL) return 0;
  stringPrint(str);
  stringFree(str);
  return 1;
}  