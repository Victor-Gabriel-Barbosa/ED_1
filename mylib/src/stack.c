#include <stdio.h>
#include <stdlib.h> 
#include <stdarg.h>
#include "stack.h"

/**
 * @brief Estrutura do nó da pilha.
 * 
 * Cada nó contém um valor `info` e um ponteiro para o próximo nó da pilha.
 */
typedef struct nodeS {
  int data;
  struct nodeS *next; 
} NodeS;

/**
 * @brief Estrutura da pilha (Stack).
 * 
 * A pilha contém um ponteiro para o topo ('top') e o tamanho ('size')
 */
typedef struct stack {
  NodeS *top;
  size_t size;
} *Stack;

/**
 * @brief Cria uma nova pilha ou retorna a pilha existente.
 * 
 * @param stk Ponteiro para a pilha existente (ou NULL para criar uma nova).
 * @return Stack Retorna um ponteiro para a nova pilha ou para a pilha já existente.
 */
Stack newStack() { 
  Stack stk = (Stack)malloc(sizeof(struct stack));
  if (stk == NULL) return stk; 
  stk->top = NULL;
  stk->size = 0;
  return stk;
} 

/**
 * @brief Destroi a pilha, liberando a memória alocada.
 * 
 * @param stk Ponteiro para a pilha que será destruída.
 * @return Stack Retorna NULL para indicar que a pilha foi destruída.
 */
Stack destroyStack(Stack stk) {
  if (stk == NULL) return stk;
  NodeS *current = stk->top;
  while (current != NULL) {
    NodeS *next = current->next;
    free(current); // Libera cada nó
    current = next;
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
int isStackEmpty(Stack stk) {
  return (stk == NULL || stk->top == NULL);
}

/**
 * @brief Retorna o tamanho atual da pilha.
 * 
 * @param stk Ponteiro para a pilha.
 * @return size_t Tamanho da pilha (número de elementos).
 */
size_t sizeStack(Stack stk) {
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
Stack push(Stack stk, int info) {
  if (stk == NULL) return stk;
  NodeS *newNode = (NodeS *)malloc(sizeof(NodeS));
  if (newNode == NULL) return stk;
  newNode->data = info;
  newNode->next = stk->top;
  stk->top = newNode;
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
Stack pop(Stack stk, int *info) {
  if (isStackEmpty(stk)) return stk;
  NodeS *temp = stk->top;
  *info = temp->data;
  stk->top = temp->next;
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
int top(Stack stk, int *info) {
  if (isStackEmpty(stk)) return 0;
  *info = stk->top->data;
  return 1;
}

/**
 * @brief Exibe todos os elementos da pilha.
 * 
 * @param stk Ponteiro para a pilha.
 * @return int Retorna 1 em caso de sucesso, ou 0 em caso de falha.
 */
int printStack(Stack stk) {
  if (isStackEmpty(stk)) return 0;
  NodeS *current = stk->top;
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  return 1;
}