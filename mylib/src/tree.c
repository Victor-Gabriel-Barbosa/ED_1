#include <tree.h>
#include <stdlib.h>
#include <stringlib.h>

/**
 * @brief Estrutura que representa um nó da árvore binária.
 */
typedef struct tree_t {
  obj info;             /**< Dados do nó, utilizando obj */
  struct tree_t* left;    /**< Ponteiro para o filho esquerdo */
  struct tree_t* right;   /**< Ponteiro para o filho direito */
} *tree;

/**
 * @brief Cria uma nova árvore vazia.
 * 
 * Aloca memória para uma nova árvore, inicializando o ponteiro da raiz como NULL.
 * 
 * @return tree Um ponteiro para a nova árvore criada.
 */
tree treeNew() {
  return NULL;
}

/**
 * @brief Insere um novo elemento na árvore.
 * 
 * Insere o valor `info` na posição correta na árvore de acordo com as regras da árvore binária de busca.
 * 
 * @param tre Um ponteiro para a árvore onde o elemento será inserido.
 * @param info O valor a ser inserido na árvore.
 * @return int Retorna 1 se a inserção for bem-sucedida, ou 0 em caso de erro.
 */
tree treeInsert(tree tre, obj info) {
  tree node = (tree)malloc(sizeof(struct tree_t));
  if (node == NULL) return tre;
  node->info = info;
  node->left = NULL;
  node->right = NULL;
  if (tre == NULL) return node;
  tree current = tre;
  tree parent = NULL;
  while (current != NULL) {
    parent = current; 
    if (objCmp(info, current->info) < 0) current = current->left;
    else current = current->right;
  }
  if (objCmp(info, parent->info) < 0) parent->left = node;
  else parent->right = node;
  return tre; 
}

/**
 * @brief Busca um elemento na árvore.
 * 
 * Verifica se o valor `info` está presente na árvore.
 * 
 * @param tre Um ponteiro para a árvore onde a busca será realizada.
 * @param info O valor a ser buscado na árvore.
 * @return int Retorna 1 se o valor for encontrado, ou 0 caso contrário.
 */
int treeSearch(tree tre, obj info) {
  if (tre == NULL) return 0;
  tree current = tre;
  while (current != NULL) {
    if (objCmp(info, current->info) == 0) return 1; 
    else if (objCmp(info, current->info) < 0) current = current->left;
    else current = current->right;
  }
  return 0;  
}

/**
 * @brief Remove um elemento da árvore.
 * 
 * Remove o nó contendo o valor `info` da árvore.
 * 
 * @param tre Um ponteiro para a árvore de onde o elemento será removido.
 * @param info O valor a ser removido da árvore.
 * @return int Retorna 1 se a remoção for bem-sucedida, ou 0 em caso de erro.
 */
tree treeRemove(tree tre, obj info) {
  if (tre == NULL) return NULL; 
  tree current = tre;
  tree parent = NULL;
  while (current != NULL && objCmp(info, current->info) != 0) {
    parent = current;
    if (objCmp(info, current->info) < 0) current = current->left;
    else current = current->right;
  }
  if (current == NULL) return tre;
  if (current->left == NULL && current->right == NULL) {
    if (current == tre) tre = NULL;
    else if (parent->left == current) parent->left = NULL;
    else parent->right = NULL;
    free(current);
  }
  else if (current->left == NULL || current->right == NULL) {
    tree child = (current->left != NULL) ? current->left : current->right;
    if (current == tre) tre = child;  
    else if (parent->left == current) parent->left = child;
    else parent->right = child;
    free(current);
  } else {
    tree successor = current->right;
    tree successorParent = current;
    while (successor->left != NULL) {
      successorParent = successor;
      successor = successor->left;
    }
    current->info = successor->info;
    if (successorParent->left == successor) successorParent->left = successor->right; 
    else successorParent->right = successor->right;
    free(successor);
  }
  return tre;
}

/**
 * @brief Destrói a árvore e libera a memória associada.
 * 
 * @param tre Um ponteiro para a árvore a ser destruída.
 * @return tree Retorna NULL após liberar a memória.
 */
tree treeDestroy(tree tre) {
  if (tre == NULL) return NULL;  
  treeDestroy(tre->left); 
  treeDestroy(tre->right);  
  free(tre); 
  return NULL;
}

/**
 * @brief Imprime a árvore binária em ordem.
 * 
 * A função imprime os dados da árvore em ordem (in-order traversal).
 * 
 * @param tre Ponteiro para a árvore binária.
 * @return int Retorna 1 se a árvore não for vazia, 0 se a árvore estiver vazia.
 */
int treePrint(tree tre) {
  if (tre == NULL) return 0; 
  if (tre->left != NULL) treePrint(tre->left);
  stringPrint(toString(tre->info));
  if (tre->right != NULL) treePrint(tre->right);
  return 1; 
}