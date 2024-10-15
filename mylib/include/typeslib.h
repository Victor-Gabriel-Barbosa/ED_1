#ifndef TYPESLIB_H
#define TYPESLIB_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Estrutura para representar uma string 
 */ 
typedef struct string *string;

/**
 * @brief Estrutura para representar uma lista
 */
typedef struct list *List;

/**
 * @brief Estrutura para representar uma fila
 */
typedef struct queue *Queue;

/**
 * @brief Estrutura para representar uma pilha
 */
typedef struct stack *Stack;

/**
 * @enum DataType
 * Enumeração de tipos de dados suportados.
 */
typedef enum {
    Int,     /**< Tipo inteiro */
    Float,   /**< Tipo float */
    Double,  /**< Tipo double */
    Char,    /**< Tipo char */
    Bool,    /**< Tipo booleano */
    String,  /**< Tipo string (ponteiro para char) */
    Auto,    /**< Tipo genérico, pode ter tamanho ajustado dinamicamente */
    Count    /**< Contador de tipos, marca o fim da enumeração */
} DataType;

/**
 * @brief Ajusta o tamanho do tipo 'Auto'.
 *
 * Permite que o tamanho do tipo 'Auto' seja ajustado dinamicamente.
 *
 * @param newSize O novo tamanho a ser definido para o tipo 'Auto'.
 * @return Retorna 0 em caso de sucesso e -1 se ocorrer erro.
 */
DataType autoSize(size_t newSize);

/**
 * @brief Retorna o tamanho de um tipo de dado.
 *
 * Esta função retorna o tamanho em bytes do tipo de dado especificado.
 * Se o tipo for inválido, ela retorna 0.
 *
 * @param type O tipo de dado cujo tamanho será retornado.
 * @return O tamanho do tipo de dado em bytes, ou 0 se o tipo for inválido.
 */
size_t typeGetSize(DataType type);  

#endif 