/**
 * @file binary_map.h
 * @brief Biblioteca para manipulação de Árvores Binárias utilizando obj.
 * 
 * Esta biblioteca permite criar, manipular e destruir uma árvore binária genérica,
 * que utiliza a estrutura obj para armazenar dados de diversos tipos de forma flexível.
 * 
 * @author Victor Gabriel Barbosa
 * @date 16/10/2024
 */

#ifndef MAP_H
#define MAP_H

#include "typeslib.h"

/**
 * @brief Retorna o tamanho da estrutura map_t em bytes.
 *
 * @return size_t O tamanho da estrutura `struct map_t` em bytes.
 */
size_t sizeofMap();

/**
 * @brief Cria uma nova árvore binária.
 * 
 * @return Ponteiro para a árvore criada.
 */
map mapNew();

/**
 * @brief Destrói a árvore binária, liberando toda a memória alocada.
 * 
 * @param map Ponteiro para a árvore binária a ser destruída.
 * @return Ponteiro para a árvore.
 */
map mapDestroy(map map);

/**
 * @brief Verifica se a árvore é vazia.
 * 
 * @param tre Um ponteiro para a árvore que será verificada.
 * @return int Retorna 1 se a árvore estiver vazia, ou 0 se contiver elementos.
 */
int mapIsEmpty(map tre);

/**
 * @brief Conta a quantidade de galhos na árvore.
 * 
 * @param tre Um ponteiro para a árvore que será verificada.
 * @return int A quantidade de galhos na árvore.
 */
int mapCountBranches(map tre);

/**
 * @brief Conta a quantidade de folhas na árvore.
 * 
 * @param tre Um ponteiro para a árvore que será verificada.
 * @return int A quantidade de folhas na árvore.
 */
int mapCountLeaves(map tre);

/**
 * @brief Conta o número total de nós na árvore.
 * 
 * @param tre Um ponteiro para a árvore a ser contada.
 * @return int O número total de nós na árvore.
 */
int mapCountNodes(map tre);

/**
 * @brief Calcula a altura da árvore.
 * 
 * @param tre Um ponteiro para a árvore cuja altura será calculada.
 * @return int A altura da árvore.
 */
int mapHeight(map tre);

/**
 * @brief Insere um novo dado na árvore binária.
 * 
 * @param map Ponteiro para a árvore binária.
 * @param info Dado a ser inserido, do tipo obj.
 * @return Ponteiro para a árvore.
 */
map mapAdd(map map, obj info);

/**
 * @brief Verifica se um dado está presente na árvore binária.
 * 
 * @param map Ponteiro para a árvore binária.
 * @param info Dado a ser pesquisado, do tipo obj.
 * @return 1 se o dado for encontrado, 0 caso contrário.
 */
int mapSearch(map map, obj info);

/**
 * @brief Encontra o nó com o valor máximo na árvore.
 * 
 * @param tre Um ponteiro para a árvore onde será feita a busca.
 * @return obj O valor máximo encontrado na árvore.
 */
obj mapFindMax(map tre);

/**
 * @brief Encontra o nó com o valor mínimo na árvore.
 * 
 * @param tre Um ponteiro para a árvore onde será feita a busca.
 * @return obj O valor mínimo encontrado na árvore.
 */
obj mapFindMin(map tre);

/**
 * @brief Remove um dado da árvore binária.
 * 
 * @param map Ponteiro para a árvore binária.
 * @param info Dado a ser removido, do tipo obj.
 * @return Ponteiro para a árvore.
 */
map mapRemove(map map, obj info);

/**
 * @brief Inverte a árvore binária.
 * 
 * @param tre Um ponteiro para a árvore a ser invertida.
 * @return map Retorna a árvore invertida.
 */
map mapInvert(map tre);

/**
 * @brief Compara duas árvores binárias de forma semelhante ao strcmp.
 * 
 * @param map1 Ponteiro para a primeira árvore.
 * @param map2 Ponteiro para a segunda árvore.
 * @return 0 se as árvores forem iguais, um valor negativo se map1 < map2,
 * ou um valor positivo se map1 > map2.
 */
int mapCmp(map map1, map map2);

/**
 * @brief Converte uma árvore binária em uma string.
 * 
 * @param tre Um ponteiro para a árvore a ser convertida.
 * @return string A string resultante que representa a árvore.
 */
string mapToString(map tre);

/**
 * @brief Imprime os dados da árvore binária (em ordem).
 * 
 * @param map Ponteiro para a árvore binária.
 * @return 1 se o dado for encontrado, 0 caso contrário.
 */
int mapPrint(map map);

#endif
