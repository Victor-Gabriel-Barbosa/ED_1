/**
 * @file list.h
 * @brief Implementação de uma Lista Duplamente Encadeada Genérica em C.
 * 
 * Este arquivo contém a implementação de uma lista duplamente encadeada genérica, que permite armazenar elementos de qualquer tipo.
 * A lista é composta por nós que armazenam um valor 'info' (que pode ser de qualquer tipo) e ponteiros para os nós anterior e próximo.
 * Além disso, a lista contém ponteiros para o primeiro e o último nó, assim como o tamanho atual da lista e o tamanho do tipo dos elementos armazenados.
 * 
 * Funções disponíveis:
 * - 'listNew': Cria uma nova lista.
 * - 'listDestroy': Destrói uma lista, liberando toda a memória alocada.
 * - 'listIsEmpty': Verifica se a lista está vazia.
 * - 'listSize': Retorna o número de elementos na lista.
 * - 'listAddIni': Insere um novo elemento no início da lista.
 * - 'listAddEnd': Insere um novo elemento no final da lista.
 * - 'listRemove': Remove um elemento da lista em uma posição específica.
 * - 'listSearch': Busca um elemento na lista em uma posição específica.
 * - 'listIndex': Busca o índice de um elemento na lista.
 * - 'listSort': Ordena a lista usando o algoritmo Merge Sort.
 * - 'listMerge': Mescla duas listas ordenadas em uma nova lista.
 * - 'listGet': Obtém o valor de um elemento em uma posição específica.
 * - 'listPrint': Printa todos os elementos da lista.
 * 
 * Esta implementação é flexível, permitindo que qualquer tipo de dado seja armazenado, desde que seja informado o tamanho do tipo 
 * (usualmente com 'sizeof(tipo)') no momento da criação da lista. Ela também oferece funções para manipular a lista, 
 * incluindo inserção, remoção, busca, ordenação e fusão de listas.
 * 
 * @note Esta lista é duplamente encadeada, o que significa que cada nó mantém um ponteiro tanto para o próximo quanto para o nó anterior. 
 * Isso permite uma navegação eficiente em ambas as direções, além de simplificar algumas operações como remoção.
 * 
 * @author Victor Gabriel Barbosa
 * @date 20/10/2024
 * @version 2.0
 */
#ifndef LIST_H
#define LIST_H

#include <typeslib.h>
 
/**  
 * Cria uma nova lista vazia. 
 * 
 * @return Uma nova instância do lista.
 */
list listNew();

/** 
 * @brief Libera a memória alocada para a lista.
 * 
 * @param lst Lista a ser liberado.
 * @return Um ponteiro nulo após a liberação da lista.
 */
list listDestroy(list lst);

/** 
 * @brief Verifica se a lista está vazia.
 * 
 * @param lst Lista.
 * @return 1 se a lista está vazia, 0 caso contrário
 */
int listIsEmpty(list lst);

/** 
 * @brief Obtém o tamanho da lista.
 * 
 * @param lst Lista.
 * @return O tamanho da lista.
 */
size_t listSize(list lst);

/** 
 * @brief Insere um novo elemento no início da lista.
 * 
 * @param lst Lista.
 * @param info O valor a ser inserido (objeto obj).
 * @return Um Lista atualizada.
 */
list listAddIni(list lst, obj info);

/** 
 * @brief Insere um novo elemento no fim da lista.
 * 
 * @param lst Lista.
 * @param info O valor a ser inserido (objeto obj).
 * @return Um Lista atualizada.
 */
list listAddEnd(list lst, obj info);

/** 
 * @brief Remove um elemento da lista.
 * 
 * @param lst Lista.
 * @param pos A posição do elemento a ser removido.
 * @return Lista atualizado.
 */
list listRemove(list lst, const int pos);

/** 
 * @brief Busca por um elemento da lista.
 * 
 * @param lst Lista.
 * @param pos A posição do elemento a ser buscado.
 * @param info Objeto para armazenar o dado encontrado (objeto obj).
 * @return 1 se o elemento for encontrado, 0 caso contrário.
 */
int listSearch(list lst, const int pos, obj *info); 

/**
 * @brief Busca e retorna um elemento na lista na posição especificada.
 * 
 * @param lst Lista.
 * @param pos Posição do elemento a ser buscado.
 * @return O elemento buscado (objeto obj).
 */
obj listGet(list lst, const int pos);

/**
 * @brief Busca o índice de um elemento na lista
 * 
 * @param lst Lista.
 * @param info Elemento que será usado para encontrar o índice (objeto obj).
 * @return Index de posição do elemento.
 */
int listIndex(list lst, obj info);

/**
 * Compara duas listas encadeadas.
 * 
 * @param lst1 A primeira lista a ser comparada.
 * @param lst2 A segunda lista a ser comparada.
 * 
 * @return 
 * - 1 se lst1 for maior que lst2,
 * - -1 se lst2 for maior que lst1,
 * - 0 se ambas as listas forem iguais (tanto em tamanho quanto em conteúdo).
 */
int listCmp(list lst1, list lst2);

/**
 * @brief Função principal para ordenar a lista.
 * 
 * Ordena usando o mecanismo de ordenação Intro Sort.
 * Complexidade (Pior Caso): O(NlogN).
 * 
 * @param lst Lista.
 * @return A lista ordenada.
 */
list listSort(list lst);

/**
 * @brief Mescla duas listas ordenadas em uma nova lista.
 * 
 * @param lst1 Objeto para a primeira lista.
 * @param lst2 Objeto para a segunda lista.
 * @return Objeto para a nova lista mesclada.
 */
list listMerge(list lst1, list lst2);

/**
 * @brief Converte uma lista para uma string.
 * 
 * @param lst Lista a ser convertida.
 * @return string da lista convertida.
 */
string listToString(list lst);

/** 
* @brief Simula o printf usando o tipo list.
*
* @param str Objeto para a list.
* @return 1 se a list não é vazia, 0 caso contrário.
*/
int listPrint(list lst);
                                                              
#endif