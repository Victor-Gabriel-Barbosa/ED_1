#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da lista encadeada
typedef struct NodeL {
  int info;
  struct NodeL* prox;
} NodeL;

/**
 * @brief Cria um novo nó com o valor especificado.
 *
 * @param valor O valor a ser armazenado no nó.
 * @return Um ponteiro para o novo nó.
 */
NodeL* criarNo(int valor) {
  NodeL* novoNo = (NodeL*)malloc(sizeof(NodeL));
  if (novoNo != NULL) {
    novoNo->info = valor;
    novoNo->prox = NULL;
  }
  return novoNo;
}

/**
 * @brief Adiciona um novo nó ao final da lista.
 *
 * @param inicio Ponteiro para o ponteiro do primeiro nó da lista.
 * @param valor O valor a ser adicionado.
 */
void adicionarNo(NodeL** inicio, int valor) {
  NodeL* novoNo = criarNo(valor);
  if (*inicio == NULL) {
    *inicio = novoNo;
  } else {
    NodeL* temp = *inicio;
    while (temp->prox != NULL) {
      temp = temp->prox;
    }
    temp->prox = novoNo;
  }
}

/**
 * @brief Imprime todos os elementos da lista encadeada.
 *
 * @param inicio O primeiro nó da lista.
 */
void imprimirLista(NodeL* inicio) {
  NodeL* temp = inicio;
  while (temp != NULL) {
    printf("%d ", temp->info);
    temp = temp->prox;
  }
  printf("\n");
}

/**
 * @brief Reorganiza uma subárvore para manter a propriedade do heap.
 *
 * @param vetor O array de nós a ser reorganizado.
 * @param n O tamanho do array.
 * @param i O índice do nó que será ajustado.
 */
void heapify(NodeL** vetor, int n, int i) {
  int maior = i;
  int esquerda = 2 * i + 1;
  int direita = 2 * i + 2;

  if (esquerda < n && vetor[esquerda]->info > vetor[maior]->info) maior = esquerda;
  if (direita < n && vetor[direita]->info > vetor[maior]->info) maior = direita;

  if (maior != i) {
    int temp = vetor[i]->info;
    vetor[i]->info = vetor[maior]->info;
    vetor[maior]->info = temp;
    heapify(vetor, n, maior);
  }
}

/**
 * @brief Ordena uma lista encadeada usando o algoritmo Heap Sort.
 *
 * @param inicio O primeiro nó da lista que será ordenada.
 * @param fim O último nó da lista que será ordenada.
 * @return 0 se a ordenação for bem-sucedida ou -1 se ocorrer um erro de alocação de memória.
 */
int heapSort(NodeL* inicio, NodeL* fim) {
  if (inicio == NULL || fim == NULL) return -1;

  int n = 0;
  NodeL* temp = inicio;
  while (temp != fim->prox) {
    n++;
    temp = temp->prox;
  }

  NodeL** vetor = malloc(n * sizeof(NodeL*));
  if (vetor == NULL) return -1;

  temp = inicio;
  for (int i = 0; i < n; i++) {
    vetor[i] = temp;
    temp = temp->prox;
  }

  for (int i = n / 2 - 1; i >= 0; i--) heapify(vetor, n, i);
  for (int i = n - 1; i >= 0; i--) {
    int aux = vetor[0]->info;
    vetor[0]->info = vetor[i]->info;
    vetor[i]->info = aux;
    heapify(vetor, i, 0);
  }

  free(vetor);
  return 0;
}

/**
 * @brief Retorna o último nó da lista encadeada.
 *
 * @param inicio O primeiro nó da lista.
 * @return O último nó da lista.
 */
NodeL* obterUltimoNo(NodeL* inicio) {
  NodeL* temp = inicio;
  while (temp->prox != NULL) {
    temp = temp->prox;
  }
  return temp;
}

int main() {
  NodeL* lista = NULL;

  // Adicionando elementos à lista
  adicionarNo(&lista, 5);
  adicionarNo(&lista, 3);
  adicionarNo(&lista, 8);
  adicionarNo(&lista, 1);
  adicionarNo(&lista, 7);

  printf("Lista antes da ordenação:\n");
  imprimirLista(lista);

  NodeL* ultimoNo = obterUltimoNo(lista);
  heapSort(lista, ultimoNo);

  printf("Lista após a ordenação:\n");
  imprimirLista(lista);

  NodeL* temp;
  while (lista != NULL) {
    temp = lista;
    lista = lista->prox;
    free(temp);
  }

  return 0;
}
