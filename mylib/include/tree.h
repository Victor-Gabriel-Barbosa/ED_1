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
 * @brief Destrói a árvore binária, liberando toda a memória alocada.
 * 
 * @param tree Ponteiro para a árvore binária a ser destruída.
 * @return Ponteiro para a árvore.
 */
tree treeDestroy(tree tree);

/**
 * @brief Verifica se a árvore é vazia.
 * 
 * @param tre Um ponteiro para a árvore que será verificada.
 * @return int Retorna 1 se a árvore estiver vazia, ou 0 se contiver elementos.
 */
int treeIsEmpty(tree tre);

/**
 * @brief Conta a quantidade de galhos na árvore.
 * 
 * @param tre Um ponteiro para a árvore que será verificada.
 * @return int A quantidade de galhos na árvore.
 */
int treeCountBranches(tree tre);

/**
 * @brief Conta a quantidade de folhas na árvore.
 * 
 * @param tre Um ponteiro para a árvore que será verificada.
 * @return int A quantidade de folhas na árvore.
 */
int treeCountLeaves(tree tre);

/**
 * @brief Conta o número total de nós na árvore.
 * 
 * @param tre Um ponteiro para a árvore a ser contada.
 * @return int O número total de nós na árvore.
 */
int treeCountNodes(tree tre);

/**
 * @brief Calcula a altura da árvore.
 * 
 * @param tre Um ponteiro para a árvore cuja altura será calculada.
 * @return int A altura da árvore.
 */
int treeHeight(tree tre);

/**
 * @brief Insere um novo dado na árvore binária.
 * 
 * @param tree Ponteiro para a árvore binária.
 * @param info Dado a ser inserido, do tipo obj.
 * @return Ponteiro para a árvore.
 */
tree treeAdd(tree tree, obj info);

/**
 * @brief Verifica se um dado está presente na árvore binária.
 * 
 * @param tree Ponteiro para a árvore binária.
 * @param info Dado a ser pesquisado, do tipo obj.
 * @return 1 se o dado for encontrado, 0 caso contrário.
 */
int treeSearch(tree tree, obj info);

/**
 * @brief Encontra o nó com o valor máximo na árvore.
 * 
 * @param tre Um ponteiro para a árvore onde será feita a busca.
 * @return obj O valor máximo encontrado na árvore.
 */
obj treeFindMax(tree tre);

/**
 * @brief Encontra o nó com o valor mínimo na árvore.
 * 
 * @param tre Um ponteiro para a árvore onde será feita a busca.
 * @return obj O valor mínimo encontrado na árvore.
 */
obj treeFindMin(tree tre);

/**
 * @brief Remove um dado da árvore binária.
 * 
 * @param tree Ponteiro para a árvore binária.
 * @param info Dado a ser removido, do tipo obj.
 * @return Ponteiro para a árvore.
 */
tree treeRemove(tree tree, obj info);

/**
 * @brief Inverte a árvore binária.
 * 
 * @param tre Um ponteiro para a árvore a ser invertida.
 * @return tree Retorna a árvore invertida.
 */
tree treeInvert(tree tre);

/**
 * @brief Compara duas árvores binárias de forma semelhante ao strcmp.
 * 
 * @param tree1 Ponteiro para a primeira árvore.
 * @param tree2 Ponteiro para a segunda árvore.
 * @return 0 se as árvores forem iguais, um valor negativo se tree1 < tree2,
 * ou um valor positivo se tree1 > tree2.
 */
int treeCmp(tree tree1, tree tree2);

/**
 * @brief Converte uma árvore binária em uma string.
 * 
 * @param tre Um ponteiro para a árvore a ser convertida.
 * @return string A string resultante que representa a árvore.
 */
string treeToString(tree tre);

/**
 * @brief Imprime os dados da árvore binária (em ordem).
 * 
 * @param tree Ponteiro para a árvore binária.
 * @return 1 se o dado for encontrado, 0 caso contrário.
 */
int treePrint(tree tree);

#endif
