/**
 * @file List.h
 * @brief Implementação de uma Lista Duplamente Encadeada Genérica em C.
 * 
 * Este arquivo contém a implementação de uma lista duplamente encadeada genérica, que permite armazenar elementos de qualquer tipo.
 * A lista é composta por nós que armazenam um valor `info` (que pode ser de qualquer tipo) e ponteiros para os nós anterior e próximo.
 * Além disso, a lista contém ponteiros para o primeiro e o último nó, assim como o tamanho atual da lista e o tamanho do tipo dos elementos armazenados.
 * 
 * Funções disponíveis:
 * - `listNew`: Cria uma nova lista.
 * - `listDestroy`: Destrói uma lista, liberando toda a memória alocada.
 * - `listIsEmpty`: Verifica se a lista está vazia.
 * - `listSize`: Retorna o número de elementos na lista.
 * - `listAddIni`: Insere um novo elemento no início da lista.
 * - `listAddEnd`: Insere um novo elemento no final da lista.
 * - `listRemove`: Remove um elemento da lista em uma posição específica.
 * - `listSearch`: Busca um elemento na lista em uma posição específica.
 * - `listIndex`: Busca o índice de um elemento na lista.
 * - `listSort`: Ordena a lista usando o algoritmo Merge Sort.
 * - `listMerge`: Mescla duas listas ordenadas em uma nova lista.
 * - `listGet`: Obtém o valor de um elemento em uma posição específica.
 * - `listPrint`: Printa todos os elementos da lista.
 * 
 * Esta implementação é flexível, permitindo que qualquer tipo de dado seja armazenado, desde que seja informado o tamanho do tipo 
 * (usualmente com `sizeof(tipo)`) no momento da criação da lista. Ela também oferece funções para manipular a lista, 
 * incluindo inserção, remoção, busca, ordenação e fusão de listas.
 * 
 * @note Esta lista é duplamente encadeada, o que significa que cada nó mantém um ponteiro tanto para o próximo quanto para o nó anterior. 
 * Isso permite uma navegação eficiente em ambas as direções, além de simplificar algumas operações como remoção.
 * 
 * @author Victor Gabriel Barbosa
 * @date 12/10/2024
 * @version 1.0
 */
#ifndef LIST_H
#define LIST_H

#include <typeslib.h>
 
/** 
 * Cria uma nova lista vazia. 
 * 
 * @return Um ponteiro para uma nova lista.
 */
List listNew();

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
List listAddIni(List lst, Auto info);

/** 
 * @brief Insere um novo elemento no fim da lista.
 * 
 * @param lst Ponteiro para a lista.
 * @param info Os dados a serem inseridos na lista.
 * @return Um ponteiro para a lista atualizada.
 */
List listAddEnd(List lst, Auto info);

/** 
 * @brief Remove um elemento da lista.
 * 
 * @param lst Ponteiro para a lista.
 * @param pos A posição do elemento a ser removido.
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
int listSearch(List lst, const int pos, Auto *info); 

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
int listIndex(List lst, Auto info);

/**
 * @brief Ordena uma lista usando o Merge Sort.
 * 
 * @param lst Ponteiro para a lista.
 * @return A lista ordenada.
 */
List listSort(List lst);

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