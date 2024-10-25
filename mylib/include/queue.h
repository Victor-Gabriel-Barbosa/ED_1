/**
 * @file queue.h
 * @brief Implementação de uma Fila Genérica em C.
 * 
 * Este arquivo contém a implementação de uma fila genérica que permite armazenar elementos de qualquer tipo.
 * A fila segue o modelo FIFO (First In, First Out), onde o primeiro elemento inserido é o primeiro a ser removido.
 * 
 * Funções disponíveis:
 * - 'queueNew': Cria uma nova fila.
 * - 'queueDestroy': Destrói a fila, liberando a memória alocada.
 * - 'queueIsEmpty': Verifica se a fila está vazia.
 * - 'queueSize': Retorna o número de elementos na fila.
 * - 'queueEnqueue': Adiciona um novo elemento ao final da fila.
 * - 'queueDequeue': Remove um elemento do início da fila.
 * - 'queueFront': Consulta o elemento na frente da fila sem removê-lo.
 * - 'queuePrint': Printa todos os elementos da fila.
 * 
 * Esta implementação permite armazenar dados de qualquer tipo, desde que seja informado o tamanho do tipo (via 'sizeof(tipo)')
 * no momento da criação da fila. As operações de enfileirar, desenfileirar e consultar a fila são suportadas.
 * 
 * @note A fila é uma estrutura dinâmica, e todas as operações que envolvem adição ou remoção de elementos ajustam a memória
 * conforme necessário.
 * 
 * @author Victor Gabriel Barbosa
 * @date 20/10/2024
 * @version 2.0
 */
#ifndef QUEUE_H
#define QUEUE_H

#include "typeslib.h"
 
/**
 * @brief Cria uma nova fila vazia.
 * 
 * @return Ponteiro para a nova fila, ou NULL se a alocação de memória falhar.
 */
queue queueNew();

/**
 * @brief Libera a memória utilizada por uma fila.
 * 
 * @param qeu Ponteiro para a fila a ser destruída.
 * @return NULL, indicando que a fila foi destruída e não deve mais ser utilizada.
 */
queue queueDestroy(queue qeu);

/**
 * @brief Verifica se a fila está vazia.
 * 
 * @param qeu Ponteiro para a fila a ser verificada.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int queueIsEmpty(queue qeu);

/**
 * @brief Retorna o tamanho da fila.
 * 
 * @param qeu Ponteiro para a fila cuja dimensão será verificada.
 * @return O número de elementos na fila. Retorna 0 se a fila for NULL.
 */
size_t queueSize(queue qeu);

/**
 * @brief Insere um novo elemento na fila.
 * 
 * @param qeu Ponteiro para a fila onde o elemento será inserido.
 * @param info O valor a ser inserido na fila.
 * @return Ponteiro para a fila atualizada, ou NULL se a fila for NULL ou a alocação falhar.
 */
queue queueEnqueue(queue qeu, obj info);

/**
 * @brief Remove e retorna o elemento do início da fila.
 * 
 * @param qeu Ponteiro para a fila da qual o elemento será removido.
 * @param info Ponteiro onde o valor do elemento removido será armazenado.
 * @return Ponteiro para a fila atualizada, ou a fila inalterada se estiver vazia.
 */
queue queueDequeue(queue qeu, obj* info);

/**
 * @brief Obtém o elemento do início da fila sem removê-lo.
 * 
 * @param qeu Ponteiro para a fila da qual o elemento será obtido.
 * @param info Ponteiro onde o valor do elemento do início da fila será armazenado.
 * @return 1 se o elemento foi obtido com sucesso, ou 0 se a fila estiver vazia.
 */
int queueFront(queue qeu, obj* info); 

/**
 * @brief Compara duas filas.
 *
 * @param qeu1 Ponteiro para a primeira fila a ser comparada.
 * @param qeu2 Ponteiro para a segunda fila a ser comparada.
 * @return 0 se as filas forem iguais, -1 se a primeira fila for menor, 1 se a primeira fila for maior.
 */
int queueCmp(queue qeu1, queue qeu2);

/**
 * @brief Converte a fila em uma representação de string.
 * 
 * @param qeu Ponteiro para a fila a ser convertida em string.
 * @return Uma string representando a fila, ou NULL se a fila estiver vazia.
 */
string queueToString(queue qeu);

/**
 * @brief Imprime a representação da fila na saída padrão.
 * 
 * @param qeu Ponteiro para a fila a ser impressa.
 * @return 1 se a fila foi impressa com sucesso, ou 0 se a fila estiver vazia.
 */
int queuePrint(queue qeu);
                                             
#endif