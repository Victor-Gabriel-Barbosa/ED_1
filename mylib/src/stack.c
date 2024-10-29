#include <stdio.h>
#include <stdlib.h> 
#include <stdarg.h>
#include <string.h>
#include "stringlib.h"
#include "stack.h"

/**
 * @brief Estrutura que representa um nó em uma pilha.
 */
typedef struct nodeS {
  obj info;           /**< Informação armazenada na pilha */
  struct nodeS* prox; /**< Ponteiro para o próximo nó da pilha */
} NodeS;

/**
 * @brief Estrutura que representa uma pilha.
 */
typedef struct stack_t {
  NodeS* top; /**< Topo da pilha */
  size_t N;   /**< Contador de elementos */
} *stack;

/**
 * @brief Calcula o tamanho em bytes da estrutura de dados 'stack_t'.
 * 
 * Esta função utiliza o operador 'sizeof' para retornar o tamanho em bytes da estrutura
 * 'stack_t', que representa um nó ou elemento da pilha. Ela não retorna o número de 
 * elementos presentes na pilha, mas sim a quantidade de memória que um único elemento 
 * dessa estrutura ocupa.
 * 
 * @return O tamanho em bytes da estrutura 'stack_t'.
 */
size_t sizeofStack() {
  return sizeof(struct stack_t);
}

/**
 * @brief Cria uma nova pilha.
 * 
 * Esta função aloca memória para uma nova estrutura de pilha ('stack_t'), inicializa 
 * seus membros e retorna um ponteiro para a pilha criada. Se a alocação de memória 
 * falhar, a função retorna 'NULL'.
 * 
 * @return Um ponteiro para a nova pilha, ou NULL se a alocação de memória falhar.
 */
stack stackNew() { 
  stack stk = (stack)malloc(sizeof(struct stack_t));
  if (stk == NULL) return stk; 
  stk->top = NULL;
  stk->N = 0;
  return stk;
} 

/**
 * @brief Destrói uma pilha e libera a memória associada a ela.
 * 
 * Esta função percorre todos os elementos da pilha e libera a memória 
 * ocupada por cada nó e seus dados. Após liberar todos os nós, a função 
 * também libera a memória alocada para a estrutura da pilha. Se a pilha 
 * fornecida for 'NULL', a função não faz nada e retorna 'NULL'.
 * 
 * @param stk Ponteiro para a pilha a ser destruída.
 * @return 'NULL' após liberar a pilha.
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
 * Esta função determina se uma pilha está vazia verificando se o ponteiro 
 * da pilha é 'NULL' ou se o topo da pilha é 'NULL'. A pilha é considerada 
 * vazia se não existir uma estrutura de pilha alocada ou se não houver 
 * elementos na pilha.
 * 
 * @param stk Ponteiro para a pilha a ser verificada.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int stackIsEmpty(const stack stk) {
  return (stk == NULL || stk->top == NULL);
}  

/**
 * @brief Obtém o tamanho da pilha.
 * 
 * Esta função retorna o número de elementos presentes na pilha. Se a pilha 
 * fornecida for 'NULL', a função retorna 0, indicando que a pilha não possui 
 * elementos. Caso contrário, retorna o valor armazenado no membro 'N', que 
 * representa a quantidade de elementos na pilha.
 * 
 * @param stk Ponteiro para a pilha cuja quantidade de elementos deve ser verificada.
 * @return O número de elementos na pilha. Retorna 0 se a pilha for NULL'.
 */
size_t stackSize(const stack stk) {
  return (stk == NULL) ? 0 : stk->N;
}

/**
 * @brief Adiciona um elemento à pilha.
 * 
 * Esta função insere um novo elemento no topo da pilha. Se a pilha fornecida 
 * for 'NULL', a função não realiza nenhuma operação e retorna 'NULL'. A 
 * função tenta alocar memória para um novo nó, e se a alocação falhar, ela 
 * retorna a pilha sem alterações. Caso a alocação seja bem-sucedida, o novo 
 * elemento é adicionado ao topo da pilha e o contador de elementos é 
 * incrementado.
 * 
 * @param stk Ponteiro para a pilha onde o elemento deve ser adicionado.
 * @param info O elemento a ser adicionado à pilha.
 * @return Ponteiro para a pilha atualizada, ou a pilha inalterada se estiver vazia.
 */
stack stackPush(stack stk, obj info) {
  if (stk == NULL) return NULL;
  NodeS* newNode = (NodeS*)malloc(sizeof(NodeS));
  if (newNode == NULL) return stk;
  newNode->info = objCopy(info);
  newNode->prox = stk->top;
  stk->top = newNode;
  stk->N++;
  return stk;
}

/**
 * @brief Obtém o elemento do topo da pilha.
 * 
 * Esta função recupera o elemento no topo da pilha e o armazena no 
 * endereço de memória apontado pelo parâmetro 'info'. Se a pilha estiver 
 * vazia, a função retorna 0 e não altera o valor de 'info'. Se a pilha 
 * não estiver vazia, o elemento do topo é copiado para 'info' e a 
 * função retorna 1, indicando que a operação foi bem-sucedida.
 * 
 * @param stk Ponteiro para a pilha da qual o elemento do topo deve ser recuperado.
 * @param info Ponteiro para a variável onde o elemento do topo será armazenado.
 * @return 1 se a operação for bem-sucedida, ou 0 se a pilha estiver vazia.
 */
int stackTop(const stack stk, obj* info) {
  if (stackIsEmpty(stk)) return 0;
  *info = stk->top->info;
  return 1;
}

/**
 * @brief Remove e retorna o elemento do topo da pilha.
 * 
 * Esta função remove o elemento no topo da pilha e o armazena no 
 * endereço de memória apontado pelo parâmetro 'info'. Se a pilha estiver 
 * vazia, a função não realiza nenhuma operação e retorna a pilha original. 
 * Caso contrário, o elemento do topo é copiado para 'info', o nó do topo é 
 * liberado e o contador de elementos é decrementado.
 * 
 * @param stk Ponteiro para a pilha da qual o elemento do topo deve ser removido.
 * @param info Ponteiro para a variável onde o elemento removido será armazenado.
 * @return Ponteiro para a pilha atualizada, ou a pilha inalterada se estiver vazia.
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
 * @brief Cria uma cópia de uma pilha.
 *
 * @param stk A pilha a ser copiada.
 * @return Uma cópia da pilha, ou NULL se a alocação de memória falhar.
 */
 stack stackCopy(const stack stk) {
  if (stk == NULL) return NULL;
  stack newStack = stackNew();
  NodeS* aux = stk->top;
  while (aux!= NULL) {
    stackPush(newStack, objCopy(aux->info));
    aux = aux->prox;
  }
  return newStack;
}

/**
 * @brief Compara duas pilhas.
 * 
 * Esta função compara duas pilhas, verificando sua estrutura e o conteúdo 
 * dos elementos. A comparação é realizada em duas etapas: primeiro, a 
 * função verifica se ambas as pilhas são 'NULL', se uma delas é 'NULL', 
 * ou se têm tamanhos diferentes. Se uma pilha é 'NULL' e a outra não, a 
 * pilha 'NULL' é considerada menor. Se ambas as pilhas têm o mesmo 
 * tamanho, a função compara seus elementos do topo para baixo, utilizando 
 * uma função de comparação de objetos ('objCmp').
 * 
 * @param stk1 Ponteiro para a primeira pilha a ser comparada.
 * @param stk2 Ponteiro para a segunda pilha a ser comparada.
 * @return 0 se as pilhas forem iguais, -1 se a primeira pilha for menor, 1 se a primeira pilha for maior
 */
int stackCmp(const stack stk1, const stack stk2) {
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
 * @brief Converte uma pilha em uma representação de string.
 * 
 * Esta função gera uma string que representa todos os elementos da pilha, 
 * formatando-os entre chaves '{}'. Se a pilha estiver vazia, a função 
 * retorna 'NULL'. A função percorre os elementos da pilha a partir do topo, 
 * utilizando a função 'toString' para converter cada elemento em uma 
 * string. As strings resultantes são concatenadas, separadas por vírgulas. 
 * Após a construção da string final, ela é retornada.
 * 
 * @param stk Ponteiro para a pilha a ser convertida em string.
 * @return Uma string representando a pilha, ou NULL se a pilha estiver vazia.
 */
string stackToString(const stack stk) {
  if (stackIsEmpty(stk)) return NULL;
  NodeS* aux = stk->top;
  string str = stringNew();
  stringAddChar(str, '{');
  while (aux != NULL) {
    string temp = toString(aux->info);
    str = stringAppend(str, temp);
    stringDestroy(temp);
    if (aux->prox != NULL) str = stringCat(str, ", ");
    aux = aux->prox;
  }
  stringAddChar(str, '}');
  return str;
}

/**
 * @brief Imprime os elementos da pilha.
 * 
 * Esta função imprime todos os elementos da pilha na saída padrão. Se a 
 * pilha estiver vazia, a função retorna 0 e não realiza nenhuma operação. 
 * Caso contrário, a função converte a pilha em uma representação de string 
 * usando 'stackToString', imprime essa string com 'stringPrint', e em seguida 
 * libera a memória alocada para a string. A função retorna 1 ao final 
 * indicando que a impressão foi bem-sucedida.
 * 
 * @param stk Ponteiro para a pilha a ser impressa.
 * @return 1 se a pilha foi impressa com sucesso, ou 0 se a pilha estiver vazia.
 */
int stackPrint(const stack stk) {
  if (stackIsEmpty(stk)) return 0;
  string str = stackToString(stk);
  if (str == NULL) return 0;
  stringPrint(str);
  stringDestroy(str);
  return 1;
}  