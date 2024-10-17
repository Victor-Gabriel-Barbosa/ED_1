/**
 * @file binary_tree.h
 * @brief Biblioteca para manipulação de Árvores Binárias utilizando Auto.
 * 
 * Esta biblioteca permite criar, manipular e destruir uma árvore binária genérica,
 * que utiliza a estrutura Auto para armazenar dados de diversos tipos de forma flexível.
 * 
 * @author Victor Gabriel Barbosa
 * @date 16/10/2024
 */

#ifndef TREE_H
#define TREE_H

#include <typeslib.h>

/**
 * @brief Cria uma nova árvore binária.
 * 
 * @return Ponteiro para a árvore criada.
 */
Tree treeNew();

/**
 * @brief Insere um novo dado na árvore binária.
 * 
 * @param tree Ponteiro para a árvore binária.
 * @param info Dado a ser inserido, do tipo Auto.
 * @return Ponteiro para a árvore.
 */
Tree treeInsert(Tree tree, Auto info);

/**
 * @brief Verifica se um dado está presente na árvore binária.
 * 
 * @param tree Ponteiro para a árvore binária.
 * @param info Dado a ser pesquisado, do tipo Auto.
 * @return 1 se o dado for encontrado, 0 caso contrário.
 */
int treeSearch(Tree tree, Auto info);

/**
 * @brief Remove um dado da árvore binária.
 * 
 * @param tree Ponteiro para a árvore binária.
 * @param info Dado a ser removido, do tipo Auto.
 * @return Ponteiro para a árvore.
 */
Tree treeRemove(Tree tree, Auto info);

/**
 * @brief Destrói a árvore binária, liberando toda a memória alocada.
 * 
 * @param tree Ponteiro para a árvore binária a ser destruída.
 * @return Ponteiro para a árvore.
 */
Tree treeDestroy(Tree tree);

/**
 * @brief Imprime os dados da árvore binária (em ordem).
 * 
 * @param tree Ponteiro para a árvore binária.
 * @return 1 se o dado for encontrado, 0 caso contrário.
 */
int treePrint(Tree tree);

#endif
