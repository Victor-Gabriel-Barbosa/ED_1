/**
 * @file typeslib.h
 * @brief Biblioteca para manipulação de tipos genéricos em C.
 * 
 * Este arquivo contém a definição de uma biblioteca que facilita o gerenciamento de tipos genéricos em C. 
 * Através do uso da estrutura 'obj', é possível encapsular valores de diferentes tipos de dados, como inteiros, floats, 
 * strings, listas, filas e pilhas, permitindo o armazenamento e manipulação de dados de maneira flexível e genérica.
 * 
 * A biblioteca oferece funcionalidades para converter tipos primitivos e customizados em um tipo genérico, comparar objetos encapsulados,
 * obter informações sobre o tipo e o tamanho dos dados armazenados, e liberar a memória alocada de forma segura.
 * 
 * Funções disponíveis:
 * - 'voidToAuto': Encapsula um valor genérico ('void*') como um tipo 'obj'.
 * - 'intToAuto': Encapsula um valor do tipo 'int'.
 * - 'floatToAuto': Encapsula um valor do tipo 'float'.
 * - 'doubleToAuto': Encapsula um valor do tipo 'double'.
 * - 'charToAuto': Encapsula um valor do tipo 'char'.
 * - 'charPtrToAuto': Encapsula uma string ('const char*').
 * - 'boolToAuto': Encapsula um valor booleano ('bool').
 * - 'stringToAuto': Encapsula um valor do tipo 'string'.
 * - 'listToAuto': Encapsula um valor do tipo 'list'.
 * - 'queueToAuto': Encapsula um valor do tipo 'queue'.
 * - 'stackToAuto': Encapsula um valor do tipo 'stack'.
 * - 'unknownToAuto': Encapsula um valor genérico com tipo desconhecido.
 * - 'autoDestroy': Libera a memória alocada para um objeto 'obj'.
 * - 'autoCmp': Compara dois objetos 'obj'.
 * - 'autoGetType': Retorna o tipo de dado armazenado em um objeto 'obj'.
 * - 'autoGetData': Retorna o ponteiro para os dados encapsulados em um objeto 'obj'.
 * - 'autoGetSize': Retorna o tamanho em bytes dos dados armazenados em um objeto 'obj'.
 * 
 * Esta biblioteca permite o uso flexível de diferentes tipos de dados sem precisar reescrever funções para cada tipo. Através do uso de 
 * '_Generic' no macro 'obj', é possível encapsular automaticamente um valor de qualquer tipo suportado.
 * 
 * @note Tipos customizados como 'list', 'queue' e 'stack' podem ser usados em conjunto com essa biblioteca, permitindo o uso genérico dessas estruturas.
 * 
 * @note A função 'autoDestroy' deve ser usada sempre que um objeto 'obj' não for mais necessário, para evitar vazamentos de memória.
 * 
 * @author Victor Gabriel Barbosa
 * @date 20/10/2024
 * @version 2.0
 */
#ifndef TYPESLIB_H
#define TYPESLIB_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Estrutura abstrata para representar uma string.
 */
typedef struct string_t *string;

/**
 * @brief Estrutura abstrata para representar uma lista.
 */
typedef struct list_t* list;

/**
 * @brief Estrutura abstrata para representar uma fila.
 */
typedef struct queue_t* queue;

/**
 * @brief Estrutura abstrata para representar uma pilha.
 */
typedef struct stack_t* stack;

/**
 * @brief Estrutura que representa uma árvore binária.
 */
typedef struct map_t* map;

/**
 * @brief Estrutura abstrata para representar qualquer tipo de dado.
 */
typedef struct obj_t* obj;

/**
 * @enum ObjType
 * @brief Enumeração que define os tipos de dados suportados pela biblioteca.
 */
typedef enum {
  TYPE_INT,      /**< Tipo inteiro (int). */
  TYPE_FLOAT,    /**< Tipo ponto flutuante (float). */
  TYPE_DOUBLE,   /**< Tipo ponto flutuante (double). */
  TYPE_CHAR,     /**< Tipo caractere (char). */
  TYPE_CHAR_PTR, /**< Tipo ponteiro para caractere (char*). */
  TYPE_BOOL,     /**< Tipo booleano (bool). */
  TYPE_STRING,   /**< Tipo string (string). */
  TYPE_LIST,     /**< Tipo lista (list). */
  TYPE_QUEUE,    /**< Tipo fila (queue). */
  TYPE_STACK,    /**< Tipo pilha (stack). */
  TYPE_MAP,     /**< Tipo árvore (map). */
  TYPE_UNKNOWN   /**< Tipo genérico desconhecido, usado para tipos personalizados (void*). */
} ObjType;

/**
 * @brief Converte um ponteiro de dados genérico para o tipo obj.
 * 
 * @param value Ponteiro para os dados.
 * @param size Tamanho dos dados.
 * @param type Tipo de dado (definido por ObjType).
 * @return Objeto contendo os dados.
 */
obj voidToObj(void* value, size_t size, ObjType type);

/**
 * @brief Converte um valor inteiro para obj.
 * 
 * @param value Valor inteiro.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Objeto contendo o valor inteiro.
 */
obj intToObj(int value, size_t size);

/**
 * @brief Converte um valor float para obj.
 * 
 * @param value Valor float.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Objeto contendo o valor float.
 */
obj floatToObj(float value, size_t size);

/**
 * @brief Converte um valor double para obj.
 * 
 * @param value Valor double.
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Objeto contendo o valor double.
 */
obj doubleToObj(double value, size_t size);

/**
 * @brief Converte um caractere para obj.
 * 
 * @param value Valor caractere (char).
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Objeto contendo o valor caractere.
 */
obj charToObj(char value, size_t size);

/**
 * @brief Converte uma string literal (char*) para obj.
 * 
 * @param value Ponteiro para a string.
 * @param size Tamanho da string (não utilizado nesta função).
 * @return Objeto contendo a string.
 */
obj charPtrToObj(const char* value, size_t size);

/**
 * @brief Converte um valor booleano para obj.
 * 
 * @param value Valor booleano (bool).
 * @param size Tamanho do valor (não utilizado nesta função).
 * @return Objeto contendo o valor booleano.
 */
obj boolToObj(bool value, size_t size);

/**
 * @brief Converte uma string abstrata (string) para obj.
 * 
 * @param value Estrutura string.
 * @param size Tamanho da string (não utilizado nesta função).
 * @return Objeto contendo a string.
 */
obj stringToObj(string value, size_t size);

/**
 * @brief Converte uma lista abstrata (list) para obj.
 * 
 * @param value Estrutura list.
 * @param size Tamanho da lista (não utilizado nesta função).
 * @return Objeto contendo a lista.
 */
obj listToObj(list value, size_t size);

/**
 * @brief Converte uma fila abstrata (queue) para obj.
 * 
 * @param value Estrutura queue.
 * @param size Tamanho da fila (não utilizado nesta função).
 * @return Objeto contendo a fila.
 */
obj queueToObj(queue value, size_t size);

/**
 * @brief Converte uma pilha abstrata (stack) para obj.
 * 
 * @param value Estrutura stack.
 * @param size Tamanho da pilha (não utilizado nesta função).
 * @return Objeto contendo a pilha.
 */
obj stackToObj(stack value, size_t size);

/**
 * @brief Converte uma árvore abstrata (map) para obj.
 * 
 * @param value Estrutura map.
 * @param size Tamanho da árvore (não utilizado nesta função).
 * @return Objeto contendo a árvore.
 */
obj mapToObj(map value, size_t size);

/**
 * @brief Converte um valor desconhecido para obj.
 * 
 * @param value Ponteiro para os dados.
 * @param size Tamanho dos dados.
 * @return Objeto contendo os dados genéricos.
 */
obj unknownToObj(void* value, size_t size);

/**
 * @brief Libera a memória de um obj.
 * 
 * @param a Objeto a ser destruída.
 * @return NULL após a destruição do obj.
 */
obj objDestroy(obj a);

/**
 * @brief Obtém o tipo de dado armazenado em obj.
 * 
 * @param a Objeto.
 * @return Tipo de dado (ObjType) armazenado.
 */
ObjType objGetType(obj a);

/**
 * @brief Obtém os dados armazenados em obj.
 * 
 * @param a Objeto.
 * @return Ponteiro para os dados armazenados.
 */
void* objGetData(obj a);

/**
 * @brief Obtém o tamanho dos dados armazenados em obj.
 * 
 * @param a Objeto.
 * @return Tamanho dos dados armazenados.
 */
size_t objGetSize(obj a);

/**
 * @brief Compara dois valores obj.
 * 
 * @param a Primeiro valor obj.
 * @param b Segundo valor obj.
 * @return 0 se forem iguais, valor negativo se a < b, valor positivo se a > b.
 */
int objCmp(obj a, obj b);

/** 
* @brief Exibe um valor do tipo obj na tela.
*
* @param a Objeto.
* @return 1 se o objeto é válido, 0 caso contrário.
*/
int objPrint(obj a);

/**
 * @brief Macro para converter automaticamente tipos suportados para obj.
 * 
 * @param value Valor a ser convertido.
 * @return Objeto correspondente ao tipo do valor.
 */
#define toObj(value) _Generic((value), \
  int: intToObj, \
  float: floatToObj, \
  double: doubleToObj, \
  const char: charToObj, \
  char: charToObj, \
  const char*: charPtrToObj, \
  char*: charPtrToObj, \
  bool: boolToObj, \
  string: stringToObj, \
  list: listToObj, \
  queue: queueToObj, \
  stack: stackToObj, \
  map: mapToObj, \
  default: unknownToObj \
)(value, sizeof(value))

#endif