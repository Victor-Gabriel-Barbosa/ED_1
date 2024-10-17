/**
 * @file stringlib.h
 * @brief Biblioteca para manipulação de Strings dinâmicas em C.
 * 
 * Este arquivo contém a implementação de uma biblioteca para manipulação de Strings dinâmicas. 
 * A biblioteca permite a criação, modificação, concatenação, e diversas operações úteis em Strings, 
 * como substituição de caracteres, busca de substrings e manipulação de tokens.
 * 
 * Funções disponíveis:
 * - `sizeofString': Obtém o tamanho da struct String.
 * - `stringNew`: Cria uma nova String vazia.
 * - `stringInit`: Inicializa uma String com o conteúdo de uma String literal.
 * - `stringDestroy`: Libera a memória alocada para uma String.
 * - `stringSize`: Retorna o tamanho da String.
 * - `stringResize`: Redimensiona a capacidade de armazenamento de uma String.
 * - `stringAddChar`: Adiciona um caractere ao final de uma String.
 * - `stringAppend`: Concatena duas Strings.
 * - `stringIsEqual`: Compara duas Strings e retorna se são iguais.
 * - `stringInput`: Lê uma String a partir do teclado.
 * - `stringReplace`: Substitui todas as ocorrências de um caractere por outro.
 * - `stringIndex`: Busca uma substring e retorna sua posição.
 * - `stringReverse`: Inverte o conteúdo de uma String.
 * - `stringSplit`: Divide uma String em tokens, utilizando um delimitador.
 * - `stringGet`: Retorna o conteúdo de uma String.
 * - `stringGetChar`: Acessa um caractere da String por índice.
 * - `stringSnprintf`: Simula o snprintf para Strings dinâmicas.
 * - `stringPrint`: Exibe a String no console.
 * - `toString`: Transforma um dado genérico em uma String.
 * 
 * Esta biblioteca foi projetada para facilitar o gerenciamento de Strings em C, permitindo operações que ajustam 
 * automaticamente a memória conforme necessário, tornando o uso de Strings dinâmicas mais seguro e eficiente.
 * 
 * @note As Strings são estruturas dinâmicas e, portanto, a memória é ajustada automaticamente durante as operações 
 * que envolvem adição ou remoção de caracteres.
 * 
 * @warning Sempre liberar a memória de uma String com `stringDestroy` para evitar vazamento de memória.
 * 
 * @author 
 * @date 12/10/2024
 * @version 1.0
 */
#ifndef STRINGLIB_H
#define STRINGLIB_H

#include <typeslib.h>

/**
 * @brief Obtém o tamanho da struct String.
 * 
 * @return O tamanho da struct String.
 */
size_t sizeofString();

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
 * @param type Tipo do dado que será transformado.
 * @return Uma nova instância da estrutura String contendo o conteúdo transformado.
 */
String toString(Auto info);

#endif