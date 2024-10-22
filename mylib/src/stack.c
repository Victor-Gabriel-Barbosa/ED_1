#include <stdio.h>
#include <stdlib.h> 
#include <stdarg.h>
#include <string.h>
#include <stack.h>
#include <stringlib.h>

/**
 * @brief Estrutura do nó da pilha.
 * 
 * Cada nó contém um valor `info` e um ponteiro para o próximo nó da pilha.
 */
typedef struct nodeS {
  obj info;
  struct nodeS* prox; 
} NodeS;

/**
 * @brief Estrutura da pilha (stack).
 * 
 * A pilha contém um ponteiro para o topo ('top'), um contador 
 * de elementos (`N`), o tipo de elementos ('type') e o
 * tamanho dos elementos ('sizeType')
 */
typedef struct stack_t {
  NodeS* top;
  size_t N;
} *stack;

/**
 * @brief Cria uma nova pilha ou retorna a pilha existente.
 * 
 * @return Objeto para a nova pilha.
 */
stack stackNew() { 
  stack stk = (stack)malloc(sizeof(struct stack_t));
  if (stk == NULL) return stk; 
  stk->top = NULL;
  stk->N = 0;
  return stk;
} 

/**
 * @brief Destrói a pilha, liberando a memória alocada.
 * 
 * @param stk Objeto para a pilha que será destruída.
 * @return NULL para indicar que a pilha foi destruída.
 */
stack stackDestroy(stack stk) {
  if (stk == NULL) return NULL;
  NodeS* aux = stk->top;
  while (aux != NULL) {
    NodeS* temp = aux->prox;
    if (aux->info != NULL) aux->info = objDestroy(aux->info);
    free(aux);
    aux = temp;
  }
  free(stk); 
  return NULL; 
}

/**
 * @brief Verifica se a pilha está vazia.
 * 
 * @param stk Objeto para a pilha.
 * @return 1 se a pilha estiver vazia, 0 caso contrário.
 */
int stackIsEmpty(stack stk) {
  return (stk == NULL || stk->top == NULL);
}  

/**
 * @brief Retorna o tamanho atual da pilha.
 * 
 * @param stk Objeto para a pilha.
 * @return Tamanho da pilha (número de elementos).
 */
size_t stackSize(stack stk) {
  return (stk == NULL) ? 0 : stk->N;
}

/**
 * @brief Adiciona um novo elemento no topo da pilha.
 * 
 * @param stk Objeto para a pilha.
 * @param info Valor a ser empilhado (obj).
 * @return Objeto para a pilha atualizada, ou NULL em caso de falha.
 */
stack stackPush(stack stk, obj info) {
  if (stk == NULL) return NULL;
  NodeS* newNode = (NodeS*)malloc(sizeof(NodeS));
  if (newNode == NULL) return stk;
  newNode->info = info;
  newNode->prox = stk->top;
  stk->top = newNode;
  stk->N++;
  return stk;
}

/**
 * @brief Consulta o elemento no topo da pilha sem removê-lo.
 * 
 * @param stk Objeto para a pilha.
 * @param info Ponteiro onde será armazenado o valor do topo da pilha.
 * @return 1 se a operação foi bem-sucedida, ou 0 se a pilha estiver vazia.
 */
int stackTop(stack stk, obj* info) {
  if (stackIsEmpty(stk)) return 0;
  *info = stk->top->info;
  return 1;
}

/**
 * @brief Remove o elemento do topo da pilha.
 * 
 * @param stk Objeto para a pilha.
 * @param info Ponteiro onde será armazenado o valor removido do topo (obj).
 * @return Objeto da pilha atualizada, ou NULL se a pilha estiver vazia.
 */
stack stackPop(stack stk, obj* info) {
  if (stackIsEmpty(stk)) return stk;
  NodeS* temp = stk->top;
  *info = temp->info;
  stk->top = temp->prox;
  free(temp); 
  stk->N--;
  return stk;
} 

/**
 * Compara duas pilhas (stack).
 * 
 * @param stk1 A primeira pilha a ser comparada.
 * @param stk2 A segunda pilha a ser comparada.
 * 
 * @return 
 * - 1 se stk1 for maior que stk2 (em termos de tamanho ou conteúdo),
 * - -1 se stk2 for maior que stk1,
 * - 0 se ambas as pilha forem iguais.
 */
int stackCmp(stack stk1, stack stk2) {
  if (stk1 == NULL && stk2 == NULL) return 0; 
  if (stk1 == NULL) return -1; 
  if (stk2 == NULL) return 1; 
  if (stk1->N > stk2->N) return 1; 
  if (stk1->N < stk2->N) return -1; 
  NodeS* aux1 = stk1->top;
  NodeS* aux2 = stk2->top;
  while (aux1 != NULL && aux2 != NULL) {
    if (objCmp(aux1->info, aux2->info) != 0) return (objCmp(aux1->info, aux2->info) > 0) ? 1 : -1;
    aux1 = aux1->prox;
    aux2 = aux2->prox;
  }
  return 0;
}

/**
 * @brief Converte uma pilha para uma string.
 * 
 * @param stk Pilha a ser convertida.
 * @return string da pilha convertida.
 */
string stackToString(stack stk) {
  if (stackIsEmpty(stk)) return NULL;
  NodeS* aux = stk->top;
  string str = stringNew();
  stringAddChar(str, '{');
  while (aux != NULL) {
    string temp = toString(aux->info);
    str = stringAppend(str, temp);
    if (aux->prox != NULL) str = stringCat(str, ", ");
    aux = aux->prox;
  }
  stringAddChar(str, '}');
  return str;
}

/** 
* @brief Exibe todos os elementos de uma pilha.
*
* @param qeu Objeto para a pilha.
* @return 1 se a pilha não é vazia, 0 caso contrário.
*/
int stackPrint(stack stk) {
  if (stackIsEmpty(stk)) return 0;
  stringPrint(stackToString(stk));
  return 1;
}  