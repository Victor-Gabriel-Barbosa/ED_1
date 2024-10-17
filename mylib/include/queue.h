/**
 * @file Queue.h
 * @brief Implementação de uma Fila Genérica em C.
 * 
 * Este arquivo contém a implementação de uma fila genérica que permite armazenar elementos de qualquer tipo.
 * A fila segue o modelo FIFO (First In, First Out), onde o primeiro elemento inserido é o primeiro a ser removido.
 * 
 * Funções disponíveis:
 * - `queueNew`: Cria uma nova fila.
 * - `queueDestroy`: Destrói a fila, liberando a memória alocada.
 * - `queueIsEmpty`: Verifica se a fila está vazia.
 * - `queueSize`: Retorna o número de elementos na fila.
 * - `queueEnqueue`: Adiciona um novo elemento ao final da fila.
 * - `queueDequeue`: Remove um elemento do início da fila.
 * - `queueFront`: Consulta o elemento na frente da fila sem removê-lo.
 * - `queuePrint`: Printa todos os elementos da fila.
 * 
 * Esta implementação permite armazenar dados de qualquer tipo, desde que seja informado o tamanho do tipo (via `sizeof(tipo)`)
 * no momento da criação da fila. As operações de enfileirar, desenfileirar e consultar a fila são suportadas.
 * 
 * @note A fila é uma estrutura dinâmica, e todas as operações que envolvem adição ou remoção de elementos ajustam a memória
 * conforme necessário.
 * 
 * @author Victor Gabriel Barbosa
 * @date 12/10/2024
 * @version 1.0
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <typeslib.h>
 
/** 
 * @brief Cria uma nova fila vazia. 
 * 
 * @return Um ponteiro para uma nova fila.
 */
Queue queueNew();

/** 
 * @brief  Libera a memória alocada para a fila.
 * 
 * @param qeu Ponteiro para a fila a ser liberada.
 * @return Um ponteiro nulo após a liberação da fila.
 */
Queue queueDestroy(Queue qeu);

/** 
 * @brief Verifica se a fila está vazia.
 * 
 * @param qeu Ponteiro para a fila.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int queueIsEmpty(Queue qeu);

/** 
 * @brief Obtém o tamanho da fila.
 * 
 * @param qeu Ponteiro para a fila.
 * @return O tamanho da fila.
 */
size_t queueSize(Queue qeu);

/** 
 * @brief Insere um novo elemento no início da fila.
 * 
 * @param qeu Ponteiro para a fila.
 * @param info Os dados a serem inseridos na fila.
 * @return Um ponteiro para a fila atualizada.
 */
Queue queueEnqueue(Queue qeu, Auto info);

/** 
 * @brief Remove um elemento da fila.
 * 
 * @param qeu Ponteiro para a fila.
 * @param info Ponteiro para um elemento da fila.
 * @return Um ponteiro para a fila atualizada.
 */
Queue queueDequeue(Queue qeu, Auto *info);

/** 
 * @brief Busca por um elemento da fila.b
 * 
 * @param qeu Ponteiro para a fila.
 * @param posi A posição do elemento a ser buscado.
 * @param info Ponteiro para armazenar os dados encontrados.
 * @return 1 se o elemento for encontrado, 0 caso contrário.
 */
int queueFront(Queue qeu, Auto *info); 

/** 
* @brief Printa todos os elementos de uma fila.
*
* @param qeu Ponteiro para a fila.
* @return 1 se a fila não é vazia, 0 caso contrário.
*/
int queuePrint(Queue qeu);
                                             
#endif