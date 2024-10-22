#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stringlib.h>
#include <list.h>
#include <queue.h>
#include <stack.h>
#include <typeslib.h>

/**
 * @brief Estrutura que representa um valor de tipo genérico, 
 * com um ponteiro para os dados, o tipo de dado e o tamanho em bytes.
 */
typedef struct obj_t {
  void* data;    /**< Ponteiro para os dados armazenados */
  ObjType type;  /**< Tipo de dado representado */
  size_t size;   /**< Tamanho do tipo de dado em bytes */
} *obj;

/**
 * @brief Converte um valor genérico em um objeto obj.
 * 
 * @param value Ponteiro para o valor.
 * @param size Tamanho do valor em bytes.
 * @param type Tipo do valor.
 * @return Objeto obj ou NULL em caso de falha.
 */
obj voidToObj(void* value, size_t size, ObjType type) {
  // Verifica entrada
  if (value == NULL || size == 0) return NULL;

  // Aloca obj
  obj a = malloc(sizeof(struct obj_t));
  if (a == NULL) return NULL;

  // Aloca dados
  a->data = malloc(size);
  if (a->data == NULL) {
    free(a);
    return NULL;
  }

  // Define tamanho, tipo e copia dados
  a->size = size;
  a->type = type;
  memcpy(a->data, value, size);

  return a;
}

/**
 * @brief Converte um inteiro em um objeto obj.
 * 
 * @param value Valor inteiro a ser convertido.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Objeto obj contendo o valor int.
 */
obj intToObj(int value, size_t size) {
  return voidToObj(&value, sizeof(int), TYPE_INT); 
}

/**
 * @brief Converte um float em um objeto obj.
 * 
 * @param value Valor float a ser convertido.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Objeto obj contendo o valor float.
 */
obj floatToObj(float value, size_t size) {
  return voidToObj(&value, sizeof(float), TYPE_FLOAT);
}

/**
 * @brief Converte um double em um objeto obj.
 * 
 * @param value Valor double a ser convertido.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Objeto obj contendo o valor double.
 */
obj doubleToObj(double value, size_t size) {
  return voidToObj(&value, sizeof(double), TYPE_DOUBLE);
}

/**
 * @brief Converte um char em um objeto obj.
 * 
 * @param value Valor char a ser convertido.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Objeto obj contendo o valor char.
 */
obj charToObj(char value, size_t size) {
  return voidToObj(&value, sizeof(char), TYPE_CHAR);
}

/**
 * @brief Converte uma string literal em um objeto obj.
 * 
 * @param value Ponteiro para a string.
 * @param size Tamanho da string (não utilizado nesta função).
 * @return Objeto obj contendo a string.
 */
obj charPtrToObj(const char* value, size_t size) {
  // Aloca obj
  obj a = malloc(sizeof(struct obj_t));
  if (a == NULL) return NULL;

  // Define o tamanho da string (+1 para o terminador)
  a->size = strlen(value) + 1;

  // Aloca espaço para a string literal
  a->data = malloc(a->size);
  if (a->data == NULL) {
    free(a);
    return NULL;
  }

  // Copia a string para 'data'
  strcpy(a->data, value);

  // Define o tipo de dado como string
  a->type = TYPE_CHAR_PTR;

  return a;
}

/**
 * @brief Converte um valor booleano (bool) em um objeto obj.
 * 
 * @param value Valor booleano a ser convertido.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Objeto obj contendo o valor booleano.
 */
obj boolToObj(bool value, size_t size) {
  return voidToObj(&value, sizeof(bool), TYPE_BOOL);
}

/**
 * @brief Converte um objeto string em um objeto obj.
 * 
 * @param value Objeto string a ser convertido.
 * @param size Tamanho do objeto (não utilizado nesta função).
 * @return Objeto obj contendo o objeto string.
 */
obj stringToObj(string value, size_t size) {
  return voidToObj(&value, sizeof(string), TYPE_STRING);
}

/**
 * @brief Converte um objeto list em um objeto obj.
 * 
 * @param value Objeto list a ser convertido.
 * @param size Tamanho do objeto (não utilizado nesta função).
 * @return Objeto obj contendo o objeto list.
 */
obj listToObj(list value, size_t size) {
  return voidToObj(value, sizeof(list), TYPE_LIST);
}

/**
 * @brief Converte um objeto queue em um objeto obj.
 * 
 * @param value Objeto queue a ser convertido.
 * @param size Tamanho do objeto (não utilizado nesta função).
 * @return Objeto obj contendo o objeto queue.
 */
obj queueToObj(queue value, size_t size) {
  return voidToObj(value, sizeof(queue), TYPE_QUEUE);
}

/**
 * @brief Converte um objeto stack em um objeto obj.
 * 
 * @param value Objeto stack a ser convertido.
 * @param size Tamanho do objeto (não utilizado nesta função).
 * @return Objeto obj contendo o objeto stack.
 */
obj stackToObj(stack value, size_t size) {
  return voidToObj(value, sizeof(stack), TYPE_STACK);
}

/**
 * @brief Converte um valor genérico e desconhecido em um objeto obj.
 * 
 * @param value Ponteiro para o valor.
 * @param size Tamanho do valor em bytes.
 * @return Objeto obj contendo o valor.
 */
obj unknownToObj(void* value, size_t size) {
  return voidToObj(value, size, TYPE_UNKNOWN);
}

/**
 * @brief Libera a memória ocupada por um objeto obj.
 * 
 * @param a Objeto obj a ser destruído.
 * @return Retorna NULL após destruir o objeto.
 */
obj objDestroy(obj a) {
  // Verifica se o objeto é NULL
  if (a == NULL) return a;

  // Libera dados e o objeto
  free(a->data);
  free(a);

  return NULL;
}

/**
 * @brief Compara dois objetos obj.
 * 
 * @param a Primeiro objeto obj.
 * @param b Segundo objeto obj.
 * @return 0 se forem iguais, valor negativo se a < b, valor positivo se a > b.
 */
int objCmp(obj a, obj b) {
  // Verifica se ambos são NULL
  if (a == NULL && b == NULL) return 0;

  // Se um for NULL, o NULL é considerado menor
  if (a == NULL || b == NULL) return (a == NULL) ? -1 : 1;

  // Verifica se os dados de ambos são NULL
  if (a->data == NULL || b->data == NULL) return (a->data == NULL) ? -1 : 1;

  // Tipos diferentes são considerados iguais (0)
  if (a->type != b->type) return 0;

  // Compara com base no tipo
  switch (a->type) {
    case TYPE_INT:
      // Compara inteiros
      return (*(int*)a->data < *(int*)b->data) ? -1 : (*(int*)a->data > *(int*)b->data);
    case TYPE_FLOAT:
      // Compara floats
      return (*(float*)a->data > *(float*)b->data) - (*(float*)a->data < *(float*)b->data);
    case TYPE_DOUBLE:
      // Compara doubles
      return (*(double*)a->data > *(double*)b->data) - (*(double*)a->data < *(double*)b->data);
    case TYPE_CHAR:
      // Compara caracteres
      return (*(char*)a->data < *(char*)b->data) ? -1 : (*(char*)a->data > *(char*)b->data);
    case TYPE_CHAR_PTR:
      // Compara strings literais
      return strcmp((char*)a->data, (char*)b->data);
    case TYPE_BOOL:
      // Compara booleanos
      return (*(bool*)a->data == *(bool*)b->data) ? 0 : (*(bool*)a->data ? 1 : -1);
    case TYPE_STRING:
      // Compara Strings
      return stringCmp(*(string*)a->data, *(string*)b->data);
    case TYPE_LIST:
      // Compara Listas
      return listCmp(*(list*)a->data, *(list*)b->data);
    case TYPE_QUEUE:
      // Compara Filas
      return queueCmp(*(queue*)a->data, *(queue*)b->data);
    case TYPE_STACK:
      // Compara Pilhas
      return stackCmp(*(stack*)a->data, *(stack*)b->data);
    default:
      // Tipo desconhecido, retorna 0
      return 0;
  }
}

/**
 * @brief Retorna o tipo de dado de um objeto obj.
 * 
 * @param a Objeto obj.
 * @return O tipo de dado (ObjType).
 */
ObjType objGetType(obj a) {
  return (a == NULL) ? TYPE_UNKNOWN : a->type;
}

/**
 * @brief Retorna o ponteiro para os dados de um objeto obj.
 * 
 * @param a Objeto obj.
 * @return Ponteiro para os dados ou NULL se o objeto for inválido.
 */
void* objGetData(obj a) {
  return (a == NULL) ? NULL : a->data;
}

/**
 * @brief Retorna o tamanho em bytes de um objeto obj.
 * 
 * @param a Objeto obj.
 * @return O tamanho dos dados em bytes ou 0 se o objeto for inválido.
 */
size_t objGetSize(obj a) {
  return (a == NULL) ? 0 : a->size;
}

/** 
* @brief Exibe um valor do tipo obj na tela.
*
* @param a Objeto obj.
* @return 1 se o objeto é válido, 0 caso contrário.
*/
int objPrint(obj a) {
  // Verifica se 'a' é NULL
  if (a == NULL) return 0;
  
  // Exibe o dado com base no tipo
  switch (a->type) {
    case TYPE_INT:
      // Exibe inteiro 
      printf("%d", *(int*)a->data);
      break;
    case TYPE_FLOAT:
      // Exibe float
      printf("%f", *(float*)a->data);
      break;
    case TYPE_DOUBLE:
      // Exibe double
      printf("%lf", *(double*)a->data);
      break;
    case TYPE_CHAR:
      // Exibe char
      printf("%c", *(char*)a->data);
      break;
    case TYPE_CHAR_PTR:
      // Exibe string literal
      printf("%s", (char*)a->data);
      break;
    case TYPE_BOOL:
      // Exibe booleano
      printf("%s", *(bool*)a->data ? "true" : "false");
      break;
    case TYPE_STRING:
      // Exibe string
      stringPrint(*(string*)a->data);
      break;
    case TYPE_LIST:
      // Exibe Lista
      listPrint(*(list*)a->data);
      break;
    case TYPE_QUEUE:
      // Exibe Fila
      queuePrint(*(queue*)a->data);
      break;
    case TYPE_STACK:
      // Exibe stack
      stackPrint(*(stack*)a->data);
      break;
    default:
      // Tipo desconhecido
      printf("Unknown Type");
      break;
  }
  return 1;
}