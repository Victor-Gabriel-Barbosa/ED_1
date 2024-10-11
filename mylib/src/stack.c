#include <stdio.h>
#include <stdlib.h> 
#include <stdarg.h>
#include <string.h>
#include "stack.h"

/**
 * @brief Estrutura do nó da pilha.
 * 
 * Cada nó contém um valor `info` e um ponteiro para o próximo nó da pilha.
 */
typedef struct nodeS {
  void *info;
  struct nodeS *next; 
} NodeS;

/**
 * @brief Estrutura da pilha (Stack).
 * 
 * A pilha contém um ponteiro para o topo ('stackTop') e o tamanho ('size')
 */
typedef struct stack {
  NodeS *stackTop;
  size_t size;
  size_t sizeTip;
} *Stack;

/**
 * @brief Cria uma nova pilha ou retorna a pilha existente.
 * 
 * @param sizeTip O tamanho do tipo de dado que será armazenado na pilha. 
 * @return Stack Retorna um ponteiro para a nova pilha ou para a pilha já existente.
 */
Stack stackNew(size_t sizeTip) { 
  Stack stk = (Stack)malloc(sizeof(struct stack));
  if (stk == NULL) return stk; 
  stk->sizeTip = sizeTip;  
  stk->stackTop = NULL;
  stk->size = 0;
  return stk;
} 

/**
 * @brief Destrói a pilha, liberando a memória alocada.
 * 
 * @param stk Ponteiro para a pilha que será destruída.
 * @return Stack Retorna NULL para indicar que a pilha foi destruída.
 */
Stack stackDestroy(Stack stk) {
  if (stk == NULL) return stk;
  NodeS *aux = stk->stackTop;
  while (aux != NULL) {
    NodeS *temp = aux->next;
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
 * @return int Retorna 1 se a pilha estiver vazia, 0 caso contrário.
 */
int stackIsEmpty(Stack stk) {
  return (stk == NULL || stk->stackTop == NULL);
}

/**
 * @brief Retorna o tamanho atual da pilha.
 * 
 * @param stk Ponteiro para a pilha.
 * @return size_t Tamanho da pilha (número de elementos).
 */
size_t stackSize(Stack stk) {
  if (stk == NULL) return 0;
  return stk->size;
}

/**
 * @brief Adiciona um novo elemento no topo da pilha.
 * 
 * @param stk Ponteiro para a pilha.
 * @param info Valor a ser empilhado.
 * @return Stack Retorna um ponteiro para a pilha atualizada, ou NULL em caso de falha.
 */
Stack stackPush(Stack stk, void *info) {
  if (stk == NULL) return stk;
  NodeS *newNode = (NodeS *)malloc(sizeof(NodeS));
  if (newNode == NULL) return stk;
  newNode->info = malloc(stk->sizeTip);
  if (newNode->info == NULL) {
    free(newNode);
    return stk;
  }
  memcpy(newNode->info, info, stk->sizeTip);
  newNode->next = stk->stackTop;
  stk->stackTop = newNode;
  stk->size++;
  return stk;
}

/**
 * @brief Remove o elemento do topo da pilha.
 * 
 * @param stk Ponteiro para a pilha.
 * @param info Ponteiro onde será armazenado o valor removido do topo.
 * @return Stack Retorna o ponteiro da pilha, ou NULL se a pilha estiver vazia.
 */
Stack stackPop(Stack stk, void *info) {
  if (stackIsEmpty(stk)) return stk;
  NodeS *temp = stk->stackTop;
  memcpy(info, temp->info, stk->sizeTip);
  stk->stackTop = temp->next;
  free(temp); 
  stk->size--;
  return stk;
} 

/**
 * @brief Consulta o elemento no topo da pilha sem removê-lo.
 * 
 * @param stk Ponteiro para a pilha.
 * @param info Ponteiro onde será armazenado o valor do topo da pilha.
 * @return int Retorna 1 se a operação foi bem-sucedida, ou 0 se a pilha estiver vazia.
 */
int stackTop(Stack stk, void *info) {
  if (stackIsEmpty(stk)) return 0;
  memcpy(info, stk->stackTop->info, stk->sizeTip);
  return 1;
}