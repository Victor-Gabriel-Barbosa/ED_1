/**
 * @file stringlib.h
 * @brief Biblioteca para manipulação de Strings dinâmicas em C.
 * 
 * Este arquivo contém a implementação de uma biblioteca para manipulação de Strings dinâmicas. 
 * A biblioteca permite a criação, modificação, concatenação, e diversas operações úteis em Strings, 
 * como substituição de caracteres, busca de substrings e manipulação de tokens.
 * 
 * Funções disponíveis:
 * - `stringNew`: Cria uma nova string vazia.
 * - `stringInit`: Inicializa uma string com o conteúdo de uma string literal.
 * - `stringDestroy`: Libera a memória alocada para uma string.
 * - `stringSize`: Retorna o tamanho da string.
 * - `stringResize`: Redimensiona a capacidade de armazenamento de uma string.
 * - `stringAddChar`: Adiciona um caractere ao final de uma string.
 * - `stringAppend`: Concatena duas Strings.
 * - `stringIsEqual`: Compara duas Strings e retorna se são iguais.
 * - `stringInput`: Lê uma string a partir do teclado.
 * - `stringReplace`: Substitui todas as ocorrências de um caractere por outro.
 * - `stringIndex`: Busca uma substring e retorna sua posição.
 * - `stringReverse`: Inverte o conteúdo de uma string.
 * - `stringSplit`: Divide uma string em tokens, utilizando um delimitador.
 * - `stringGet`: Retorna o conteúdo de uma string.
 * - `stringGetChar`: Acessa um caractere da string por índice.
 * - `stringSnprintf`: Simula o snprintf para Strings dinâmicas.
 * - `stringPrint`: Exibe a string no console.
 * - `toString`: Transforma um dado genérico em uma string.
 * 
 * Esta biblioteca foi projetada para facilitar o gerenciamento de Strings em C, permitindo operações que ajustam 
 * automaticamente a memória conforme necessário, tornando o uso de Strings dinâmicas mais seguro e eficiente.
 * 
 * @note As Strings são estruturas dinâmicas e, portanto, a memória é ajustada automaticamente durante as operações 
 * que envolvem adição ou remoção de caracteres.
 * 
 * @warning Sempre liberar a memória de uma string com `stringDestroy` para evitar vazamento de memória.
 * 
 * @author 
 * @date 12/10/2024
 * @version 1.0
 */
#ifndef STRINGLIB_H
#define STRINGLIB_H

#include <typeslib.h>

/** 
 * @brief Cria uma nova string vazia. 
 * 
 * @return Uma nova instância da estrutura string. 
 */
string stringNew();

/** 
 * @brief Inicializa uma string com o conteúdo de uma string existente.
 * 
 * @param str A string a ser copiada.
 * @return Uma nova instância da estrutura string contendo o conteúdo de str.
 */
string stringInit(const char *str);

/** 
 * @brief Libera a memória alocada para a string.
 * 
 * @param str Ponteiro para a string a ser liberada.
 * @return 1 se a string não é vazia, 0 caso contrário.
 */
int stringDestroy(string str);

/** 
 * @brief Obtém o tamanho da string.
 * 
 * @param str Ponteiro para a string.
 * @return O tamanho da string.
 */
size_t stringSize(const string str);

/** 
 * @brief Redimensiona a capacidade da string.
 * 
 * @param str Ponteiro para a string a ser redimensionada.
 * @param new_capacity O novo tamanho da capacidade da string.
 * @return 1 se a string não é vazia, 0 caso contrário.
 */
int stringResize(string str, size_t new_capacity);

/** 
 * @brief Adiciona um caractere ao final da string.
 * 
 * @param str Ponteiro para a string.
 * @param c O caractere a ser adicionado.
* @return 1 se a string não é vazia, 0 caso contrário.
 */
int stringAddChar(string str, char c);

/** 
 * @brief Concatena duas strings e retorna a string resultante.
 * 
 * @param str1 Constante para a primeira string.
 * @param str2 Constante para a segunda string.
 * @return Uma nova instância da estrutura string resultante da concatenação.
 */
string stringAppend(const string str1, const string str2);

/** 
 * @brief Compara duas strings e retorna 1 se forem iguais, caso contrário, 0.
 * 
 * @param str1 Ponteiro para a primeira string.
 * @param str2 Ponteiro para a segunda string.
 * @return 1 se as strings forem iguais, 0 caso contrário.
 */
int stringIsEqual(const string str1, const string str2);

/** 
 * @brief Lê uma string do teclado.
 * 
 * @return Uma instância da estrutura string contendo a string lida.
 */
string stringInput();

/** 
 * @brief Substitui todas as ocorrências de um caractere por outro.
 * 
 * @param str Ponteiro para a string.
 * @param a O caractere a ser substituído.
 * @param b O caractere substituto.
 * @return O número de substituições realizadas.
 */
size_t stringReplace(string str, const char a, const char b);

/** 
 * @brief Encontra uma substring e retorna a posição inicial ou -1 se não encontrado.
 * 
 * @param str Constante para a string onde a busca será realizada.
 * @param substr A substring a ser buscada.
 * @return A posição inicial da substring ou -1 se não encontrada.
 */
int stringIndex(const string str, const char *substr);

/** 
 * @brief Inverte o conteúdo da string.
 * 
 * @param str A string a ser invertida.
 * @return Uma nova instância da estrutura string com o conteúdo invertido.
 */
string stringReverse(const string str);

/** 
 * @brief Divide uma string em tokens usando um delimitador.
 * 
 * @param str Constante para a string a ser dividida.
 * @param dlm O delimitador utilizado para a divisão.
 * @return Um ponteiro para um array de strings contendo os tokens.
 */ 
string *stringSplit(const string str, const char *dlm);

/** 
 * @brief Pega o conteúdo de uma string
 * 
 * @param str Ponteiro para a string.
 * @return Conteúdo da string.
 */
const char *stringGet(const string str);

/** 
 * @brief Localiza um caractere dentro de uma string pelo índice.
 * 
 * @param str Constante para a string.
 * @param pos O índice do caractere a ser localizado.
 * @return Um ponteiro para o caractere na posição especificada ou NULL se fora dos limites.
 */
char *stringGetChar(const string str, size_t pos);

/**
 * @brief Simula o snprintf usando o tipo string.
 *
 * @param dest Ponteiro para a string de destino.
 * @param format Formato da string.
 * @return 1 se a string não é vazia, 0 caso contrário.
 */
int stringSnprintf(string dest, const char *format, ...);

/** 
* @brief Mostra uma string na tela.

* @param str Ponteiro para a string.
* @return 1 se a string não é vazia, 0 caso contrário.
*/
int stringPrint(string str);

/**
 * @brief Transforma um dado qualquer em uma string.
 *  
 * @param data Ponteiro genérico para o dado que será transformado.
 * @param type Tipo do dado que será transformado.
 * @param sizeType Tamanho do tipo do dado que será transformado.
 * @return Uma nova instância da estrutura string contendo o conteúdo transformado.
 */
string toString(void *data, DataType type, size_t sizeTip);

#endif