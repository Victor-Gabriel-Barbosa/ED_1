/**
 * @file list.h
 * @brief Implementação de uma Lista Duplamente Encadeada Genérica em C.
 * 
 * Este arquivo contém a implementação de uma lista duplamente encadeada genérica, que permite armazenar elementos de qualquer tipo.
 * A lista é composta por nós que armazenam um valor 'info' (que pode ser de qualquer tipo) e ponteiros para os nós anterior e próximo.
 * Além disso, a lista contém ponteiros para o primeiro e o último nó, assim como o tamanho atual da lista e o tamanho do tipo dos elementos armazenados.
 * 
 * Macros:
 * - 'listAdd': Adiciona um valor ao final da lista.
 * 
 * Funções disponíveis:
 * - 'sizeofList': Calcula o tamanho em bytes da estrutura de dados 'list_t'. 
 * - 'listNew': Cria uma nova lista.
 * - 'listDestroy': Destrói uma lista, liberando toda a memória alocada.
 * - 'listIsEmpty': Verifica se a lista está vazia.
 * - 'listSize': Retorna o número de elementos na lista.
 * - 'listAddIni': Insere um novo elemento no início da lista.
 * - 'listAddEnd': Insere um novo elemento no final da lista.
 * - 'listReplace': Substitui a primeira ocorrência de um objeto em uma lista.
 * - 'listReplaceAll': Substitui todas as ocorrências de um objeto em uma lista.
 * - 'listRemoveIf': Remove a primeira as ocorrência de um objeto em uma lista.
 * - 'listRemoveAllIf': Remove todas as ocorrências de um objeto em uma lista.
 * - 'listRemove': Remove um elemento da lista em uma posição específica.
 * - 'listSearch': Busca um elemento na lista em uma posição específica.
 * - 'listIndex': Busca o índice de um elemento na lista.
 * - 'listCopy': Cria uma cópia de uma lista encadeada.
 * - 'listCmp': Compara duas listas elemento por elemento.
 * - 'listSort': Ordena a lista usando o algoritmo Merge Sort.
 * - 'listGet': Obtém o valor de um elemento em uma posição específica.
 * - 'listMerge': Mescla duas listas ordenadas em uma nova lista.
 * - 'listToString': Converte uma lista encadeada em uma representação de string.
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
 * @brief Calcula o tamanho em bytes da estrutura de dados 'list_t'.
 * 
 * @return size_t O tamanho em bytes da estrutura 'list_t'.
 */
size_t sizeofList();
 
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
int listIsEmpty(const list lst);

/**
 * @brief Retorna o número de elementos na lista.
 *
 * @param lst A lista da qual se deseja obter o tamanho.
 * @return O número de nós na lista ou 0 se a lista for nula.
 */
size_t listSize(const list lst);

/**
 * @brief Adiciona um novo nó no início da lista.
 *
 * @param lst A lista onde o novo nó será adicionado.
 * @param info O objeto a ser armazenado no novo nó.
 * @return A lista atualizada com o novo nó no início.
 */
list listAddIni(list lst, const obj info);

/**
 * @brief Adiciona um novo nó ao final da lista.
 *
 * @param lst A lista onde o novo nó será adicionado.
 * @param info O objeto a ser armazenado no novo nó.
 * @return A lista atualizada com o novo nó no final.
 */
list listAddEnd(list lst, const obj info);

/**
 * @brief Adiciona um valor ao final da lista.
 * 
 * Macro que adiciona um valor ('value') ao final de uma lista ('lst'), 
 * convertendo-o automaticamente para o tipo adequado.
 *
 * @param lst Lista onde o valor será adicionado.
 * @param value Valor a ser adicionado na lista.
 */
#define listAdd(lst, value) listAddEnd(lst, toObj(value))

/**
 * @brief Substitui a primeira ocorrência de um objeto em uma lista.
 *
 * @param lst A lista onde será feita a substituição. Não pode estar vazia.
 * @param info1 O objeto que será procurado na lista.
 * @param info2 O objeto que substituirá o objeto a.
 * @return A lista após a substituição. Se a lista estiver vazia, ou se a, ou b forem NULL, retorna a lista original.
 */
list listReplace(list lst, const obj info1, const obj info2);

/**
 * @brief Substitui todas as ocorrências de um objeto em uma lista.
 *
 * @param lst A lista onde serão feitas as substituições. Não pode estar vazia.
 * @param info1 O objeto que será procurado na lista.
 * @param info2 O objeto que substituirá o objeto a.
 * @return A lista após as substituições.
 */
size_t listReplaceAll(list lst, const obj info1, const obj info2);

/**
 * @brief Remove um nó da lista em uma posição específica.
 *
 * @param lst A lista da qual o nó será removido.
 * @param pos A posição do nó a ser removido (de 0 a N-1).
 * @return A lista após a remoção do nó.
 */
list listRemove(list lst, const int pos);

/**
 * @brief Remove a primeira as ocorrência de um objeto em uma lista.
 *
 * Esta função percorre a lista fornecida e remove a primeira ocorrências do objeto info.
 *
 * @param lst A lista da qual os objetos serão removidos.
 * @param info O objeto que será removido da lista.
 * @return A lista após as remoções.
 */
list listRemoveIf(list lst, const obj info);

/**
 * @brief Remove todas as ocorrências de um objeto em uma lista e retorna a quantidade de elementos removidos.
 *
 * Esta função percorre a lista fornecida e remove todas as ocorrências do objeto info, contando quantas remoções foram feitas.
 *
 * @param lst A lista da qual os objetos serão removidos. Não pode estar vazia.
 * @param info O objeto que será removido da lista.
 * @return O número de elementos removidos.
 */
size_t listRemoveAllIf(list lst, const obj info);

/**
 * @brief Busca um objeto em uma posição específica da lista.
 *
 * @param lst A lista onde será realizada a busca.
 * @param pos A posição do objeto a ser buscado (de 0 a N-1).
 * @param info Ponteiro para armazenar o objeto encontrado.
 * @return 1 se o objeto for encontrado e armazenado com sucesso,
 * ou -1 se a lista estiver vazia, a posição for inválida, ou o ponteiro 'info' for nulo.
 */
int listSearch(const list lst, const int pos, obj* info); 

/**
 * @brief Retorna o objeto armazenado em uma posição específica da lista.
 *
 * @param lst A lista da qual se deseja obter o objeto.
 * @param pos A posição do nó de onde o objeto será obtido (de 0 a N-1).
 * @return O objeto armazenado no nó na posição especificada ou NULL se a posição for inválida.
 */
obj listGet(const list lst, const int pos);

/** 
 * @brief Retorna o índice da primeira ocorrência de um objeto na lista.
 *
 * @param lst A lista onde o objeto será procurado.
 * @param info O objeto a ser comparado com os elementos da lista.
 * @return O índice do primeiro nó contendo o objeto ou -1 se o objeto não for encontrado.
 */
int listIndex(const list lst, const obj info);


/**
 * @brief Cria uma cópia de uma lista encadeada.
 *
 * @param lst A lista a ser copiada.
 * @return Uma cópia da lista, ou NULL se a alocação de memória falhar.
 */
list listCopy(const list lst);

/**
 * @brief Compara duas listas elemento por elemento.
 *
 * @param lst1 A primeira lista a ser comparada.
 * @param lst2 A segunda lista a ser comparada.
 * @return 0 se as listas forem iguais, 1 se 'lst1' for maior, -1 se 'lst2' for maior.
 */
int listCmp(const list lst1, const list lst2);

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
list listMerge(const list lst1, const list lst2);

/**
 * @brief Converte uma lista encadeada em uma representação de string.
 *
 * @param lst A lista a ser convertida em string.
 * @return A representação de string da lista, ou NULL se a lista estiver vazia.
 */
string listToString(const list lst);

/**
 * @brief Exibe a representação em string de uma lista encadeada.
 *
 * @param lst A lista a ser exibida.
 * @return 1 se a impressão foi bem-sucedida ou 0 se a lista estiver vazia.
 */
int listPrint(const list lst);
                                                              
#endif