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

#include "typeslib.h"
 
/**
 * @brief Cria uma nova lista duplamente encadeada e inicializa seus campos.
 * 
 * @return Ponteiro para a nova lista, ou NULL se a alocação de memória falhar.
 */
list listNew();

/**
 * @brief Libera toda a memória alocada para a lista e seus elementos.
 * 
 * @param lst Ponteiro para a lista a ser destruída.
 * @return NULL após a destruição da lista.
 */
list listDestroy(list lst);

/**
 * @brief Verifica se uma lista encadeada está vazia.
 *
 * @param lst A lista a ser verificada.
 * @return 1 se a lista estiver vazia, 0 caso contrário.
 */
int listIsEmpty(list lst);

/**
 * @brief Retorna o número de elementos na lista.
 *
 * @param lst A lista da qual se deseja obter o tamanho.
 * @return O número de nós na lista ou 0 se a lista for nula.
 */
size_t listSize(list lst);

/**
 * @brief Adiciona um novo nó no início da lista.
 *
 * @param lst A lista onde o novo nó será adicionado.
 * @param info O objeto a ser armazenado no novo nó.
 * @return A lista atualizada com o novo nó no início.
 */
list listAddIni(list lst, obj info);

/**
 * @brief Adiciona um novo nó ao final da lista.
 *
 * @param lst A lista onde o novo nó será adicionado.
 * @param info O objeto a ser armazenado no novo nó.
 * @return A lista atualizada com o novo nó no final.
 */
list listAddEnd(list lst, obj info);

/**
 * @brief Remove um nó da lista em uma posição específica.
 *
 * @param lst A lista da qual o nó será removido.
 * @param pos A posição do nó a ser removido (de 0 a N-1).
 * @return A lista após a remoção do nó.
 */
list listRemove(list lst, const int pos);

/**
 * @brief Busca um objeto em uma posição específica da lista.
 *
 * @param lst A lista onde será realizada a busca.
 * @param pos A posição do objeto a ser buscado (de 0 a N-1).
 * @param info Ponteiro para armazenar o objeto encontrado.
 * @return 1 se o objeto for encontrado e armazenado com sucesso,
 * ou -1 se a lista estiver vazia, a posição for inválida, ou o ponteiro 'info' for nulo.
 */
int listSearch(list lst, const int pos, obj *info); 

/**
 * @brief Retorna o objeto armazenado em uma posição específica da lista.
 *
 * @param lst A lista da qual se deseja obter o objeto.
 * @param pos A posição do nó de onde o objeto será obtido (de 0 a N-1).
 * @return O objeto armazenado no nó na posição especificada ou NULL se a posição for inválida.
 */
obj listGet(list lst, const int pos);

/**
 * @brief Retorna o índice da primeira ocorrência de um objeto na lista.
 *
 * @param lst A lista onde o objeto será procurado.
 * @param info O objeto a ser comparado com os elementos da lista.
 * @return O índice do primeiro nó contendo o objeto ou -1 se o objeto não for encontrado.
 */
int listIndex(list lst, obj info);

/**
 * @brief Compara duas listas elemento por elemento.
 *
 * @param lst1 A primeira lista a ser comparada.
 * @param lst2 A segunda lista a ser comparada.
 * @return 0 se as listas forem iguais, 1 se 'lst1' for maior, -1 se 'lst2' for maior.
 */
int listCmp(list lst1, list lst2);

/**
 * @brief Ordena uma lista encadeada usando o algoritmo Quick Sort.
 *
 * @param lst A lista a ser ordenada.
 * @return A lista ordenada, ou a mesma lista se estiver vazia 
 * ou contendo um único elemento.
 */
list listSort(list lst);

/**
 * @brief Mescla duas listas encadeadas ordenadas em uma única lista ordenada.
 *
 * @param lst1 A primeira lista a ser mesclada.
 * @param lst2 A segunda lista a ser mesclada.
 * @return A lista mesclada ordenada, ou NULL se a alocação de memória falhar.
 */
list listMerge(list lst1, list lst2);

/**
 * @brief Converte uma lista encadeada em uma representação de string.
 *
 * @param lst A lista a ser convertida em string.
 * @return A representação de string da lista, ou NULL se a lista estiver vazia.
 */
string listToString(list lst);

/**
 * @brief Exibe a representação em string de uma lista encadeada.
 *
 * @param lst A lista a ser exibida.
 * @return 1 se a impressão foi bem-sucedida ou 0 se a lista estiver vazia.
 */
int listPrint(list lst);
                                                              
#endif