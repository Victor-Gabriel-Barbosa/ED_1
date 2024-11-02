#include <tree.h>
#include <stdlib.h>
#include "stringlib.h"

/**
 * @brief Estrutura que representa um nó da árvore AVL.
 */
typedef struct tree_t {
  obj info;             /**< Informação armazenada na árvore */
  struct tree_t* left;  /**< Ponteiro para o filho esquerdo da árvore */
  struct tree_t* right; /**< Ponteiro para o filho direito da árvore */
  int treeHeight;       /**< Altura do nó para manter o balanceamento AVL */
} *tree;

/**
 * @brief Retorna o tamanho da estrutura tree_t em bytes.
 *
 * Esta função utiliza o operador sizeof para calcular o tamanho
 * da estrutura 'struct tree_t' em tempo de compilação. O tamanho
 * é útil para operações que envolvem a alocação de memória ou
 * manipulação de blocos de dados.
 *
 * @return size_t O tamanho da estrutura 'struct tree_t' em bytes.
 */
size_t sizeofTree() {
  return sizeof(struct tree_t);
}

/**
 * @brief Cria uma nova árvore vazia.
 * 
 * Aloca memória para uma nova árvore, inicializando o ponteiro da raiz como NULL.
 * 
 * @return Um ponteiro para a nova árvore criada.
 */
tree treeNew() {
  return NULL;
}

/**
 * @brief Libera a memória alocada para a árvore binária.
 * 
 * @param tre Um ponteiro para a árvore a ser liberada.
 * @return  NULL após liberar a memória.
 */
tree treeFree(tree tre) {
  if (tre == NULL) return NULL;  
  treeFree(tre->left); 
  treeFree(tre->right);  
  free(tre); 
  return NULL;
}

/**
 * @brief Verifica se a árvore é vazia.
 * 
 * Verifica se o ponteiro da raiz da árvore é NULL.
 * 
 * @param tre Um ponteiro para a árvore que será verificada.
 * @return 1 se a árvore estiver vazia, ou 0 se contiver elementos.
 */
int treeIsEmpty(const tree tre) {
  return (tre == NULL);
}

/**
 * @brief Calcula a altura da árvore AVL.
 * 
 * @param tre Um ponteiro para a árvore cuja altura será calculada.
 * @return A altura da árvore.
 */
size_t treeHeight(const tree tre) {
  return (tre == NULL) ? -1 : tre->treeHeight;
}

/**
 * @brief Calcula o fator de balanceamento do nó.
 *
 * @param tre Um ponteiro para o nó da árvore.
 * @return O fator de balanceamento do nó.
 */
int treeBalanceFactor(const tree tre) {
  return (tre == NULL) ? 0 : treeHeight(tre->left) - treeHeight(tre->right);
}

/**
 * @brief Atualiza a altura do nó.
 *
 * @param tre Um ponteiro para o nó da árvore.
 */
void treeUpdateHeight(tree tre) {
  if (tre != NULL) {
    size_t leftHeight = treeHeight(tre->left);
    size_t rightHeight = treeHeight(tre->right);
    tre->treeHeight = (size_t)((leftHeight > rightHeight ? leftHeight : rightHeight) + 1);
  }
}

/**
 * @brief Realiza uma rotação simples para a direita.
 *
 * @param y Um ponteiro para o nó desbalanceado.
 * @return Um ponteiro para a nova raiz após a rotação.
 */
tree treeRotateRight(tree y) {
  tree x = y->left;
  tree T2 = x->right;
  x->right = y;
  y->left = T2;
  treeUpdateHeight(y);
  treeUpdateHeight(x);
  return x;
}

/**
 * @brief Realiza uma rotação simples para a esquerda.
 *
 * @param x Um ponteiro para o nó desbalanceado.
 * @return Um ponteiro para a nova raiz após a rotação.
 */
tree treeRotateLeft(tree x) {
  tree y = x->right;
  tree T2 = y->left;
  y->left = x;
  x->right = T2;
  treeUpdateHeight(x);
  treeUpdateHeight(y);
  return y;
}

/**
 * @brief Balanceia o nó da árvore AVL.
 *
 * @param tre Um ponteiro para o nó desbalanceado.
 * @return Um ponteiro para o nó balanceado.
 */
tree treeBalance(tree tre) {
  treeUpdateHeight(tre);
  int bf = (int)treeBalanceFactor(tre);
  if (bf > 1 && treeBalanceFactor(tre->left) >= 0) return treeRotateRight(tre);
  if (bf > 1 && treeBalanceFactor(tre->left) < 0) {
    tre->left = treeRotateLeft(tre->left);
    return treeRotateRight(tre);
  }
  if (bf < -1 && treeBalanceFactor(tre->right) <= 0) return treeRotateLeft(tre);
  if (bf < -1 && treeBalanceFactor(tre->right) > 0) {
    tre->right = treeRotateRight(tre->right);
    return treeRotateLeft(tre);
  }
  return tre;
}

/**
 * @brief Conta a quantidade de galhos na árvore.
 * 
 * Um galho é definido como um nó que possui pelo menos um filho.
 * 
 * @param tre Um ponteiro para a árvore que será verificada.
 * @return A quantidade de galhos na árvore.
 */
int treeCountBranches(const tree tre) {
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
 * @return A quantidade de folhas na árvore.
 */
int treeCountLeaves(const tree tre) {
  if (tre == NULL) return 0; 
  if (tre->left == NULL && tre->right == NULL) return 1;
  return treeCountLeaves(tre->left) + treeCountLeaves(tre->right);
}

/**
 * @brief Conta o número total de nós na árvore.
 * 
 * @param tre Um ponteiro para a árvore a ser contada.
 * @return O número total de nós na árvore.
 */
int treeCountNodes(const tree tre) {
  return (tre == NULL) ? 0 : 1 + treeCountNodes(tre->left) + treeCountNodes(tre->right);
}

/**
 * @brief Insere um novo elemento na árvore AVL.
 *
 * @param tre Um ponteiro para a árvore onde o elemento será inserido.
 * @param info O valor a ser inserido na árvore.
 * @return Um ponteiro para a raiz da árvore após a inserção e balanceamento.
 */
tree treeInsert(tree tre, const obj info) {
  if (tre == NULL) {
    tree node = (tree)malloc(sizeof(struct tree_t));
    if (node == NULL) return NULL;
    node->info = objCopy(info);
    node->left = NULL;
    node->right = NULL;
    node->treeHeight = 0;
    return node;
  }
  if (objCmp(info, tre->info) < 0) tre->left = treeInsert(tre->left, info);
  else if (objCmp(info, tre->info) > 0) tre->right = treeInsert(tre->right, info);
  else return tre;
  return treeBalance(tre);
}

/**
 * @brief Remove um elemento da árvore AVL.
 *
 * @param tre Um ponteiro para a árvore de onde o elemento será removido.
 * @param info O valor a ser removido da árvore.
 * @return Um ponteiro para a raiz da árvore após a remoção e balanceamento.
 */
tree treeRemove(tree tre, const obj info) {
  if (tre == NULL) return NULL;
  if (objCmp(info, tre->info) < 0) tre->left = treeRemove(tre->left, info);
  else if (objCmp(info, tre->info) > 0) tre->right = treeRemove(tre->right, info);
  else {
    if (tre->left == NULL || tre->right == NULL) {
      tree temp = (tre->left != NULL) ? tre->left : tre->right;
      if (temp == NULL) {
        temp = tre;
        tre = NULL;
      } else *tre = *temp;
      free(temp);
    } else {
      tree temp = tre->right;
      while (temp->left != NULL) temp = temp->left;
      tre->info = temp->info;
      tre->right = treeRemove(tre->right, temp->info);
    }
  }
  if (tre == NULL) return tre;
  return treeBalance(tre);
}

/**
 * @brief Busca um elemento na árvore.
 * 
 * Verifica se o valor 'info' está presente na árvore.
 * 
 * @param tre Um ponteiro para a árvore onde a busca será realizada.
 * @param info O valor a ser buscado na árvore.
 * @return 1 se o valor for encontrado, ou 0 caso contrário.
 */
int treeSearch(const tree tre, const obj info) {
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
 * @return O valor máximo encontrado na árvore.
 */
obj treeFindMax(const tree tre) {
  if (tre == NULL) return NULL;
  tree current = tre;
  while (current->right != NULL) current = current->right;
  return current->info;
}

/**
 * @brief Encontra o nó com o valor mínimo na árvore.
 * 
 * @param tre Um ponteiro para a árvore onde será feita a busca.
 * @return O valor mínimo encontrado na árvore.
 */
obj treeFindMin(const tree tre) {
  if (tre == NULL) return NULL;
  tree current = tre;
  while (current->left != NULL) current = current->left;
  return current->info;
}

/**
 * @brief Inverte a árvore binária.
 * 
 * A função troca os nós esquerdo e direito de cada subárvore na árvore.
 * 
 * @param tre Um ponteiro para a árvore a ser invertida.
 * @return A árvore invertida.
 */
tree treeInvert(tree tre) {
  if (tre == NULL) return NULL; 
  tree temp = tre->left; 
  tre->left = treeInvert(tre->right);
  tre->right = treeInvert(temp); 
  return tre;
}

/**
 * @brief Cria uma cópia de uma árvore binária.
 *
 * @param tre A árvore a ser copiada.
 * @return Uma cópia da árvore, ou NULL se a alocação de memória falhar.
 */
tree treeCopy(const tree tre) {
  if (tre == NULL) return NULL;
  tree newTree = (tree)malloc(sizeof(struct tree_t));
  if (newTree == NULL) return NULL;
  newTree->info = objCopy(tre->info);
  newTree->left = treeCopy(tre->left);
  newTree->right = treeCopy(tre->right);
  return newTree;
}

/**
 * @brief Compara duas árvores binárias de forma semelhante ao strcmp.
 * 
 * @param tree1 Ponteiro para a primeira árvore.
 * @param tree2 Ponteiro para a segunda árvore.
 * @return 0 se as árvores forem iguais, um valor negativo se tree1 < tree2,
 * ou um valor positivo se tree1 > tree2.
 */
int treeCmp(const tree tree1, const tree tree2) {
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
 * @return A string resultante que representa a árvore.
 */
string treeToString(const tree tre) {
  if (tre == NULL) return stringNew();
  string currentStr = objToString(tre->info);
  string leftStr = treeToString(tre->left);
  string rightStr = treeToString(tre->right);
  string result = stringNew();
  stringAddChar(result, '<');
  stringAppend(result, currentStr);
  if (!stringIsEmpty(leftStr) || !stringIsEmpty(rightStr)) {
    if (!stringIsEmpty(leftStr)) {
      stringCat(result, ", ");
      stringAppend(result, leftStr);
    }
    if (!stringIsEmpty(rightStr)) {
      stringCat(result, ", ");
      stringAppend(result, rightStr);
    }
  }
  stringAddChar(result, '>');
  stringFree(currentStr);
  stringFree(leftStr);
  stringFree(rightStr);
  return result;
}


/**
 * @brief Imprime a árvore binária em ordem.
 * 
 * A função imprime os dados da árvore em ordem (in-order traversal).
 * 
 * @param tre Ponteiro para a árvore binária.
 * @return 1 se a árvore não for vazia, 0 se a árvore estiver vazia.
 */
int treePrint(const tree tre) {
  if (tre == NULL) return 0; 
  string str = treeToString(tre);
  if (str == NULL) return 0;
  stringPrint(str);
  stringFree(str);
  return 1; 
}