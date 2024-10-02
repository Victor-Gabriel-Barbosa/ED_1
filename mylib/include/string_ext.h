#ifndef STRING_EXT_H
#define STRING_EXT_H

#include <stddef.h>

/**
 * @brief Estrutura da string (String).
 * 
 * A string contém um ponteiro para os dados da string.
 * O tamanho atual da string.
 * A capacidade alocada para a string.
 * e um contador de elementos (`N`).
 */
typedef struct string {
  char *data; 
  size_t size;
  size_t capacity; 
} String;

// Macro para obter o tamanho de um array
#define SIZE_ARRAY(arr) (sizeof(arr) / sizeof((arr)[0]))

/** 
 * Simula o printf e aceita novos tipos.
 * 
 * @param format A string de formato.
 * @param ... Os argumentos a serem formatados.
 */
void printsf(const char *format, ...); 

/** 
 * Captura exceções. 
 */
void catchError();

/** 
 * Cria uma nova string vazia. 
 * 
 * @return Uma nova instância da estrutura String. 
 */
String newString();

/** 
 * Inicializa uma string com o conteúdo de uma string existente.
 * 
 * @param str A string a ser copiada.
 * @return Uma nova instância da estrutura String contendo o conteúdo de str.
 */
String initString(const char *str);

/** 
 * Libera a memória alocada para a string.
 * 
 * @param str Ponteiro para a string a ser liberada.
 */
void destroyString(String *str);

/** 
 * Obtém o tamanho da string.
 * 
 * @param str Ponteiro para a string.
 * @return O tamanho da string.
 */
size_t sizeString(const String str);

/** 
 * Redimensiona a capacidade da string.
 * 
 * @param str Ponteiro para a string a ser redimensionada.
 * @param new_capacity O novo tamanho da capacidade da string.
 */
void resizeString(String *str, size_t new_capacity);

/** 
 * Adiciona um caractere ao final da string.
 * 
 * @param str Ponteiro para a string.
 * @param c O caractere a ser adicionado.
 */
void addChar(String *str, char c);

/** 
 * Concatena duas strings e retorna a string resultante.
 * 
 * @param str1 Constante para a primeira string.
 * @param str2 Constante para a segunda string.
 * @return Uma nova instância da estrutura String resultante da concatenação.
 */
String appendStrings(const String str1, const String str2);

/** 
 * Compara duas strings e retorna 1 se forem iguais, caso contrário, 0.
 * 
 * @param str1 Ponteiro para a primeira string.
 * @param str2 Ponteiro para a segunda string.
 * @return 1 se as strings forem iguais, 0 caso contrário.
 */
int isStringEqual(const String str1, const String str2);

/** 
 * Lê uma string do teclado.
 * 
 * @return Uma instância da estrutura String contendo a string lida.
 */
String inputString();

/** 
 * Substitui todas as ocorrências de um caractere por outro.
 * 
 * @param str Ponteiro para a string.
 * @param a O caractere a ser substituído.
 * @param b O caractere substituto.
 * @return O número de substituições realizadas.
 */
size_t replaceChar(String *str, const char a, const char b);

/** 
 * Encontra uma substring e retorna a posição inicial ou -1 se não encontrado.
 * 
 * @param str Constante para a string onde a busca será realizada.
 * @param substr A substring a ser buscada.
 * @return A posição inicial da substring ou -1 se não encontrada.
 */
int indexOfSubstring(const String str, const char *substr);

/** 
 * Inverte o conteúdo da string.
 * 
 * @param str A string a ser invertida.
 * @return Uma nova instância da estrutura String com o conteúdo invertido.
 */
String reverseString(const String str);

/** 
 * Divide uma string em tokens usando um delimitador.
 * 
 * @param str Constante para a string a ser dividida.
 * @param dlm O delimitador utilizado para a divisão.
 * @return Um ponteiro para um array de strings contendo os tokens.
 */
String *splitString(const String str, const char *dlm);

/** 
 * Localiza um caractere dentro de uma string pelo índice.
 * 
 * @param str Constante para a string.
 * @param posi O índice do caractere a ser localizado.
 * @return Um ponteiro para o caractere na posição especificada ou NULL se fora dos limites.
 */
char *getCharAt(const String str, size_t posi);

/**
 * Simula o snprintsf usando o tipo string.
 *
 * @param dest Ponteiro para a string de destino.
 * @param format Formato da string.
 */
void snprintsf(String *dest, const char *format, ...);

#endif