#ifndef STRINGLIB_H
#define STRINGLIB_H

#include <stddef.h>

/**
 * @brief Estrutura para representar uma String 
 */ 
typedef struct string *String;

/** 
 * @brief Cria uma nova String vazia. 
 * 
 * @return Uma nova instância da estrutura String. 
 */
String stringNew();

/** 
 * @brief Inicializa uma String com o conteúdo de uma String existente.
 * 
 * @param str A String a ser copiada.
 * @return Uma nova instância da estrutura String contendo o conteúdo de str.
 */
String stringInit(const char *str);

/** 
 * @brief Libera a memória alocada para a String.
 * 
 * @param str Ponteiro para a String a ser liberada.
 * @return 1 se a String não é vazia, 0 caso contrário.
 */
int stringDestroy(String str);

/** 
 * @brief Obtém o tamanho da String.
 * 
 * @param str Ponteiro para a String.
 * @return O tamanho da String.
 */
size_t stringSize(const String str);

/** 
 * @brief Redimensiona a capacidade da String.
 * 
 * @param str Ponteiro para a String a ser redimensionada.
 * @param new_capacity O novo tamanho da capacidade da String.
 * @return 1 se a String não é vazia, 0 caso contrário.
 */
int stringResize(String str, size_t new_capacity);

/** 
 * @brief Adiciona um caractere ao final da String.
 * 
 * @param str Ponteiro para a String.
 * @param c O caractere a ser adicionado.
* @return 1 se a String não é vazia, 0 caso contrário.
 */
int stringAddChar(String str, char c);

/** 
 * @brief Concatena duas strings e retorna a String resultante.
 * 
 * @param str1 Constante para a primeira String.
 * @param str2 Constante para a segunda String.
 * @return Uma nova instância da estrutura String resultante da concatenação.
 */
String stringAppend(const String str1, const String str2);

/** 
 * @brief Compara duas strings e retorna 1 se forem iguais, caso contrário, 0.
 * 
 * @param str1 Ponteiro para a primeira String.
 * @param str2 Ponteiro para a segunda String.
 * @return 1 se as strings forem iguais, 0 caso contrário.
 */
int stringIsEqual(const String str1, const String str2);

/** 
 * @brief Lê uma String do teclado.
 * 
 * @return Uma instância da estrutura String contendo a String lida.
 */
String stringInput();

/** 
 * @brief Substitui todas as ocorrências de um caractere por outro.
 * 
 * @param str Ponteiro para a String.
 * @param a O caractere a ser substituído.
 * @param b O caractere substituto.
 * @return O número de substituições realizadas.
 */
size_t stringReplace(String str, const char a, const char b);

/** 
 * @brief Encontra uma substring e retorna a posição inicial ou -1 se não encontrado.
 * 
 * @param str Constante para a String onde a busca será realizada.
 * @param substr A substring a ser buscada.
 * @return A posição inicial da substring ou -1 se não encontrada.
 */
int stringIndex(const String str, const char *substr);

/** 
 * @brief Inverte o conteúdo da String.
 * 
 * @param str A String a ser invertida.
 * @return Uma nova instância da estrutura String com o conteúdo invertido.
 */
String stringReverse(const String str);

/** 
 * @brief Divide uma String em tokens usando um delimitador.
 * 
 * @param str Constante para a String a ser dividida.
 * @param dlm O delimitador utilizado para a divisão.
 * @return Um ponteiro para um array de strings contendo os tokens.
 */ 
String *stringSplit(const String str, const char *dlm);

/** 
 * @brief Pega o conteúdo de uma String
 * 
 * @param str Ponteiro para a String.
 * @return Conteúdo da String.
 */
const char *stringGet(const String str);

/** 
 * @brief Localiza um caractere dentro de uma String pelo índice.
 * 
 * @param str Constante para a String.
 * @param pos O índice do caractere a ser localizado.
 * @return Um ponteiro para o caractere na posição especificada ou NULL se fora dos limites.
 */
char *stringGetChar(const String str, size_t pos);

/**
 * @brief Simula o snprintf usando o tipo String.
 *
 * @param dest Ponteiro para a String de destino.
 * @param format Formato da String.
 * @return 1 se a String não é vazia, 0 caso contrário.
 */
int stringSnprintf(String dest, const char *format, ...);

/** 
* @brief Mostra uma String na tela.

* @param str Ponteiro para a String.
* @return 1 se a String não é vazia, 0 caso contrário.
*/
int stringPrint(String str);

/**
 * @brief Transforma um dado qualquer em uma String.
 * 
 * @param data Ponteiro genérico para o dado que será transformado.
 * @param sizeTip Tamanho da variável que será transformado.
 * @return Uma nova instância da estrutura String contendo o conteúdo transformado.
 */
String toString(void *data, size_t sizeTip);

#endif