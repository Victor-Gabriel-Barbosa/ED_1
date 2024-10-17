/**
 * @file typeslib.h
 * @brief Biblioteca para manipulação de tipos genéricos em C.
 * 
 * Este arquivo contém a definição de uma biblioteca que facilita o gerenciamento de tipos genéricos em C. 
 * Através do uso da estrutura `Auto`, é possível encapsular valores de diferentes tipos de dados, como inteiros, floats, 
 * strings, listas, filas e pilhas, permitindo o armazenamento e manipulação de dados de maneira flexível e genérica.
 * 
 * A biblioteca oferece funcionalidades para converter tipos primitivos e customizados em um tipo genérico, comparar objetos encapsulados,
 * obter informações sobre o tipo e o tamanho dos dados armazenados, e liberar a memória alocada de forma segura.
 * 
 * Funções disponíveis:
 * - `voidToAuto`: Encapsula um valor genérico (`void*`) como um tipo `Auto`.
 * - `intToAuto`: Encapsula um valor do tipo `int`.
 * - `floatToAuto`: Encapsula um valor do tipo `float`.
 * - `doubleToAuto`: Encapsula um valor do tipo `double`.
 * - `charToAuto`: Encapsula um valor do tipo `char`.
 * - `charPtrToAuto`: Encapsula uma string (`const char*`).
 * - `boolToAuto`: Encapsula um valor booleano (`bool`).
 * - `stringToAuto`: Encapsula um valor do tipo `String`.
 * - `listToAuto`: Encapsula um valor do tipo `List`.
 * - `queueToAuto`: Encapsula um valor do tipo `Queue`.
 * - `stackToAuto`: Encapsula um valor do tipo `Stack`.
 * - `unknownToAuto`: Encapsula um valor genérico com tipo desconhecido.
 * - `destroyAuto`: Libera a memória alocada para um objeto `Auto`.
 * - `autoCmp`: Compara dois objetos `Auto`.
 * - `getAutoType`: Retorna o tipo de dado armazenado em um objeto `Auto`.
 * - `getAutoData`: Retorna o ponteiro para os dados encapsulados em um objeto `Auto`.
 * - `getAutoSize`: Retorna o tamanho em bytes dos dados armazenados em um objeto `Auto`.
 * 
 * Esta biblioteca permite o uso flexível de diferentes tipos de dados sem precisar reescrever funções para cada tipo. Através do uso de 
 * `_Generic` no macro `AUTO`, é possível encapsular automaticamente um valor de qualquer tipo suportado.
 * 
 * @note Tipos customizados como `List`, `Queue` e `Stack` podem ser usados em conjunto com essa biblioteca, permitindo o uso genérico dessas estruturas.
 * 
 * @note A função `destroyAuto` deve ser usada sempre que um objeto `Auto` não for mais necessário, para evitar vazamentos de memória.
 * 
 * @author Victor Gabriel Barbosa
 * @date 16/10/2024
 * @version 1.0
 */
#ifndef TYPESLIB_H
#define TYPESLIB_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Estrutura abstrata para representar uma string.
 */
typedef struct string *String;

/**
 * @brief Estrutura abstrata para representar uma lista.
 */
typedef struct list *List;

/**
 * @brief Estrutura abstrata para representar uma fila.
 */
typedef struct queue *Queue;

/**
 * @brief Estrutura abstrata para representar uma pilha.
 */
typedef struct stack *Stack;

/**
 * @brief Estrutura que representa uma árvore binária.
 */
typedef struct tree *Tree;

/**
 * @enum AutoType
 * @brief Enumeração que define os tipos de dados suportados pela biblioteca.
 */
typedef enum {
  TYPE_INT,     /**< Tipo inteiro. */
  TYPE_FLOAT,   /**< Tipo ponto flutuante (float). */
  TYPE_DOUBLE,  /**< Tipo ponto flutuante (double). */
  TYPE_CHAR,    /**< Tipo caractere (char). */
  TYPE_CHAR_P,  /**< Tipo ponteiro para caractere (char*). */
  TYPE_BOOL,    /**< Tipo booleano (bool). */
  TYPE_STRING,  /**< Tipo string. */
  TYPE_LIST,    /**< Tipo lista. */
  TYPE_QUEUE,   /**< Tipo fila. */
  TYPE_STACK,   /**< Tipo pilha. */
  TYPE_UNKNOWN, /**< Tipo genérico desconhecido, usado para tipos personalizados. */
} AutoType;

/**
 * @brief Estrutura abstrata para representar qualquer tipo de dado.
 */
typedef struct auto_t *Auto;

/**
 * @brief Converte um ponteiro de dados genérico para a estrutura Auto.
 * 
 * @param value Ponteiro para os dados.
 * @param size Tamanho dos dados.
 * @param type Tipo de dado (definido por AutoType).
 * @return Estrutura Auto contendo os dados.
 */
Auto voidToAuto(void* value, size_t size, AutoType type);

/**
 * @brief Converte um valor inteiro para Auto.
 * 
 * @param value Valor inteiro.
 * @param size Tamanho do valor.
 * @return Estrutura Auto contendo o valor inteiro.
 */
Auto intToAuto(int value, size_t size);

/**
 * @brief Converte um valor float para Auto.
 * 
 * @param value Valor float.
 * @param size Tamanho do valor.
 * @return Estrutura Auto contendo o valor float.
 */
Auto floatToAuto(float value, size_t size);

/**
 * @brief Converte um valor double para Auto.
 * 
 * @param value Valor double.
 * @param size Tamanho do valor.
 * @return Estrutura Auto contendo o valor double.
 */
Auto doubleToAuto(double value, size_t size);

/**
 * @brief Converte um caractere para Auto.
 * 
 * @param value Valor caractere (char).
 * @param size Tamanho do valor.
 * @return Estrutura Auto contendo o valor caractere.
 */
Auto charToAuto(char value, size_t size);

/**
 * @brief Converte uma string C (ponteiro de char) para Auto.
 * 
 * @param value Ponteiro para a string.
 * @param size Tamanho da string.
 * @return Estrutura Auto contendo a string.
 */
Auto charPtrToAuto(const char* value, size_t size);

/**
 * @brief Converte um valor booleano para Auto.
 * 
 * @param value Valor booleano (bool).
 * @param size Tamanho do valor.
 * @return Estrutura Auto contendo o valor booleano.
 */
Auto boolToAuto(bool value, size_t size);

/**
 * @brief Converte uma string abstrata (String) para Auto.
 * 
 * @param value Estrutura String.
 * @param size Tamanho da string.
 * @return Estrutura Auto contendo a string.
 */
Auto stringToAuto(String value, size_t size);

/**
 * @brief Converte uma lista abstrata (List) para Auto.
 * 
 * @param value Estrutura List.
 * @param size Tamanho da lista.
 * @return Estrutura Auto contendo a lista.
 */
Auto listToAuto(List value, size_t size);

/**
 * @brief Converte uma fila abstrata (Queue) para Auto.
 * 
 * @param value Estrutura Queue.
 * @param size Tamanho da fila.
 * @return Estrutura Auto contendo a fila.
 */
Auto queueToAuto(Queue value, size_t size);

/**
 * @brief Converte uma pilha abstrata (Stack) para Auto.
 * 
 * @param value Estrutura Stack.
 * @param size Tamanho da pilha.
 * @return Estrutura Auto contendo a pilha.
 */
Auto stackToAuto(Stack value, size_t size);

/**
 * @brief Converte um valor desconhecido para Auto.
 * 
 * @param value Ponteiro para os dados.
 * @param size Tamanho dos dados.
 * @return Estrutura Auto contendo os dados genéricos.
 */
Auto unknownToAuto(void* value, size_t size);

/**
 * @brief Libera a memória de um Auto.
 * 
 * @param a Estrutura Auto a ser destruída.
 * @return NULL após a destruição do Auto.
 */
Auto destroyAuto(Auto a);

/**
 * @brief Obtém o tipo de dado armazenado no Auto.
 * 
 * @param a Estrutura Auto.
 * @return Tipo de dado (AutoType) armazenado.
 */
AutoType getAutoType(Auto a);

/**
 * @brief Obtém os dados armazenados no Auto.
 * 
 * @param a Estrutura Auto.
 * @return Ponteiro para os dados armazenados.
 */
void* getAutoData(Auto a);

/**
 * @brief Obtém o tamanho dos dados armazenados no Auto.
 * 
 * @param a Estrutura Auto.
 * @return Tamanho dos dados armazenados.
 */
size_t getAutoSize(Auto a);

/**
 * @brief Compara dois valores Auto.
 * 
 * @param a Primeiro valor Auto.
 * @param b Segundo valor Auto.
 * @return 0 se forem iguais, valor negativo se a < b, valor positivo se a > b.
 */
int autoCmp(Auto a, Auto b);

/**
 * @brief Macro para converter automaticamente tipos suportados para Auto.
 * 
 * @param value Valor a ser convertido.
 * @return Estrutura Auto correspondente ao tipo do valor.
 */
#define AUTO(value) _Generic((value), \
  int: intToAuto, \
  float: floatToAuto, \
  double: doubleToAuto, \
  char: charToAuto, \
  const char*: charPtrToAuto, \
  char*: charPtrToAuto, \
  bool: boolToAuto, \
  String: stringToAuto, \
  List: listToAuto, \
  Queue: queueToAuto, \
  Stack: stackToAuto, \
  default: unknownToAuto \
)(value, sizeof(value))

#endif