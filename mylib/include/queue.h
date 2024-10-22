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

#include <typeslib.h>
 
/** 
 * @brief Cria uma nova fila vazia. 
 * 
 * @return Um ponteiro para uma nova fila.
 */
queue queueNew();

/** 
 * @brief Libera a memória alocada para a fila.
 * 
 * @param qeu Objeto para a fila a ser liberada.
 * @return Um ponteiro nulo após a liberação da fila.
 */
queue queueDestroy(queue qeu);

/** 
 * @brief Verifica se a fila está vazia.
 * 
 * @param qeu Objeto para a fila.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int queueIsEmpty(queue qeu);

/** 
 * @brief Obtém o tamanho da fila.
 * 
 * @param qeu Objeto para a fila.
 * @return O tamanho da fila.
 */
size_t queueSize(queue qeu);

/** 
 * @brief Insere um novo elemento no início da fila.
 * 
 * @param qeu Objeto para a fila.
 * @param info Os dados a serem inseridos na fila.
 * @return Um objeto para a fila atualizada.
 */
queue queueEnqueue(queue qeu, obj info);

/** 
 * @brief Remove um elemento da fila.
 * 
 * @param qeu Objeto para a fila.
 * @param info Ponteiro para um elemento da fila.
 * @return Um objeto para a fila atualizada.
 */
queue queueDequeue(queue qeu, obj* info);

/** 
 * @brief Busca por um elemento da fila.b
 * 
 * @param qeu Objeto para a fila.
 * @param pos A posição do elemento a ser buscado.
 * @param info Ponteiro para armazenar os dados encontrados.
 * @return 1 se o elemento for encontrado, 0 caso contrário.
 */
int queueFront(queue qeu, obj* info); 

/**
 * Compara duas filas (queues).
 * 
 * @param qeu1 A primeira fila a ser comparada.
 * @param qeu2 A segunda fila a ser comparada.
 * 
 * @return 
 * - 1 se qeu1 for maior que qeu2 (em termos de tamanho ou conteúdo),
 * - -1 se qeu2 for maior que qeu1,
 * - 0 se ambas as filas forem iguais.
 */
int queueCmp(queue qeu1, queue qeu2);

/**
 * @brief Converte uma fila para uma string.
 * 
 * @param qeu Fila a ser convertida.
 * @return string da fila convertida.
 */
string queueToString(queue qeu);

/** 
* @brief Exibe todos os elementos de uma fila.
*
* @param qeu Objeto para a fila.
* @return 1 se a fila não é vazia, 0 caso contrário.
*/
int queuePrint(queue qeu);
                                             
#endif