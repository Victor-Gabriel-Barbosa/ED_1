#include <tree.h>
#include <stdlib.h>
#include <stringlib.h>

/**
 * @brief Estrutura que representa um nó da árvore binária.
 */
typedef struct tree_t {
  obj info;               /**< Dados do nó, utilizando obj */
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
 * @brief Verifica se a árvore é vazia.
 * 
 * Verifica se o ponteiro da raiz da árvore é NULL.
 * 
 * @param tre Um ponteiro para a árvore que será verificada.
 * @return int Retorna 1 se a árvore estiver vazia, ou 0 se contiver elementos.
 */
int treeIsEmpty(tree tre) {
  return (tre == NULL);
}

/**
 * @brief Conta a quantidade de galhos na árvore.
 * 
 * Um galho é definido como um nó que possui pelo menos um filho.
 * 
 * @param tre Um ponteiro para a árvore que será verificada.
 * @return int A quantidade de galhos na árvore.
 */
int treeCountBranches(tree tre) {
  if (tre == NULL) return 0; 
  int count = 0;
  if (tre->left != NULL || tre->right != NULL) count = 1; 
  count += treeCountBranches(tre->left);
  count += treeCountBranches(tre->right);
  return count;
}

/**
 * @brief Conta a quantidade de folhas na árvore.
 * 
 * Uma folha é definida como um nó que não possui filhos.
 * 
 * @param tre Um ponteiro para a árvore que será verificada.
 * @return int A quantidade de folhas na árvore.
 */
int treeCountLeaves(tree tre) {
  if (tre == NULL) return 0; 
  if (tre->left == NULL && tre->right == NULL) return 1;
  return treeCountLeaves(tre->left) + treeCountLeaves(tre->right);
}

/**
 * @brief Conta o número total de nós na árvore.
 * 
 * @param tre Um ponteiro para a árvore a ser contada.
 * @return int O número total de nós na árvore.
 */
int treeCountNodes(tree tre) {
  return (tre == NULL) ? 0 : 1 + treeCountNodes(tre->left) + treeCountNodes(tre->right);
}

/**
 * @brief Calcula a altura da árvore.
 * 
 * A altura é definida como o número de arestas no caminho mais longo da raiz até uma folha.
 * 
 * @param tre Um ponteiro para a árvore cuja altura será calculada.
 * @return int A altura da árvore.
 */
int treeHeight(tree tre) {
  if (tre == NULL) return -1;  
  int leftHeight = treeHeight(tre->left);
  int rightHeight = treeHeight(tre->right);
  return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
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
tree treeAdd(tree tre, obj info) {
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
 * @brief Encontra o nó com o valor máximo na árvore.
 * 
 * @param tre Um ponteiro para a árvore onde será feita a busca.
 * @return obj O valor máximo encontrado na árvore.
 */
obj treeFindMax(tree tre) {
  if (tre == NULL) return NULL;  
  while (tre->right != NULL) tre = tre->right;
  return tre->info;
}

/**
 * @brief Encontra o nó com o valor mínimo na árvore.
 * 
 * @param tre Um ponteiro para a árvore onde será feita a busca.
 * @return obj O valor mínimo encontrado na árvore.
 */
obj treeFindMin(tree tre) {
  if (tre == NULL) return NULL; 
  while (tre->left != NULL) tre = tre->left;
  return tre->info;
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
 * @brief Inverte a árvore binária.
 * 
 * A função troca os nós esquerdo e direito de cada subárvore na árvore.
 * 
 * @param tre Um ponteiro para a árvore a ser invertida.
 * @return tree Retorna a árvore invertida.
 */
tree treeInvert(tree tre) {
  if (tre == NULL) return NULL; 
  tree temp = tre->left; 
  tre->left = treeInvert(tre->right);
  tre->right = treeInvert(temp); 
  return tre;
}

/**
 * @brief Compara duas árvores binárias de forma semelhante ao strcmp.
 * 
 * @param tree1 Ponteiro para a primeira árvore.
 * @param tree2 Ponteiro para a segunda árvore.
 * @return 0 se as árvores forem iguais, um valor negativo se tree1 < tree2,
 * ou um valor positivo se tree1 > tree2.
 */
int treeCmp(tree tree1, tree tree2) {
  if (tree1 == NULL && tree2 == NULL) return 0; 
  if (tree1 == NULL) return -1;
  if (tree2 == NULL) return 1; 
  int cmp = objCmp(tree1->info, tree2->info);
  if (cmp != 0) return cmp; 
  int leftComparison = treeCmp(tree1->left, tree2->left);
  if (leftComparison != 0) return leftComparison;
  return treeCmp(tree1->right, tree2->right); 
}

/**
 * @brief Converte uma árvore binária em uma string.
 * 
 * A função percorre a árvore em pré-ordem e concatena os valores em uma string.
 * 
 * @param tre Um ponteiro para a árvore a ser convertida.
 * @return string A string resultante que representa a árvore.
 */
string treeToString(tree tre) {
  if (tre == NULL) return stringNew(); 
  string currentStr = toString(tre->info);
  string leftStr = treeToString(tre->left);
  string rightStr = treeToString(tre->right);
  string result = stringNew(); 
  stringAddChar(result, '<'); 
  result = stringAppend(result, currentStr); 
  if (leftStr != NULL) result = stringAppend(result, leftStr);
  if (leftStr != NULL || rightStr != NULL) result = stringCat(result, ", "); 
  if (rightStr != NULL) result = stringAppend(result, rightStr);
  stringAddChar(result, '>'); 
  stringDestroy(currentStr);
  stringDestroy(leftStr);
  stringDestroy(rightStr); 
  return result; 
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
  string str = treeToString(tre);
  stringPrint(str);
  stringDestroy(str);
  return 1; 
}