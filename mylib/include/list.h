#ifndef LIST_H
#define LIST_H

#include <stddef.h>

/**
 * @brief Estrutura para representar uma lista
 */
typedef struct list *List;
 
/** 
 * Cria uma nova lista vazia. 
 * 
 * @return Um ponteiro para uma nova lista.
 */
List newList();

/** 
 * @brief Libera a memória alocada para a lista.
 * 
 * @param Ptd Ponteiro para a lista a ser liberada.
 * @return Um ponteiro nulo após a liberação da lista.
 */
List destroyList(List Ptd);

/** 
 * @brief Verifica se a lista está vazia.
 * 
 * @param Ptd Ponteiro para a lista.
 */
int isEmptyList(List Ptd);

/** 
 * @brief Obtém o tamanho da lista.
 * 
 * @param Ptd Ponteiro para a lista.
 * @return O tamanho da lista.
 */
size_t sizeList(List Ptd);

/** 
 * @brief Insere um novo elemento no início da lista.
 * 
 * @param Ptd Ponteiro para a lista.
 * @param info Os dados a serem inseridos na lista.
 * @return Um ponteiro para a lista atualizada.
 */
List insertAtBegin(List Ptd, const int info);

/** 
 * @brief Insere um novo elemento no fim da lista.
 * 
 * @param Ptd Ponteiro para a lista.
 * @param info Os dados a serem inseridos na lista.
 * @return Um ponteiro para a lista atualizada.
 */
List insertAtEnd(List Ptd, const int info);

/** 
 * @brief Remove um elemento da lista.
 * 
 * @param Ptd Ponteiro para a lista.
 * @param posi A posição do elemento a ser removido.
 * @return Um ponteiro para a lista atualizada.
 */
List removeAt(List Ptd, const int pos);

/** 
 * @brief Busca por um elemento da lista.
 * 
 * @param Ptd Ponteiro para a lista.
 * @param posi A posição do elemento a ser buscado.
 * @param info Ponteiro para armazenar os dados encontrados.
 * @return 1 se o elemento for encontrado, 0 caso contrário.
 */
int searchAt(List Ptd, const int pos, int *info); 

/** 
 * @brief Imprime a lista.
 * 
 * @param Ptd Ponteiro para a lista.
 * @return 1 se a impressão for bem-sucedida, 0 caso contrário.
 */
int printList(List Ptd); 
                                             
#endif