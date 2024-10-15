#include <stdio.h>
#include <stdlib.h> 
#include <stdarg.h>
#include <string.h>
#include <stack.h>
#include <stringlib.h>

/**
 * @brief Estrutura do nó da pilha.
 * 
 * Cada nó contém um valor `info` e um ponteiro para o próximo nó da pilha.
 */
typedef struct nodeS {
  void *info;
  struct nodeS *prox; 
} NodeS;

/**
 * @brief Estrutura da pilha (Stack).
 * 
 * A pilha contém um ponteiro para o topo ('top') e o tamanho ('size')
 */
typedef struct stack {
  NodeS *top;
  size_t N;
  DataType type;
  size_t sizeType;
} *Stack;

/**
 * @brief Cria uma nova pilha ou retorna a pilha existente.
 * 
 * @param type O tipo de dados que serão armazenados na pilha.
 * @param sizeType O tamanho do tipo de dados que serão armazenados na pilha. 
 * @return Ponteiro para a nova pilha ou para a pilha já existente.
 */
Stack stackNew(DataType type, size_t sizeType) { 
  Stack stk = (Stack)malloc(sizeof(struct stack));
  if (stk == NULL) return stk; 
  stk->top = NULL;
  stk->N = 0;
  stk->type = type;
  stk->sizeType = sizeType;  
  return stk;
} 

/**
 * @brief Destrói a pilha, liberando a memória alocada.
 * 
 * @param stk Ponteiro para a pilha que será destruída.
 * @return NULL para indicar que a pilha foi destruída.
 */
Stack stackDestroy(Stack stk) {
  if (stk == NULL) return NULL;
  NodeS *aux = stk->top;
  while (aux != NULL) {
    NodeS *temp = aux->prox;
    if (aux->info != NULL) free(aux->info);
    free(aux);
    aux = temp;
  }
  free(stk); 
  return NULL; 
}

/**
 * @brief Verifica se a pilha está vazia.
 * 
 * @param stk Ponteiro para a pilha.
 * @return 1 se a pilha estiver vazia, 0 caso contrário.
 */
int stackIsEmpty(Stack stk) {
  return (stk == NULL || stk->top == NULL);
}  

/**
 * @brief Retorna o tamanho atual da pilha.
 * 
 * @param stk Ponteiro para a pilha.
 * @return amanho da pilha (número de elementos).
 */
size_t stackSize(Stack stk) {
  return (stk == NULL) ? 0 : stk->N;
}

/**
 * @brief Adiciona um novo elemento no topo da pilha.
 * 
 * @param stk Ponteiro para a pilha.
 * @param info Valor a ser empilhado.
 * @return Retorna um ponteiro para a pilha atualizada, ou NULL em caso de falha.
 */
Stack stackPush(Stack stk, void *info) {
  if (stk == NULL) return stk;
  NodeS *newNode = (NodeS *)malloc(sizeof(NodeS));
  if (newNode == NULL) return stk;
  newNode->info = malloc(stk->sizeType);
  if (newNode->info == NULL) {
    free(newNode);
    return stk;
  }
  memcpy(newNode->info, info, stk->sizeType);
  newNode->prox = stk->top;
  stk->top = newNode;
  stk->N++;
  return stk;
}

/**
 * @brief Remove o elemento do topo da pilha.
 * 
 * @param stk Ponteiro para a pilha.
 * @param info Ponteiro onde será armazenado o valor removido do topo.
 * @return Retorna o ponteiro da pilha, ou NULL se a pilha estiver vazia.
 */
Stack stackPop(Stack stk, void *info) {
  if (stackIsEmpty(stk)) return stk;
  NodeS *temp = stk->top;
  memcpy(info, temp->info, stk->sizeType);
  stk->top = temp->prox;
  free(temp); 
  stk->N--;
  return stk;
} 

/**
 * @brief Consulta o elemento no topo da pilha sem removê-lo.
 * 
 * @param stk Ponteiro para a pilha.
 * @param info Ponteiro onde será armazenado o valor do topo da pilha.
 * @return int Retorna 1 se a operação foi bem-sucedida, ou 0 se a pilha estiver vazia.
 */
int top(Stack stk, void *info) {
  if (stackIsEmpty(stk)) return 0;
  memcpy(info, stk->top->info, stk->sizeType);
  return 1;
}

/** 
* @brief Printa todos os elementos de uma pilha.
*
* @param qeu Ponteiro para a pilha.
* @return 1 se a pilha não é vazia, 0 caso contrário.
*/
int stackPrint(Stack stk) {
  if (stackIsEmpty(stk)) return 0;
  NodeS *aux = stk->top;
  while (aux != NULL) {
    stringPrint(toString(aux->info, stk->type, stk->sizeType));
    printf(" ");
    aux = aux->prox;
  }
  return 1;
}  