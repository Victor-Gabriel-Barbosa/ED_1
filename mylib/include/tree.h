/**
 * @file binary_tree.h
 * @brief Biblioteca para manipulação de Árvores Binárias utilizando obj.
 * 
 * Esta biblioteca permite criar, manipular e destruir uma árvore binária genérica,
 * que utiliza a estrutura obj para armazenar dados de diversos tipos de forma flexível.
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
tree treeNew();

/**
 * @brief Insere um novo dado na árvore binária.
 * 
 * @param tree Ponteiro para a árvore binária.
 * @param info Dado a ser inserido, do tipo obj.
 * @return Ponteiro para a árvore.
 */
tree treeInsert(tree tree, obj info);

/**
 * @brief Verifica se um dado está presente na árvore binária.
 * 
 * @param tree Ponteiro para a árvore binária.
 * @param info Dado a ser pesquisado, do tipo obj.
 * @return 1 se o dado for encontrado, 0 caso contrário.
 */
int treeSearch(tree tree, obj info);

/**
 * @brief Remove um dado da árvore binária.
 * 
 * @param tree Ponteiro para a árvore binária.
 * @param info Dado a ser removido, do tipo obj.
 * @return Ponteiro para a árvore.
 */
tree treeRemove(tree tree, obj info);

/**
 * @brief Destrói a árvore binária, liberando toda a memória alocada.
 * 
 * @param tree Ponteiro para a árvore binária a ser destruída.
 * @return Ponteiro para a árvore.
 */
tree treeDestroy(tree tree);

/**
 * @brief Imprime os dados da árvore binária (em ordem).
 * 
 * @param tree Ponteiro para a árvore binária.
 * @return 1 se o dado for encontrado, 0 caso contrário.
 */
int treePrint(tree tree);

#endif
