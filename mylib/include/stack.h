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
 * @return Um ponteiro para a nova pilha, ou NULL se a alocação de memória falhar.
 */
stack stackNew();


/**
 * @brief Destrói uma pilha e libera a memória associada a ela.
 * 
 * @param stk Ponteiro para a pilha a ser destruída.
 * @return 'NULL' após liberar a pilha.
 */
stack stackDestroy(stack stk);

/**
 * @brief Verifica se a pilha está vazia.
 * 
 * @param stk Ponteiro para a pilha a ser verificada.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int stackIsEmpty(stack stk);

/**
 * @brief Obtém o tamanho da pilha.
 * 
 * @param stk Ponteiro para a pilha cuja quantidade de elementos deve ser verificada.
 * @return O número de elementos na pilha. Retorna 0 se a pilha for NULL'.
 */
size_t stackSize(stack stk);

/**
 * @brief Adiciona um elemento à pilha.
 *
 * @param stk Ponteiro para a pilha onde o elemento deve ser adicionado.
 * @param info O elemento a ser adicionado à pilha.
 * @return Ponteiro para a pilha atualizada, ou a pilha inalterada se estiver vazia.
 */
stack stackPush(stack stk, obj info);

/**
 * @brief Obtém o elemento do topo da pilha.
 * 
 * @param stk Ponteiro para a pilha da qual o elemento do topo deve ser recuperado.
 * @param info Ponteiro para a variável onde o elemento do topo será armazenado.
 * @return 1 se a operação for bem-sucedida, ou 0 se a pilha estiver vazia.
 */
int stackTop(stack stk, obj* info);

/**
 * @brief Remove e retorna o elemento do topo da pilha.
 * 
 * @param stk Ponteiro para a pilha da qual o elemento do topo deve ser removido.
 * @param info Ponteiro para a variável onde o elemento removido será armazenado.
 * @return Ponteiro para a pilha atualizada, ou a pilha inalterada se estiver vazia.
 */
stack stackPop(stack stk, obj* info);

/**
 * @brief Compara duas pilhas.
 * 
 * @param stk1 Ponteiro para a primeira pilha a ser comparada.
 * @param stk2 Ponteiro para a segunda pilha a ser comparada.
 * @return 0 se as pilhas forem iguais, -1 se a primeira pilha for menor, 1 se a primeira pilha for maior
 */
int stackCmp(stack stk1, stack stk2);

/**
 * @brief Converte uma pilha em uma representação de string.
 * 
 * @param stk Ponteiro para a pilha a ser convertida em string.
 * @return Uma string representando a pilha, ou NULL se a pilha estiver vazia.
 */
string stackToString(stack stk);

/**
 * @brief Imprime os elementos da pilha.
 * 
 * @param stk Ponteiro para a pilha a ser impressa.
 * @return 1 se a pilha foi impressa com sucesso, ou 0 se a pilha estiver vazia.
 */
int stackPrint(stack stk);
 
#endif