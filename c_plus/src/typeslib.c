#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringlib.h"
#include "typeslib.h"
#include "list.h"
#include "queue.h"
#include "stack.h"
#include "tree.h"
/**
 * @brief Estrutura que representa um valor de tipo genérico, 
 * com um ponteiro para os dados, o tipo de dado e o tamanho em bytes.
 */
typedef struct obj_t {
  void* data;   /**< Ponteiro para os dados armazenados */
  ObjType type; /**< Tipo de dado representado */
  size_t size;  /**< Tamanho do tipo de dado em bytes */
} *obj;

/**
 * @brief Converte um valor genérico em um objeto.
 * 
 * @param value Ponteiro para o valor.
 * @param size Tamanho do valor em bytes.
 * @param type Tipo do valor.
 * @return Objeto ou NULL em caso de falha.
 */
obj voidToObj(void* value, size_t size, ObjType type) {
  if (value == NULL || size == 0) return NULL;
  obj a = malloc(sizeof(struct obj_t));
  if (a == NULL) return NULL;
  a->data = malloc(size);
  if (a->data == NULL) {
    free(a);
    return NULL;
  }
  a->size = size;
  a->type = type;
  memcpy(a->data, value, size);
  return a;
}

/**
 * @brief Converte um inteiro em um objeto.
 * 
 * @param value Valor inteiro a ser convertido.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Objeto contendo o valor int.
 */
obj intToObj(int value, size_t size) {
  return voidToObj(&value, sizeof(int), TYPE_INT); 
}

/**
 * @brief Converte um float em um objeto.
 * 
 * @param value Valor float a ser convertido.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Objeto contendo o valor float.
 */
obj floatToObj(float value, size_t size) {
  return voidToObj(&value, sizeof(float), TYPE_FLOAT);
}

/**
 * @brief Converte um double em um objeto.
 * 
 * @param value Valor double a ser convertido.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Objeto contendo o valor double.
 */
obj doubleToObj(double value, size_t size) {
  return voidToObj(&value, sizeof(double), TYPE_DOUBLE);
}

/**
 * @brief Converte um char em um objeto.
 * 
 * @param value Valor char a ser convertido.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Objeto contendo o valor char.
 */
obj charToObj(char value, size_t size) {
  return voidToObj(&value, sizeof(char), TYPE_CHAR);
}

/**
 * @brief Converte uma string literal (char*) em um objeto.
 * 
 * @param value Ponteiro para a string.
 * @param size Tamanho da string (não utilizado nesta função).
 * @return Objeto contendo a string.
 */
obj charPtrToObj(const char* value, size_t size) {
  obj a = malloc(sizeof(struct obj_t));
  if (a == NULL) return NULL;
  a->size = strlen(value) + 1;
  a->data = malloc(a->size);
  if (a->data == NULL) {
    free(a);
    return NULL;
  }
  strcpy(a->data, value);
  a->type = TYPE_CHAR_PTR;
  return a;
}

/**
 * @brief Converte um valor booleano (bool) em um objeto.
 * 
 * @param value Valor booleano a ser convertido.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Objeto contendo o valor booleano.
 */
obj boolToObj(bool value, size_t size) {
  return voidToObj(&value, sizeof(bool), TYPE_BOOL);
}

/**
 * @brief Converte um objeto string em um objeto.
 * 
 * @param value Objeto string a ser convertido.
 * @param size Tamanho do objeto (não utilizado nesta função).
 * @return Objeto contendo o objeto string.
 */
obj stringToObj(string value, size_t size) {
  return voidToObj(value, sizeofString(), TYPE_STRING);
}

/**
 * @brief Converte um objeto list em um objeto.
 * 
 * @param value Objeto list a ser convertido.
 * @param size Tamanho do objeto (não utilizado nesta função).
 * @return Objeto contendo o objeto list.
 */
obj listToObj(list value, size_t size) {
  return voidToObj(value, sizeofList(), TYPE_LIST);
}

/**
 * @brief Converte um objeto queue em um objeto.
 * 
 * @param value Objeto queue a ser convertido.
 * @param size Tamanho do objeto (não utilizado nesta função).
 * @return Objeto contendo o objeto queue.
 */
obj queueToObj(queue value, size_t size) {
  return voidToObj(value, sizeofQueue(), TYPE_QUEUE);
}

/**
 * @brief Converte um objeto stack em um objeto.
 * 
 * @param value Objeto stack a ser convertido.
 * @param size Tamanho do objeto (não utilizado nesta função).
 * @return Objeto contendo o objeto stack.
 */
obj stackToObj(stack value, size_t size) {
  return voidToObj(value, sizeofStack(), TYPE_STACK);
}

/**
 * @brief Converte uma árvore abstrata (tree) para obj.
 * 
 * @param value Estrutura tree.
 * @param size Tamanho da árvore (não utilizado nesta função).
 * @return Objeto contendo a árvore.
 */
obj treeToObj(tree value, size_t size) {
  return voidToObj(value, sizeofTree(), TYPE_TREE);
}

/**
 * @brief Converte um objeto abstrato (obj) para obj.
 * 
 * @param value Estrutura objeto.
 * @param size Tamanho do objeto (não utilizado nesta função).
 * @return Objeto contendo o objeto.
 */
obj objToObj(obj value, size_t size) {
  return voidToObj(value->data, value->size, value->type);
}

/**
 * @brief Converte um valor genérico e desconhecido em um objeto.
 * 
 * @param value Ponteiro para o valor.
 * @param size Tamanho do valor em bytes.
 * @return Objeto contendo o valor.
 */
obj unknownToObj(void* value, size_t size) {
  return voidToObj(&value, size, TYPE_UNKNOWN);
}

/**
 * @brief Libera a memória ocupada por um objeto.
 * 
 * @param a Objeto a ser destruído.
 * @return Retorna NULL após destruir o objeto.
 */
obj objFree(obj a) {
  if (a == NULL) return a;
  free(a->data);
  free(a);
  return NULL;
}

/**
 * @brief Cria uma cópia de um objeto.
 * 
 * @param a Objeto a ser copiado.
 * @return Objeto cópia, NULL em caso de falha.
 */
obj objCopy(const obj a) {
  obj b = malloc(sizeof(struct obj_t));
  if (b == NULL) return NULL;
  b->size = a->size;
  b->type = a->type;
  b->data = malloc(a->size);
  if (b->data == NULL) {
    free(b);
    return NULL;
  }
  switch (a->type) {
    case TYPE_STRING: {
      string str = stringCopy((string)a->data);
      if (str == NULL) {
        free(b->data);
        free(b);
        return NULL;
      }
      b->data = str;
      break;
    }
    case TYPE_LIST: {
      list lst = listCopy((list)a->data);
      if (lst == NULL) {
        free(b->data);
        free(b);
        return NULL;
      }
      b->data = lst; 
      break;
    }
    case TYPE_QUEUE: {
      queue qeu = queueCopy((queue)a->data);
      if (qeu == NULL) {
        free(b->data);
        free(b);
        return NULL;
      }
      b->data = qeu;  
      break;
    }
    case TYPE_STACK: {
      stack stk = stackCopy((stack)a->data);
      if (stk == NULL) {
        free(b->data);
        free(b);
        return NULL;
      }
      b->data = stk;
      break;
    }
    case TYPE_TREE: {
      tree tre = treeCopy((tree)a->data);
      if (tre == NULL) {
        free(b->data);
        free(b);
        return NULL;
      }
      b->data = tre; 
      break;
    }
    default: {
      memcpy(b->data, a->data, a->size); 
      break;
    }
  }
  return b; 
}


/**
 * @brief Compara dois objetos obj.
 * 
 * @param a Primeiro objeto.
 * @param b Segundo objeto.
 * @return 0 se forem iguais, valor negativo se a < b, valor positivo se a > b.
 */
int objCmp(obj a, obj b) {
  if (a == NULL || b == NULL) return (a == b) ? 0 : (a == NULL) ? -1 : 1;
  if (a->data == NULL || b->data == NULL) return (a->data == b->data) ? 0 : (a->data == NULL) ? -1 : 1;
  if (a->type != b->type) return a->type - b->type;
  switch (a->type) {
    case TYPE_INT:
      return (*(int*)a->data < *(int*)b->data) ? -1 : (*(int*)a->data > *(int*)b->data);
    case TYPE_FLOAT:
      return (*(float*)a->data > *(float*)b->data) - (*(float*)a->data < *(float*)b->data);
    case TYPE_DOUBLE:
      return (*(double*)a->data > *(double*)b->data) - (*(double*)a->data < *(double*)b->data);
    case TYPE_CHAR:
      return (*(char*)a->data < *(char*)b->data) ? -1 : (*(char*)a->data > *(char*)b->data);
    case TYPE_CHAR_PTR:
      return strcmp((char*)a->data, (char*)b->data);
    case TYPE_BOOL:
      return (*(bool*)a->data == *(bool*)b->data) ? 0 : (*(bool*)a->data ? 1 : -1);
    case TYPE_STRING:
      return stringCmp((string)a->data, (string)b->data);
    case TYPE_LIST:
      return listCmp((list)a->data, (list)b->data);
    case TYPE_QUEUE:
      return queueCmp((queue)a->data, (queue)b->data);
    case TYPE_STACK:
      return stackCmp((stack)a->data, (stack)b->data);
    case TYPE_TREE:
      return treeCmp((tree)a->data, (tree)b->data);
    case TYPE_UNKNOWN:
      return memcmp(a->data, b->data, a->size);
    default:
      return -1;
  }
}

/**
 * @brief Retorna o tipo de dado de um objeto.
 * 
 * @param a Objeto.
 * @return O tipo de dado (ObjType).
 */
ObjType objGetType(obj a) {
  return (a == NULL) ? TYPE_UNKNOWN : a->type;
}

/**
 * @brief Retorna o ponteiro para os dados de um objeto.
 * 
 * @param a Objeto.
 * @return Ponteiro para os dados ou NULL se o objeto for inválido.
 */
void* objGetData(obj a) {
  return (a == NULL) ? NULL : a->data;
}

/**
 * @brief Retorna o tamanho em bytes de um objeto.
 * 
 * @param a Objeto.
 * @return O tamanho dos dados em bytes ou 0 se o objeto for inválido.
 */
size_t objGetSize(obj a) {
  return (a == NULL) ? 0 : a->size;
}

/** 
* @brief Exibe um valor do tipo obj na tela.
*
* @param a Objeto.
* @return 1 se o objeto é válido, 0 caso contrário.
*/
int objPrint(obj a) {
  if (a == NULL) return 0;
  switch (a->type) {
    case TYPE_INT:
      printf("%d", *(int*)a->data);
      break;
    case TYPE_FLOAT:
      printf("%f", *(float*)a->data);
      break;
    case TYPE_DOUBLE:
      printf("%f", *(double*)a->data);
      break;
    case TYPE_CHAR:
      printf("%c", *(char*)a->data);
      break;
    case TYPE_CHAR_PTR:
      printf("%s", (char*)a->data);
      break;
    case TYPE_BOOL:
      printf("%s", *(bool*)a->data ? "true" : "false");
      break;
    case TYPE_STRING:
      stringPrint((string)a->data);
      break;
    case TYPE_LIST:
      listPrint((list)a->data);
      break;
    case TYPE_QUEUE:
      queuePrint((queue)a->data);
      break;
    case TYPE_STACK:
      stackPrint((stack)a->data);
      break; 
    case TYPE_TREE:
      treePrint((tree)a->data);
      break;
    default:
      printf("Unknown Type");
      break;
  }
  return 1;
}