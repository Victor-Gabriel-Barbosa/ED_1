#include <map.h>
#include <stdlib.h>
#include "stringlib.h"

/**
 * @brief Estrutura que representa um nó da árvore binária.
 */
typedef struct map_t {
  obj info;            /**< Dados do nó, utilizando obj */
  struct map_t* left;  /**< Ponteiro para o filho esquerdo */
  struct map_t* right; /**< Ponteiro para o filho direito */
} *map;

/**
 * @brief Retorna o tamanho da estrutura map_t em bytes.
 *
 * Esta função utiliza o operador sizeof para calcular o tamanho
 * da estrutura `struct map_t` em tempo de compilação. O tamanho
 * é útil para operações que envolvem a alocação de memória ou
 * manipulação de blocos de dados.
 *
 * @return size_t O tamanho da estrutura `struct map_t` em bytes.
 */
size_t sizeofMap() {
  return sizeof(struct map_t);
}

/**
 * @brief Cria uma nova árvore vazia.
 * 
 * Aloca memória para uma nova árvore, inicializando o ponteiro da raiz como NULL.
 * 
 * @return Um ponteiro para a nova árvore criada.
 */
map mapNew() {
  return NULL;
}

/**
 * @brief Destrói a árvore e libera a memória associada.
 * 
 * @param tre Um ponteiro para a árvore a ser destruída.
 * @return  NULL após liberar a memória.
 */
map mapDestroy(map tre) {
  if (tre == NULL) return NULL;  
  mapDestroy(tre->left); 
  mapDestroy(tre->right);  
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
int mapIsEmpty(map tre) {
  return (tre == NULL);
}

/**
 * @brief Conta a quantidade de galhos na árvore.
 * 
 * Um galho é definido como um nó que possui pelo menos um filho.
 * 
 * @param tre Um ponteiro para a árvore que será verificada.
 * @return A quantidade de galhos na árvore.
 */
int mapCountBranches(map tre) {
  if (tre == NULL) return 0; 
  int count = 0;
  if (tre->left != NULL || tre->right != NULL) count = 1; 
  count += mapCountBranches(tre->left);
  count += mapCountBranches(tre->right);
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
int mapCountLeaves(map tre) {
  if (tre == NULL) return 0; 
  if (tre->left == NULL && tre->right == NULL) return 1;
  return mapCountLeaves(tre->left) + mapCountLeaves(tre->right);
}

/**
 * @brief Conta o número total de nós na árvore.
 * 
 * @param tre Um ponteiro para a árvore a ser contada.
 * @return O número total de nós na árvore.
 */
int mapCountNodes(map tre) {
  return (tre == NULL) ? 0 : 1 + mapCountNodes(tre->left) + mapCountNodes(tre->right);
}

/**
 * @brief Calcula a altura da árvore.
 * 
 * A altura é definida como o número de arestas no caminho mais longo da raiz até uma folha.
 * 
 * @param tre Um ponteiro para a árvore cuja altura será calculada.
 * @return A altura da árvore.
 */
int mapHeight(map tre) {
  if (tre == NULL) return -1;  
  int leftHeight = mapHeight(tre->left);
  int rightHeight = mapHeight(tre->right);
  return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

/**
 * @brief Insere um novo elemento na árvore.
 * 
 * Insere o valor `info` na posição correta na árvore de acordo com as regras da árvore binária de busca.
 * 
 * @param tre Um ponteiro para a árvore onde o elemento será inserido.
 * @param info O valor a ser inserido na árvore.
 * @return 1 se a inserção for bem-sucedida, ou 0 em caso de erro.
 */
map mapAdd(map tre, obj info) {
  map node = (map)malloc(sizeof(struct map_t));
  if (node == NULL) return tre;
  node->info = info;
  node->left = NULL;
  node->right = NULL;
  if (tre == NULL) return node;
  map current = tre;
  map parent = NULL;
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
 * @return 1 se o valor for encontrado, ou 0 caso contrário.
 */
int mapSearch(map tre, obj info) {
  if (tre == NULL) return 0;
  map current = tre;
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
obj mapFindMax(map tre) {
  if (tre == NULL) return NULL;  
  while (tre->right != NULL) tre = tre->right;
  return tre->info;
}

/**
 * @brief Encontra o nó com o valor mínimo na árvore.
 * 
 * @param tre Um ponteiro para a árvore onde será feita a busca.
 * @return O valor mínimo encontrado na árvore.
 */
obj mapFindMin(map tre) {
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
 * @return 1 se a remoção for bem-sucedida, ou 0 em caso de erro.
 */
map mapRemove(map tre, obj info) {
  if (tre == NULL) return NULL; 
  map current = tre;
  map parent = NULL;
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
    map child = (current->left != NULL) ? current->left : current->right;
    if (current == tre) tre = child;  
    else if (parent->left == current) parent->left = child;
    else parent->right = child;
    free(current);
  } else {
    map successor = current->right;
    map successorParent = current;
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
 * @return A árvore invertida.
 */
map mapInvert(map tre) {
  if (tre == NULL) return NULL; 
  map temp = tre->left; 
  tre->left = mapInvert(tre->right);
  tre->right = mapInvert(temp); 
  return tre;
}

/**
 * @brief Compara duas árvores binárias de forma semelhante ao strcmp.
 * 
 * @param map1 Ponteiro para a primeira árvore.
 * @param map2 Ponteiro para a segunda árvore.
 * @return 0 se as árvores forem iguais, um valor negativo se map1 < map2,
 * ou um valor positivo se map1 > map2.
 */
int mapCmp(map map1, map map2) {
  if (map1 == NULL && map2 == NULL) return 0; 
  if (map1 == NULL) return -1;
  if (map2 == NULL) return 1; 
  int cmp = objCmp(map1->info, map2->info);
  if (cmp != 0) return cmp; 
  int leftComparison = mapCmp(map1->left, map2->left);
  if (leftComparison != 0) return leftComparison;
  return mapCmp(map1->right, map2->right); 
}

/**
 * @brief Converte uma árvore binária em uma string.
 * 
 * A função percorre a árvore em pré-ordem e concatena os valores em uma string.
 * 
 * @param tre Um ponteiro para a árvore a ser convertida.
 * @return A string resultante que representa a árvore.
 */
string mapToString(map tre) {
  if (tre == NULL) return stringNew(); 
  string currentStr = toString(tre->info);
  string leftStr = mapToString(tre->left);
  string rightStr = mapToString(tre->right);
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
 * @return 1 se a árvore não for vazia, 0 se a árvore estiver vazia.
 */
int mapPrint(map tre) {
  if (tre == NULL) return 0; 
  string str = mapToString(tre);
  stringPrint(str);
  stringDestroy(str);
  return 1; 
}