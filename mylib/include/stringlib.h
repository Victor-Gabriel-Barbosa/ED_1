/**
 * @file stringlib.h
 * @brief Biblioteca para manipulação da Strings dinâmicas em C.
 * 
 * Este arquivo contém a implementação de uma biblioteca para manipulação da Strings dinâmicas. 
 * A biblioteca permite a criação, modificação, concatenação, e diversas operações úteis em Strings, 
 * como substituição de caracteres, busca de substrings e manipulação de tokens.
 * 
 * Funções disponíveis:
 * - 'sizeofString': Obtém o tamanho do objeto string.
 * - 'stringNew': Cria uma nova string vazia.
 * - 'stringInit': Inicializa uma string com o conteúdo de uma string literal.
 * - 'stringDestroy': Libera a memória alocada para uma string.
 * - 'stringSize': Retorna o tamanho da string.
 * - 'stringResize': Redimensiona a capacidade de armazenamento de uma string.
 * - 'stringAddChar': Adiciona um caractere ao final de uma string.
 * - 'stringAppend': Concatena duas Strings.
 * - 'stringIsEqual': Compara duas Strings e retorna se são iguais.
 * - 'stringInput': Lê uma string a partir do teclado.
 * - 'stringReplace': Substitui todas as ocorrências de um caractere por outro.
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

#include <typeslib.h>

/**
 * @brief Obtém o tamanho do objeto string.
 * 
 * @return O tamanho do objeto string.
 */
size_t sizeofString();

/** 
 * @brief Cria uma nova string vazia. 
 * 
 * @return Uma nova instância do objeto string. 
 */
string stringNew();

/** 
 * @brief Inicializa uma string com o conteúdo de uma string literal.
 * 
 * @param str A string a ser copiada.
 * @return Uma nova instância do objeto string contendo o conteúdo de str.
 */
string stringInit(const char* str);

/** 
 * @brief Libera a memória alocada para string.
 * 
 * @param str Ponteiro para string a ser liberada.
 * @return 1 se string não é vazia, 0 caso contrário.
 */
int stringDestroy(string str);

/** 
 * @brief Obtém o tamanho da string.
 * 
 * @param str Objeto string.
 * @return O tamanho da string.
 */
size_t stringSize(const string str);

/** 
 * @brief Redimensiona a capacidade da string.
 * 
 * @param str Objeto string a ser redimensionado.
 * @param new_capacity O novo tamanho da capacidade da string.
 * @return 1 se a string não é vazia, 0 caso contrário.
 */
int stringResize(string str, size_t new_capacity);

/** 
 * @brief Adiciona um caractere ao final da string.
 * 
 * @param str Objeto string.
 * @param c O caractere a ser adicionado.
* @return 1 se a string não é vazia, 0 caso contrário.
 */
int stringAddChar(string str, char c);

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
 * @return A string modificada (str1).
 */
string stringCat(string str1, const char* str2);

/**
 * @brief Compara duas strings lexicograficamente.
 *
 * Esta função compara duas instâncias do objeto string e retorna um valor
 * inteiro que indica a relação lexicográfica entre elas:
 * - Menor que 0: str1 é menor que str2
 * - Igual a 0: str1 é igual a str2
 * - Maior que 0: str1 é maior que str2
 *
 * @param str1 Ponteiro constante para a primeira string.
 * @param str2 Ponteiro constante para a segunda string.
 * @return Retorna um valor inteiro conforme a relação entre as strings.
 */
int stringCmp(const string str1, const string str2);

/** 
 * @brief Lê uma string do teclado.
 * 
 * @return Uma instância do objeto string contendo a string lida.
 */
string stringInput();

/** 
 * @brief Substitui todas as ocorrências de um caractere por outro.
 * 
 * @param str Objeto string.
 * @param a O caractere a ser substituído.
 * @param b O caractere substituto.
 * @return O número de substituições realizadas.
 */
size_t stringReplace(string str, const char a, const char b);

/** 
 * @brief Encontra uma Substring e retorna a posição inicial ou -1 se não encontrado.
 * 
 * @param str Constante para a string onde a busca será realizada.
 * @param substr A substring a ser buscada.
 * @return A posição inicial da substring ou -1 se não encontrada.
 */
int stringIndexOf(const string str, const char* substr);

/** 
 * @brief Inverte o conteúdo da string.
 * 
 * @param str A string a ser invertida.
 * @return Uma nova instância do objeto string com o conteúdo invertido.
 */
string stringReverse(const string str);

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
 * @param str Objeto string.
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
 * @param dest Objeto string de destino.
 * @param format Formato da string.
 * @return 1 se a string não é vazia, 0 caso contrário.
 */
int stringSnprintf(string dest, const char* format, ...);

/** 
* @brief Exibe uma string na tela.

* @param str Objeto string.
* @return 1 se a string não é vazia, 0 caso contrário.
*/
int stringPrint(string str);

/**
 * @brief Transforma um objeto obj em uma string.
 *  
 * @param info Objeto obj.
 * @return Uma nova instância do objeto string contendo o conteúdo transformado.
 */
string toString(obj info);

#endif