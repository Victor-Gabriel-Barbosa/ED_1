#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h> 
#include <string.h>
#include <stringlib.h>
#include <typeslib.h>
#include <list.h>

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
list listDestroy(list lst) {
  if (lst == NULL) return NULL; 
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
 * @brief Verifica se uma lista encadeada está vazia.
 *
 * A função verifica se a lista é nula ou se a cabeça da lista é nula, 
 * indicando que a lista não contém elementos. Retorna 1 se a lista estiver 
 * vazia e 0 caso contrário.
 *
 * @param lst A lista a ser verificada.
 * @return 1 se a lista estiver vazia, 0 caso contrário.
 */
int listIsEmpty(list lst) {
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
size_t listSize(list lst) { 
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
  if (aux->info != NULL) aux->info = objDestroy(aux->info);
  free(aux);
  lst->N--;
  return lst;
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
 * @brief Retorna o objeto armazenado em uma posição específica da lista.
 *
 * A função acessa o nó na posição 'pos' da lista e retorna o objeto armazenado
 * nesse nó. Se a lista estiver vazia ou a posição for inválida, a função retorna NULL.
 *
 * @param lst A lista da qual se deseja obter o objeto.
 * @param pos A posição do nó de onde o objeto será obtido (de 0 a N-1).
 * @return O objeto armazenado no nó na posição especificada ou NULL se a posição for inválida.
 */
obj listGet(list lst, const int pos) {
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
 * @brief Troca os valores de dois objetos.
 *
 * A função recebe ponteiros para dois objetos 'a' e 'b' e troca seus valores.
 * Se algum dos ponteiros for nulo, a troca não é realizada e a função retorna 0.
 * Caso contrário, a troca é efetuada e a função retorna 1.
 *
 * @param a Ponteiro para o primeiro objeto a ser trocado.
 * @param b Ponteiro para o segundo objeto a ser trocado.
 * @return 1 se a troca for bem-sucedida, ou 0 se algum ponteiro for nulo.
 */
int swap(obj* a, obj* b) {
  if (a == NULL || b == NULL) return 0; 
  obj temp = *a;
  *a = *b;
  *b = temp;
  return 1;
}

/**
 * @brief Reorganiza um subárvore para manter a propriedade do heap.
 *
 * A função ajusta um subárvore com raiz no índice 'i' de um array de nós 
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
    swap(&arr[i]->info, &arr[largest]->info);
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
  if (quickSort(lst->head, high) != 0) fprintf(stderr, "Error: listSort failed");
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
int listPrint(list lst) {
  if (listIsEmpty(lst)) return 0;
  string str = listToString(lst);
  stringPrint(str);
  stringDestroy(str);
  return 1;
}  