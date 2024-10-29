/**
 * @file tree.h
 * @brief Biblioteca para manipulação de Árvores Binárias AVL utilizando objetos genéricos.
 * 
 * Esta biblioteca fornece uma interface para criar, manipular e destruir 
 * árvores binárias. As árvores são estruturas de dados que consistem em 
 * nós, onde cada nó contém um valor e ponteiros para dois filhos, 
 * permitindo uma organização hierárquica dos dados.
 * 
 * Macros Disponíveis:
 * - 'treeAdd': Adiciona um novo elemento na árvore AVL.
 *  
 * Funções Disponíveis:
 * - 'sizeofTree': Retorna o tamanho da estrutura tree_t em bytes.
 * - 'treeNew()': Cria uma nova árvore binária AVL.
 * - 'treeInsert()': Insere um novo elemento na árvore AVL.
 * - 'treeRemove()': Remove um elemento da árvore AVL.
 * - 'treeSearch()': Inserção, remoção e busca de dados.
 * - 'treeCountNodes()': Conta o número total de nós na árvore.
 * - 'treeCountLeaves()': Conta a quantidade de folhas na árvore.
 *  -'treeCountBranches()': Contagem de nós, folhas e galhos.
 * - 'treeHeight()': Calcula a altura da árvore AVL.
 * - 'treeInvert()': Inverte a árvore binária AVL.
 * - 'treeCopy': Cria uma cópia de uma árvore binária AVL.
 * - 'treeCmp()': Compara duas árvores binárias AVL de forma semelhante ao strcmp.
 * - 'treeToString()': Converte uma árvore binária AVL em uma string.
 * - 'treePrint()': Imprime os dados da árvore binária AVL (em ordem).
 *
 * Os dados armazenados na árvore são do tipo genérico 'obj', 
 * o que permite que a árvore armazene diferentes tipos de dados 
 * de maneira flexível. Os usuários devem garantir que os dados 
 * inseridos na árvore implementem as operações necessárias, como 
 * comparação e impressão.
 * 
 * @author Victor Gabriel Barbosa
 * @date 20/10/2024
 */
#ifndef TREE_H
#define TREE_H

#include "typeslib.h"

/**
 * @brief Retorna o tamanho da estrutura tree_t em bytes.
 *
 * @return size_t O tamanho da estrutura 'struct tree_t' em bytes.
 */
size_t sizeofTree();

/**
 * @brief Cria uma nova árvore binária AVL.
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
int treeIsEmpty(const tree tre);

/**
 * @brief Conta a quantidade de galhos na árvore.
 * 
 * @param tre Um ponteiro para a árvore que será verificada.
 * @return int A quantidade de galhos na árvore.
 */
int treeCountBranches(const tree tre);

/**
 * @brief Conta a quantidade de folhas na árvore.
 * 
 * @param tre Um ponteiro para a árvore que será verificada.
 * @return int A quantidade de folhas na árvore.
 */
int treeCountLeaves(const tree tre);

/**
 * @brief Conta o número total de nós na árvore.
 * 
 * @param tre Um ponteiro para a árvore a ser contada.
 * @return int O número total de nós na árvore.
 */
int treeCountNodes(const tree tre);

/**
 * @brief Calcula a altura da árvore AVL.
 * 
 * @param tre Um ponteiro para a árvore cuja altura será calculada.
 * @return A altura da árvore.
 */
size_t treeHeight(const tree tre);

/**
 * @brief Insere um novo elemento na árvore AVL.
 *
 * @param tre Um ponteiro para a árvore onde o elemento será inserido.
 * @param info O valor a ser inserido na árvore.
 * @return Um ponteiro para a raiz da árvore após a inserção e balanceamento.
 */
tree treeInsert(tree tree, const obj info);

/**
 * @brief Adiciona um novo elemento na árvore AVL.
 * 
 * Macro que adiciona um valor ('value') ao final de uma árvore ('tre'), 
 * convertendo-o automaticamente para o tipo adequado.
 *
 * @param qeu Árvore onde o valor será adicionado.
 * @param value Valor a ser adicionado na árvore.
 */
#define treeAdd(tre, value) tre = treeInsert(tre, toObj(value))

/**
 * @brief Remove um elemento da árvore AVL.
 *
 * @param tre Um ponteiro para a árvore de onde o elemento será removido.
 * @param info O valor a ser removido da árvore.
 * @return Um ponteiro para a raiz da árvore após a remoção e balanceamento.
 */
tree treeRemove(tree tre, const obj info);

/**
 * @brief Verifica se um dado está presente na árvore binária.
 * 
 * @param tree Ponteiro para a árvore binária.
 * @param info Dado a ser pesquisado, do tipo obj.
 * @return 1 se o dado for encontrado, 0 caso contrário.
 */
int treeSearch(const tree tree, const obj info);

/**
 * @brief Encontra o nó com o valor máximo na árvore.
 * 
 * @param tre Um ponteiro para a árvore onde será feita a busca.
 * @return obj O valor máximo encontrado na árvore.
 */
obj treeFindMax(const tree tre);

/**
 * @brief Encontra o nó com o valor mínimo na árvore.
 * 
 * @param tre Um ponteiro para a árvore onde será feita a busca.
 * @return obj O valor mínimo encontrado na árvore.
 */
obj treeFindMin(const tree tre);

/**
 * @brief Remove um valor de uma árvore binária.
 * 
 * A macro 'treeDelete' facilita a remoção de um valor ('value') de uma árvore binária ('tre'),
 * convertendo o valor para o tipo apropriado e chamando a função de remoção 'treeRemove'.
 *
 * @param tre Árvore binária da qual o valor será removido.
 * @param value Valor a ser removido da árvore.
 */
#define treeDelete(tre, value) tre = treeRemove(tre, toObj(value));

/**
 * @brief Inverte a árvore binária AVL.
 * 
 * @param tre Um ponteiro para a árvore a ser invertida.
 * @return tree Retorna a árvore invertida.
 */
tree treeInvert(tree tre);

/**
 * @brief Cria uma cópia de uma árvore binária.
 *
 * @param tre A árvore a ser copiada.
 * @return Uma cópia da árvore, ou NULL se a alocação de memória falhar.
 */
tree treeCopy(const tree tre);

/**
 * @brief Compara duas árvores binárias de forma semelhante ao strcmp.
 * 
 * @param tree1 Ponteiro para a primeira árvore.
 * @param tree2 Ponteiro para a segunda árvore.
 * @return 0 se as árvores forem iguais, um valor negativo se tree1 < tree2,
 * ou um valor positivo se tree1 > tree2.
 */
int treeCmp(const tree tree1, const tree tree2);

/**
 * @brief Converte uma árvore binária AVL em uma string.
 * 
 * @param tre Um ponteiro para a árvore a ser convertida.
 * @return string A string resultante que representa a árvore.
 */
string treeToString(const tree tre);

/**
 * @brief Imprime os dados da árvore binária AVL (em ordem).
 * 
 * @param tree Ponteiro para a árvore binária.
 * @return 1 se o dado for encontrado, 0 caso contrário.
 */
int treePrint(const tree tree);

#endif
