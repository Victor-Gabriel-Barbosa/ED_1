/**
 * @file stringlib.h
 * @brief Biblioteca para manipulação da Strings dinâmicas em C.
 * 
 * Este arquivo contém a implementação de uma biblioteca para manipulação da Strings dinâmicas. 
 * A biblioteca permite a criação, modificação, concatenação, e diversas operações úteis em Strings, 
 * como substituição de caracteres, busca de substrings e manipulação de tokens.
 * 
 * Funções disponíveis:
 * - 'sizeofString': Calcula o tamanho em bytes da estrutura de dados 'string_t'.
 * - 'stringNew': Cria uma nova string vazia.
 * - 'stringInit': Inicializa uma string com o conteúdo de uma string literal.
 * - 'stringDestroy': Libera a memória alocada para uma string.
 * - 'stringIsEmpty': Verifica se uma string está vazia.
 * - 'stringSize': Retorna o tamanho da string.
 * - 'stringResize': Redimensiona a capacidade de armazenamento de uma string.
 * - 'stringAddChar': Adiciona um caractere ao final de uma string.
 * - 'stringAppend': Concatena duas Strings.
 * - 'stringCat': Concatena uma string com uma string literal.
 * - 'stringCopy': Cria uma cópia de uma string.
 * - 'stringIsEqual': Compara duas Strings e retorna se são iguais.
 * - 'stringInput': Lê uma string a partir do teclado.
 * - 'stringReplace': Substitui um caractere por outro.
 * - 'stringReplaceAll': Substitui todas as ocorrências de um caractere por outro.
 * - 'stringIndex': Busca uma substring e retorna sua posição.
 * - 'stringReverse': Inverte o conteúdo de uma string.
 * - 'stringSplit': Divide uma string em tokens, utilizando um delimitador.
 * - 'stringGet': Retorna o conteúdo de uma string.
 * - 'stringGetChar': Acessa um caractere da string por índice.
 * - 'stringSnprintf': Simula o snprintf para Strings dinâmicas.
 * - 'stringPrint': Exibe a string no console.
 * - 'toString': Transforma um dado genérico em uma string.
 * 
 * Esta biblioteca foi projetada para facilitar o gerenciamento da Strings em C, permitindo operações que ajustam 
 * automaticamente a memória conforme necessário, tornando o uso da Strings dinâmicas mais seguro e eficiente.
 * 
 * @note As Strings são estruturas dinâmicas e, portanto, a memória é ajustada automaticamente durante as operações 
 * que envolvem adição ou remoção de caracteres.
 * 
 * @warning Sempre liberar a memória de uma string com 'stringDestroy' para evitar vazamento de memória.
 * 
 * @author Victor Gabriel Barbosa
 * @date 20/10/2024
 * @version 2.0
 */
#ifndef STRINGLIB_H
#define STRINGLIB_H

#include <stdarg.h>
#include "typeslib.h"

/**
 * @brief Calcula o tamanho em bytes da estrutura de dados 'string_t'.
 * 
 * @return O tamanho em bytes da estrutura 'string_t'.
 */
size_t sizeofString();

/** 
 * @brief Cria uma nova string vazia. 
 * 
 * @return Uma nova instância de string. 
 */
string stringNew();

/** 
 * @brief Libera a memória alocada para string.
 * 
 * @param str Ponteiro para string a ser liberada.
 * @return 1 se string não é vazia, 0 caso contrário.
 */
int stringDestroy(string str);

/** 
 * @brief Inicializa uma string com o conteúdo de uma string literal.
 * 
 * @param str A string a ser copiada.
 * @return Uma nova instância de string contendo o conteúdo de str.
 */
string stringInit(const char* str);

/**
 * @brief Verifica se uma string está vazia.
 *
 * A função verifica se a string fornecida é nula ou tem tamanho zero.
 *
 * @param str A string a ser verificada.
 * @return 1 se a string for nula ou estiver vazia, 0 caso contrário.
 */
int stringIsEmpty(string str);

/** 
 * @brief Obtém o tamanho da string.
 * 
 * @param str String.
 * @return O tamanho da string.
 */
size_t stringSize(const string str);

/** 
 * @brief Redimensiona a capacidade da string.
 * 
 * @param str String a ser redimensionada.
 * @param new_capacity O novo tamanho da capacidade da string.
 * @return 1 se a string não é vazia, 0 caso contrário.
 */
int stringResize(string str, const size_t new_capacity);

/** 
 * @brief Adiciona um caractere ao final da string.
 * 
 * @param str String.
 * @param c O caractere a ser adicionado.
 * @return A string modificada, ou NULL se ocorrer um erro.
 */
string stringAddChar(string str, const char c);

/**
 * @brief Concatena a segunda string na primeira string.
 *
 * @param str1 Ponteiro para a primeira string que será modificada.
 * @param str2 Constante para a segunda string que será concatenada.
 * @return A string modificada (str1).
 */
string stringAppend(string str1, const string str2);

/**
 * @brief Concatena uma string com uma string literal.
 *
 * @param str1 Ponteiro para a primeira string que será modificada.
 * @param str2 Constante para a segunda string literal que será concatenada.
 * @return A string modificada (str1), ou NULL se ocorrer um erro.
 */
string stringCat(string str1, const char* str2);

/**
 * @brief Cria uma cópia de uma string.
 *
 * @param str A string a ser copiada.
 * @return Uma cópia da string, ou NULL se a alocação de memória falhar.
 */
string stringCopy(const string str);

/**
 * @brief Compara duas strings lexicograficamente.
 *
 * Esta função compara duas strings e retorna um valor
 * inteiro que indica a relação lexicográfica entre elas:
 * - Menor que 0: str1 é menor que str2
 * - Igual a 0: str1 é igual a str2
 * - Maior que 0: str1 é maior que str2
 *
 * @param str1 Ponteiro constante para a primeira string.
 * @param str2 Ponteiro constante para a segunda string.
 * @return Um valor inteiro conforme a relação entre as strings.
 */
int stringCmp(const string str1, const string str2);

/** 
 * @brief Lê uma string do teclado.
 * 
 * @return A string lida, ou NULL se ocorrer um erro.
 */
string stringInput();

/** 
 * @brief Substitui um caractere por outro.
 * 
 * @param str String.
 * @param a O caractere a ser substituído.
 * @param b O caractere substituto.
 * @return 1 se o caractere foi substituído, 0 caso contrário.
 */
int stringReplace(string str, const char a, const char b);

/** 
 * @brief Substitui todas as ocorrências de um caractere por outro.
 * 
 * @param str String.
 * @param a O caractere a ser substituído.
 * @param b O caractere substituto.
 * @return O número de substituições realizadas.
 */
size_t stringReplaceAll(string str, const char a, const char b);

/** 
 * @brief Encontra uma Substring e retorna a posição inicial ou -1 se não encontrado.
 * 
 * @param str Constante para a string onde a busca será realizada.
 * @param substr A substring a ser buscada.
 * @return A posição inicial da substring ou -1 se não encontrada.
 */
int stringIndex(const string str, const char* substr);

/** 
 * @brief Inverte o conteúdo da string.
 * 
 * @param str A string a ser invertida.
 * @return Uma nova instância de string com o conteúdo invertido.
 */
string stringReverse(string str);

/** 
 * @brief Divide uma string em tokens usando um delimitador.
 * 
 * @param str Constante para a string a ser dividida.
 * @param dlm O delimitador utilizado para a divisão.
 * @return Um ponteiro para um array da Strings contendo os tokens.
 */ 
string* stringSplit(const string str, const char* dlm);

/** 
 * @brief Pega o conteúdo de uma string
 * 
 * @param str String.
 * @return Conteúdo da string.
 */
const char* stringGet(const string str);

/** 
 * @brief Localiza um caractere dentro de uma string pelo índice.
 * 
 * @param str Constante para a string.
 * @param pos O índice do caractere a ser localizado.
 * @return Um ponteiro para o caractere na posição especificada ou NULL se fora dos limites.
 */
char* stringGetChar(const string str, size_t pos);

/**
 * @brief Simula o snprintf usando o tipo string.
 *
 * @param dest String de destino.
 * @param format Formato da string.
 * @return A string modificada (str1), ou NULL se ocorrer um erro.
 */
string stringSnprintf(string dest, const char* format, ...);

/**
 * @brief Transforma um objeto obj em uma string.
 *  
 * @param info Objeto obj.
 * @return Uma nova instância de string contendo o conteúdo transformado.
 */
string toString(const obj info);

/**
 * @brief Converte um valor qualquer em uma string.
 * 
 * @param value Valor a ser convertido.
 * @return Uma nova instância de string contendo o conteúdo transformado
 */
#define toStr(value) (toString(toObj(value)))

/** 
* @brief Exibe uma string na tela.

* @param str String a ser exibida.
* @return 1 se a string não é vazia, 0 caso contrário.
*/
int stringPrint(const string str);

#endif