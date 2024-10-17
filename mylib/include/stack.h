/**
 * @file Stack.h
 * @brief Implementação de uma Pilha Genérica em C.
 * 
 * Este arquivo contém a implementação de uma pilha genérica que permite armazenar elementos de qualquer tipo.
 * A pilha é estruturada de forma que os elementos sejam empilhados e desempilhados no modo LIFO (Last In, First Out).
 * 
 * Funções disponíveis:
 * - `stackNew`: Cria uma nova pilha.
 * - `stackDestroy`: Destrói a pilha, liberando toda a memória alocada.
 * - `stackIsEmpty`: Verifica se a pilha está vazia.
 * - `stackSize`: Retorna o número de elementos na pilha.
 * - `stackPush`: Empilha um novo elemento no topo da pilha.
 * - `stackPop`: Remove o elemento no topo da pilha.
 * - `stackTop`: Consulta o elemento no topo da pilha sem removê-lo.
 * - `stackPrint`: Printa todos os elementos da pilha.
 * 
 * Esta implementação permite armazenar dados de qualquer tipo, desde que seja informado o tamanho do tipo (via `sizeof(tipo)`)
 * no momento da criação da pilha. As operações suportadas incluem empilhar, desempilhar, consultar o topo e verificar o tamanho.
 * 
 * @note A pilha é uma estrutura dinâmica, e todas as operações que envolvem adição ou remoção de elementos ajustam a memória
 * conforme necessário.
 * 
 * @author Victor Gabriel Barbosa
 * @date 12/10/2024
 * @version 1.0
 */
#ifndef STACK_H
#define STACK_H 

#include <typeslib.h>

/**
 * @brief Cria uma nova pilha ou retorna a pilha existente.
 * 
 * @return Stack Retorna um ponteiro para a nova pilha.
 */
Stack stackNew();

/**
 * @brief Destrói a pilha, liberando a memória alocada.
 * 
 * @param stk Ponteiro para a pilha que será destruída.
 * @return Stack Retorna NULL para indicar que a pilha foi destruída.
 */
Stack stackDestroy(Stack stk);

/**
 * @brief Verifica se a pilha está vazia.
 * 
 * @param stk Ponteiro para a pilha.
 * @return int Retorna 1 se a pilha estiver vazia, 0 caso contrário.
 */
int stackIsEmpty(Stack stk);

/**
 * @brief Retorna o tamanho atual da pilha.
 * 
 * @param stk Ponteiro para a pilha.
 * @return size_t Tamanho da pilha (número de elementos).
 */
size_t stackSize(Stack stk);

/**
 * @brief Adiciona um novo elemento no topo da pilha.
 * 
 * @param stk Ponteiro para a pilha.
 * @param info Valor a ser empilhado.
 * @return Stack Retorna um ponteiro para a pilha atualizada, ou NULL em caso de falha.
 */
Stack stackPush(Stack stk, Auto info);

/**
 * @brief Remove o elemento do topo da pilha.
 * 
 * @param stk Ponteiro para a pilha.
 * @param info Ponteiro onde será armazenado o valor removido do topo.
 * @return Stack Retorna o ponteiro da pilha, ou NULL se a pilha estiver vazia.
 */
Stack stackPop(Stack stk, Auto *info);

/**
 * @brief Consulta o elemento no topo da pilha sem removê-lo.
 * 
 * @param stk Ponteiro para a pilha.
 * @param info Ponteiro onde será armazenado o valor do topo da pilha.
 * @return int Retorna 1 se a operação foi bem-sucedida, ou 0 se a pilha estiver vazia.
 */
int stackTop(Stack stk, Auto *info);

/** 
* @brief Printa todos os elementos de uma pilha.
*
* @param qeu Ponteiro para a pilha.
* @return 1 se a pilha não é vazia, 0 caso contrário.
*/
int stackPrint(Stack stk);
 
#endif