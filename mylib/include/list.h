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
 * @param sizeTip Tamanho do tipo da variável a ser armazenada.
 * @return Um ponteiro para uma nova lista.
 */
List listNew(size_t sizeTip);

/** 
 * @brief Libera a memória alocada para a lista.
 * 
 * @param lst Ponteiro para a lista a ser liberada.
 * @return Um ponteiro nulo após a liberação da lista.
 */
List listDestroy(List lst);

/** 
 * @brief Verifica se a lista está vazia.
 * 
 * @param lst Ponteiro para a lista.
 */
int listIsEmpty(List lst);

/** 
 * @brief Obtém o tamanho da lista.
 * 
 * @param lst Ponteiro para a lista.
 * @return O tamanho da lista.
 */
size_t listSize(List lst);

/** 
 * @brief Insere um novo elemento no início da lista.
 * 
 * @param lst Ponteiro para a lista.
 * @param info Os dados a serem inseridos na lista.
 * @return Um ponteiro para a lista atualizada.
 */
List listAddIni(List lst, const void *info);

/** 
 * @brief Insere um novo elemento no fim da lista.
 * 
 * @param lst Ponteiro para a lista.
 * @param info Os dados a serem inseridos na lista.
 * @return Um ponteiro para a lista atualizada.
 */
List listAddEnd(List lst, const void *info);

/** 
 * @brief Remove um elemento da lista.
 * 
 * @param lst Ponteiro para a lista.
 * @param posi A posição do elemento a ser removido.
 * @return Um ponteiro para a lista atualizada.
 */
List listRemove(List lst, const int pos);

/** 
 * @brief Busca por um elemento da lista.
 * 
 * @param lst Ponteiro para a lista.
 * @param pos A posição do elemento a ser buscado.
 * @param info Ponteiro para armazenar os dados encontrados.
 * @return 1 se o elemento for encontrado, 0 caso contrário.
 */
int listSearch(List lst, const int pos, void *info); 

/**
 * @brief Busca e retorna um elemento na lista na posição especificada.
 * 
 * @param lst Ponteiro para a lista.
 * @param pos Posição do elemento a ser buscado.
 * @return O elemento buscado.
 */
void *listGet(List lst, const int pos);

/**
 * @brief Busca o índice de um elemento na lista
 * 
 * @param lst Ponteiro para a lista.
 * @param info Elemento que será usado para encontrar o índice.
 * @return Index de posição do elemento.
 */
int listIndex(List lst, void *info);

/**
 * @brief Ordena uma lista usando o Merge Sort.
 * 
 * @param lst Ponteiro para a lista.
 * @return 1 se a lista foi ordenada com sucesso, 0 se houver erro.
 */
int listSort(List lst);

/**
 * @brief Mescla duas listas ordenadas em uma nova lista.
 * 
 * @param lst1 Ponteiro para a primeira lista.
 * @param lst2 Ponteiro para a segunda lista.
 * @return Ponteiro para a nova lista mesclada.
 */
List listMerge(List lst1, List lst2);

/** 
* @brief Simula o printf usando o tipo List.
*
* @param str Ponteiro para a List.
* @return 1 se a List não é vazia, 0 caso contrário.
*/
int listPrint(List lst);
                                                              
#endif