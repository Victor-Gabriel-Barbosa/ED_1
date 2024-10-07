#ifndef STACK_H
#define STACK_H 

#include <stddef.h>

/**
 * @brief Estrutura para representar uma pilha
 */
typedef struct stack *Stack;

/**
 * @brief Cria uma nova pilha ou retorna a pilha existente.
 * 
 * @return Stack Retorna um ponteiro para a nova pilha.
 */
Stack newStack();

/**
 * @brief Destroi a pilha, liberando a memória alocada.
 * 
 * @param stk Ponteiro para a pilha que será destruída.
 * @return Stack Retorna NULL para indicar que a pilha foi destruída.
 */
Stack destroyStack(Stack stk);

/**
 * @brief Verifica se a pilha está vazia.
 * 
 * @param stk Ponteiro para a pilha.
 * @return int Retorna 1 se a pilha estiver vazia, 0 caso contrário.
 */
int isStackEmpty(Stack stk);

/**
 * @brief Retorna o tamanho atual da pilha.
 * 
 * @param stk Ponteiro para a pilha.
 * @return size_t Tamanho da pilha (número de elementos).
 */
size_t sizeStack(Stack stk);

/**
 * @brief Adiciona um novo elemento no topo da pilha.
 * 
 * @param stk Ponteiro para a pilha.
 * @param info Valor a ser empilhado.
 * @return Stack Retorna um ponteiro para a pilha atualizada, ou NULL em caso de falha.
 */
Stack push(Stack stk, int info);

/**
 * @brief Remove o elemento do topo da pilha.
 * 
 * @param stk Ponteiro para a pilha.
 * @param info Ponteiro onde será armazenado o valor removido do topo.
 * @return Stack Retorna o ponteiro da pilha, ou NULL se a pilha estiver vazia.
 */
Stack pop(Stack stk, int *info);

/**
 * @brief Consulta o elemento no topo da pilha sem removê-lo.
 * 
 * @param stk Ponteiro para a pilha.
 * @param info Ponteiro onde será armazenado o valor do topo da pilha.
 * @return int Retorna 1 se a operação foi bem-sucedida, ou 0 se a pilha estiver vazia.
 */
int top(Stack stk, int *info);

/**
 * @brief Exibe todos os elementos da pilha.
 * 
 * @param stk Ponteiro para a pilha.
 * @return int Retorna 1 em caso de sucesso, ou 0 em caso de falha.
 */
int printStack(Stack stk);

#endif