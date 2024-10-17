#include <typeslib.h>
#include <string.h>

/**
 * @struct auto_t
 * @brief Estrutura que representa um valor de tipo genérico, com um ponteiro para os dados, o tipo de dado e o tamanho em bytes.
 */
typedef struct auto_t {
  void *data;      /**< Ponteiro para os dados armazenados */
  AutoType type;   /**< Tipo de dado representado */
  size_t size;     /**< Tamanho do tipo de dado em bytes */
} *Auto;

/**
 * @brief Converte um valor genérico em um objeto Auto.
 * 
 * @param value Ponteiro para o valor.
 * @param size Tamanho do valor em bytes.
 * @param type Tipo do valor.
 * @return Um ponteiro para um objeto Auto ou NULL em caso de falha.
 */
Auto voidToAuto(void* value, size_t size, AutoType type) {
  Auto a = malloc(sizeof(struct auto_t));
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
 * @brief Converte um inteiro em um objeto Auto.
 * 
 * @param value Valor inteiro a ser convertido.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Um ponteiro para um objeto Auto contendo o valor inteiro.
 */
Auto intToAuto(int value, size_t size) {
  return voidToAuto(&value, sizeof(int), TYPE_INT);
}

/**
 * @brief Converte um float em um objeto Auto.
 * 
 * @param value Valor float a ser convertido.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Um ponteiro para um objeto Auto contendo o valor float.
 */
Auto floatToAuto(float value, size_t size) {
  return voidToAuto(&value, sizeof(float), TYPE_FLOAT);
}

/**
 * @brief Converte um double em um objeto Auto.
 * 
 * @param value Valor double a ser convertido.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Um ponteiro para um objeto Auto contendo o valor double.
 */
Auto doubleToAuto(double value, size_t size) {
  return voidToAuto(&value, sizeof(double), TYPE_DOUBLE);
}

/**
 * @brief Converte um char em um objeto Auto.
 * 
 * @param value Valor char a ser convertido.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Um ponteiro para um objeto Auto contendo o valor char.
 */
Auto charToAuto(char value, size_t size) {
  return voidToAuto(&value, sizeof(char), TYPE_CHAR);
}

/**
 * @brief Converte uma string (char*) em um objeto Auto.
 * 
 * @param value Ponteiro para a string.
 * @param size Tamanho da string (não utilizado nesta função).
 * @return Um ponteiro para um objeto Auto contendo a string.
 */
Auto charPtrToAuto(const char *value, size_t size) {
  Auto a = malloc(sizeof(struct auto_t));
  if (a == NULL) return NULL;
  a->size = strlen(value) + 1;
  a->data = malloc(a->size);
  if (a->data == NULL) {
    free(a);
    return NULL;
  }
  strcpy(a->data, value);
  a->type = TYPE_CHAR_P;
  return a;
}

/**
 * @brief Converte um valor booleano (bool) em um objeto Auto.
 * 
 * @param value Valor booleano a ser convertido.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Um ponteiro para um objeto Auto contendo o valor booleano.
 */
Auto boolToAuto(bool value, size_t size) {
  return voidToAuto(&value, sizeof(bool), TYPE_BOOL);
}

/**
 * @brief Converte um objeto String em um objeto Auto.
 * 
 * @param value Objeto String a ser convertido.
 * @param size Tamanho do objeto (não utilizado nesta função).
 * @return Um ponteiro para um objeto Auto contendo o objeto String.
 */
Auto stringToAuto(String value, size_t size) {
  return voidToAuto(&value, sizeof(String), TYPE_STRING);
}

/**
 * @brief Converte um objeto List em um objeto Auto.
 * 
 * @param value Objeto List a ser convertido.
 * @param size Tamanho do objeto (não utilizado nesta função).
 * @return Um ponteiro para um objeto Auto contendo o objeto List.
 */
Auto listToAuto(List value, size_t size) {
  return voidToAuto(value, sizeof(List), TYPE_LIST);
}

/**
 * @brief Converte um objeto Queue em um objeto Auto.
 * 
 * @param value Objeto Queue a ser convertido.
 * @param size Tamanho do objeto (não utilizado nesta função).
 * @return Um ponteiro para um objeto Auto contendo o objeto Queue.
 */
Auto queueToAuto(Queue value, size_t size) {
  return voidToAuto(value, sizeof(Queue), TYPE_QUEUE);
}

/**
 * @brief Converte um objeto Stack em um objeto Auto.
 * 
 * @param value Objeto Stack a ser convertido.
 * @param size Tamanho do objeto (não utilizado nesta função).
 * @return Um ponteiro para um objeto Auto contendo o objeto Stack.
 */
Auto stackToAuto(Stack value, size_t size) {
  return voidToAuto(value, sizeof(Stack), TYPE_STACK);
}

/**
 * @brief Converte um valor genérico e desconhecido em um objeto Auto.
 * 
 * @param value Ponteiro para o valor.
 * @param size Tamanho do valor em bytes.
 * @return Um ponteiro para um objeto Auto contendo o valor.
 */
Auto unknownToAuto(void* value, size_t size) {
  return voidToAuto(value, size, TYPE_UNKNOWN);
}

/**
 * @brief Libera a memória ocupada por um objeto Auto.
 * 
 * @param a Ponteiro para o objeto Auto a ser destruído.
 * @return Retorna NULL após destruir o objeto.
 */
Auto destroyAuto(Auto a) {
  if (a == NULL) return a;
  free(a->data);
  free(a);
  return NULL;
}

/**
 * @brief Compara dois objetos Auto.
 * 
 * @param a Primeiro objeto Auto.
 * @param b Segundo objeto Auto.
 * @return 0 se forem iguais, -1 se o primeiro for menor ou 1 se o segundo for menor.
 */
int autoCmp(Auto a, Auto b) {
  if (a == NULL && b == NULL) return 0;
  if (a == NULL || b == NULL) return (a == NULL) ? -1 : 1;
  if (a->type != b->type) return 1;
  switch (a->type) {
    case TYPE_INT:
      return (*(int*)a->data - *(int*)b->data);
    case TYPE_FLOAT:
      return (*(float*)a->data > *(float*)b->data) - (*(float*)a->data < *(float*)b->data);
    case TYPE_DOUBLE:
      return (*(double*)a->data > *(double*)b->data) - (*(double*)a->data < *(double*)b->data);
    case TYPE_CHAR:
      return (*(char*)a->data - *(char*)b->data);
    case TYPE_CHAR_P:
      return strcmp((char*)a->data, (char*)b->data);
    case TYPE_BOOL:
      return (*(bool*)a->data - *(bool*)b->data);
    case TYPE_STRING:
      return strcmp((char*)a->data, (char*)b->data);
    default:
      return 1;
  }
}

/**
 * @brief Retorna o tipo de dado de um objeto Auto.
 * 
 * @param a Objeto Auto.
 * @return O tipo de dado (AutoType).
 */
AutoType getAutoType(Auto a) {
  if (a == NULL) return TYPE_UNKNOWN;
  return a->type;
}

/**
 * @brief Retorna o ponteiro para os dados de um objeto Auto.
 * 
 * @param a Objeto Auto.
 * @return Ponteiro para os dados ou NULL se o objeto for inválido.
 */
void* getAutoData(Auto a) {
  if (a == NULL) return NULL;
  return a->data;
}

/**
 * @brief Retorna o tamanho em bytes de um objeto Auto.
 * 
 * @param a Objeto Auto.
 * @return O tamanho dos dados em bytes ou 0 se o objeto for inválido.
 */
size_t getAutoSize(Auto a) {
  if (a == NULL) return 0;
  return a->size;
}