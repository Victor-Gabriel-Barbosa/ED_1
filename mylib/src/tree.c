#include <tree.h>
#include <stdlib.h>
#include <stringlib.h>

/**
 * @brief Estrutura que representa um nó da árvore binária.
 */
typedef struct nodeT {
  Auto info;             /**< Dados do nó, utilizando Auto */
  struct nodeT *left;    /**< Ponteiro para o filho esquerdo */
  struct nodeT *right;   /**< Ponteiro para o filho direito */
} NodeT;

/**
 * @brief Estrutura que representa uma árvore binária.
 */
typedef struct tree {
  NodeT *root;  /**< Raiz da árvore */
} *Tree;

/**
 * @brief Cria uma nova árvore vazia.
 * 
 * Aloca memória para uma nova árvore, inicializando o ponteiro da raiz como NULL.
 * 
 * @return Tree Um ponteiro para a nova árvore criada.
 */
Tree treeNew() {
  Tree newTree = (Tree)malloc(sizeof(struct tree));
  if (newTree == NULL) return NULL;
  newTree->root = NULL;
  return newTree;
}

/**
 * @brief Insere um novo elemento na árvore.
 * 
 * Insere o valor `info` na posição correta na árvore de acordo com as regras da árvore binária de busca.
 * 
 * @param tree Um ponteiro para a árvore onde o elemento será inserido.
 * @param info O valor a ser inserido na árvore.
 * @return int Retorna 1 se a inserção for bem-sucedida, ou 0 em caso de erro.
 */
Tree treeInsert(Tree tree, Auto info) {
  if (tree == NULL) return tree;
  NodeT *newNode = (NodeT *)malloc(sizeof(NodeT));
  if (newNode == NULL) return tree; 
  newNode->info = info;
  newNode->left = NULL;
  newNode->right = NULL;
  if (tree->root == NULL) {
    tree->root = newNode;  
    return tree;
  }
  NodeT *current = tree->root;
  NodeT *parent = NULL;
  while (current != NULL) {
    parent = current;
    if (info < current->info) current = current->left;
    else current = current->right;
  }
  if (info < parent->info) parent->left = newNode;
  else parent->right = newNode;
  return tree;
}

/**
 * @brief Busca um elemento na árvore.
 * 
 * Verifica se o valor `info` está presente na árvore.
 * 
 * @param tree Um ponteiro para a árvore onde a busca será realizada.
 * @param info O valor a ser buscado na árvore.
 * @return int Retorna 1 se o valor for encontrado, ou 0 caso contrário.
 */
int treeSearch(Tree tree, Auto info) {
  if (tree == NULL) return 0;
  NodeT *current = tree->root;
  while (current != NULL) {
    if (info == current->info) return 1; 
    else if (info < current->info) current = current->left;
    else current = current->right;
  }
  return 0;  
}

/**
 * @brief Encontra o nó com o menor valor em uma árvore.
 * 
 * @param node Um ponteiro para o nó a partir do qual a busca será feita.
 * @return NodeT Um ponteiro para o nó com o menor valor encontrado.
 */
NodeT *findMin(NodeT *node) {
  while (node && node->left != NULL) node = node->left;
  return node;
}

/**
 * @brief Remove um elemento da árvore.
 * 
 * Remove o nó contendo o valor `info` da árvore.
 * 
 * @param tree Um ponteiro para a árvore de onde o elemento será removido.
 * @param info O valor a ser removido da árvore.
 * @return int Retorna 1 se a remoção for bem-sucedida, ou 0 em caso de erro.
 */
Tree treeRemove(Tree tree, Auto info) {
  if (tree == NULL) return NULL;
  NodeT *current = tree->root;
  NodeT *parent = NULL;
  while (current != NULL && current->info != info) {
    parent = current;
    if (info < current->info) current = current->left;
    else current = current->right;
  }
  if (current == NULL) return tree; 
  if (current->left == NULL && current->right == NULL) {
    if (current == tree->root) tree->root = NULL;
    else if (parent->left == current) parent->left = NULL;
    else parent->right = NULL;
  }
  else if (current->left == NULL || current->right == NULL) {
    NodeT *child = (current->left != NULL) ? current->left : current->right;
    if (current == tree->root) tree->root = child; 
    else if (parent->left == current) parent->left = child;
    else parent->right = child;
  }
  else {
    NodeT *successor = findMin(current->right);
    Auto successorValue = successor->info;
    treeRemove(tree, successorValue);  
    current->info = successorValue;  
  }
  free(current); 
  return tree;
}

/**
 * @brief Libera a memória dos nós da árvore recursivamente.
 * 
 * @param node Um ponteiro para o nó atual.
 */
void freeNode(NodeT *node) {
  if (node != NULL) {
    freeNode(node->left);
    freeNode(node->right);
    free(node);
  }
}

/**
 * @brief Destrói a árvore e libera a memória associada.
 * 
 * @param tree Um ponteiro para a árvore a ser destruída.
 * @return Tree Retorna NULL após liberar a memória.
 */
Tree treeDestroy(Tree tree) {
  if (tree != NULL) {
    freeNode(tree->root);
    free(tree);
  }
  return NULL;
}

/**
 * @brief Imprime a árvore em ordem.
 * 
 * @param node Um ponteiro para o nó atual.
 */
void printInOrder(NodeT *node) {
  if (node != NULL) {
    printInOrder(node->left);
    stringPrint(toString(node->info));
    printInOrder(node->right);
  }
}

/**
 * @brief Imprime os dados da árvore binária (em ordem).
 * 
 * @param tree Ponteiro para a árvore binária.
 * @return 1 se o dado for encontrado, 0 caso contrário.
 */
int treePrint(Tree tree) {
  if (tree == NULL) return 0;
  printInOrder(tree->root);
  return 1;
}