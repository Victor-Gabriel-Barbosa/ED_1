/**
 * @file stack.h
 * @brief Implementação de uma Pilha Genérica em C.
 * 
 * Este arquivo contém a implementação de uma pilha genérica que permite armazenar elementos de qualquer tipo.
 * A pilha é estruturada de forma que os elementos sejam empilhados e desempilhados no modo LIFO (Last In, First Out).
 * 
 * Funções disponíveis:
 * - 'stackNew': Cria uma nova pilha.
 * - 'stackDestroy': Destrói a pilha, liberando toda a memória alocada.
 * - 'stackIsEmpty': Verifica se a pilha está vazia.
 * - 'stackSize': Retorna o número de elementos na pilha.
 * - 'stackPush': Empilha um novo elemento no topo da pilha.
 * - 'stackPop': Remove o elemento no topo da pilha.
 * - 'stackTop': Consulta o elemento no topo da pilha sem removê-lo.
 * - 'stackPrint': Printa todos os elementos da pilha.
 * 
 * Esta implementação permite armazenar dados de qualquer tipo, desde que seja informado o tamanho do tipo (via 'sizeof(tipo)')
 * no momento da criação da pilha. As operações suportadas incluem empilhar, desempilhar, consultar o topo e verificar o tamanho.
 * 
 * @note A pilha é uma estrutura dinâmica, e todas as operações que envolvem adição ou remoção de elementos ajustam a memória
 * conforme necessário.
 * 
 * @author Victor Gabriel Barbosa
 * @date 20/10/2024
 * @version 2.0
 */
#ifndef STACK_H
#define STACK_H 

#include <typeslib.h>

/**
 * @brief Cria uma nova pilha.
 * 
 * @return Objeto para a nova pilha.
 */
stack stackNew();

/**
 * @brief Destrói a pilha, liberando a memória alocada.
 * 
 * @param stk Objeto para a pilha que será destruída.
 * @return NULL para indicar que a pilha foi destruída.
 */
stack stackDestroy(stack stk);

/**
 * @brief Verifica se a pilha está vazia.
 * 
 * @param stk Objeto para a pilha.
 * @return 1 se a pilha estiver vazia, 0 caso contrário.
 */
int stackIsEmpty(stack stk);

/**
 * @brief Retorna o tamanho atual da pilha.
 * 
 * @param stk Objeto para a pilha.
 * @return size_t Tamanho da pilha (número de elementos).
 */
size_t stackSize(stack stk);

/**
 * @brief Adiciona um novo elemento no topo da pilha.
 * 
 * @param stk Objeto para a pilha.
 * @param info Valor a ser empilhado.
 * @return Objeto para a pilha atualizada, ou NULL em caso de falha.
 */
stack stackPush(stack stk, obj info);

/**
 * @brief Remove o elemento do topo da pilha.
 * 
 * @param stk Objeto para a pilha.
 * @param info Ponteiro onde será armazenado o valor removido do topo (obj).
 * @return Objeto para a pilha, ou NULL se a pilha estiver vazia.
 */
stack stackPop(stack stk, obj* info);

/**
 * @brief Consulta o elemento no topo da pilha sem removê-lo.
 * 
 * @param stk Objeto para a pilha.
 * @param info Ponteiro onde será armazenado o valor do topo da pilha (obj).
 * @return 1 se a operação foi bem-sucedida, ou 0 se a pilha estiver vazia.
 */
int stackTop(stack stk, obj* info);

/**
 * Compara duas pilhas (stack).
 * 
 * @param stk1 A primeira pilha a ser comparada.
 * @param stk2 A segunda pilha a ser comparada.
 * 
 * @return 
 * - 1 se stk1 for maior que stk2 (em termos de tamanho ou conteúdo),
 * - -1 se stk2 for maior que stk1,
 * - 0 se ambas as pilha forem iguais.
 */
int stackCmp(stack stk1, stack stk2);

/**
 * @brief Converte uma pilha para uma string.
 * 
 * @param stk Pilha a ser convertida.
 * @return string da pilha convertida.
 */
string stackToString(stack stk);

/** 
* @brief Exibe todos os elementos de uma pilha.
*
* @param qeu Objeto para a pilha.
* @return 1 se a pilha não é vazia, 0 caso contrário.
*/
int stackPrint(stack stk);
 
#endif