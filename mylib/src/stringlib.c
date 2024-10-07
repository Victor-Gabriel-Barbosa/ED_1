#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <String.h>
#include "stringlib.h"

/**
 * @brief Estrutura da String (String).
 * 
 * A String contém um ponteiro para os dados da String.
 * O tamanho atual da String.
 * A capacidade alocada para a String.
 * e um contador de elementos (`N`).
 */
typedef struct string {
  char *data; 
  size_t size;
  size_t capacity; 
} *String;

/**
 * @brief Cria uma nova String com capacidade inicial.
 *
 * Essa função aloca memória para uma nova String e define sua capacidade
 * inicial. A String é inicializada com um tamanho de 0, pronta para ser
 * utilizada. É importante chamar essa função antes de realizar outras
 * operações de String.
 *
 * @return A nova String criada.
 */
String newString() {
  String new = (String)malloc(sizeof(struct string));
  if (new == NULL) {
    perror("\nMemória insuficiente!\n");
    exit(1);
  }
  new->size = 0;
  new->capacity = 32;  
  new->data = (char *)malloc((new->capacity + 1) * sizeof(char));
  if (new->data == NULL) {
    perror("\nMemória insuficiente!\n");
    exit(1);
  }
  new->data[0] = '\0'; 
  return new;
}

/**
 * @brief Inicializa uma String com o conteúdo de uma String existente.
 *
 * Essa função copia o conteúdo de uma String existente para uma nova
 * String, alocando a memória necessária para armazenar a cópia. A função
 * é útil para duplicar strings quando necessário.
 *
 * @param str Ponteiro para a String existente.
 * @return A nova String inicializada.
 */
String initString(const char *str) {
  String new = (String)malloc(sizeof(struct string));
  if (new == NULL) {
    perror("\nMemória insuficiente!\n");
    exit(1);
  }
  new->size = strlen(str);
  new->capacity = new->size + 1; 
  new->data = (char *)malloc((new->capacity) * sizeof(char));
  if (new->data == NULL) {
    perror("\nMemória insuficiente\n");
    exit(1);
  }
  strcpy(new->data, str);
  return new;
}

/**
 * @brief Libera a memória alocada para a String.
 *
 * Essa função é responsável por desalocar a memória usada pela String,
 * evitando vazamentos de memória. Deve ser chamada sempre que uma String
 * não for mais necessária.
 *
 * @param str Ponteiro para a String a ser liberada.
 * @return 1 se a String não é vazia, 0 caso contrário.
 */
int destroyString(String str) {
  if (str == NULL) return 0;
  free(str->data);
  str->data = NULL;
  str->size = 0;
  str->capacity = 0;
  free(str);
  return 1;
}

/**
 * @brief Obtém o tamanho da String.
 *
 * Essa função retorna o número de caracteres presentes na String, sem
 * contar o terminador nulo. É uma maneira de verificar quantos caracteres
 * estão efetivamente armazenados na String.
 *
 * @param str Ponteiro para a String.
 * @return O tamanho da String.
 */
size_t sizeString(const String str) {
  if (str == NULL) return 0;
  return str->size;
}

/**
 * @brief Redimensiona a capacidade da String.
 *
 * Essa função altera a capacidade da String, permitindo que ela armazene
 * mais ou menos caracteres, conforme necessário. É importante garantir que
 * a nova capacidade seja maior que o tamanho atual da String, se
 * caracteres adicionais forem a serem adicionados.
 *
 * @param str Ponteiro para a String a ser redimensionada.
 * @param new_capacity Nova capacidade da String.
 * @return 1 se a String não é vazia, 0 caso contrário.
 */
int resizeString(String str, size_t new_capacity) {
  if (str == NULL) return 0;
  if (new_capacity > str->capacity) {
    str->data = (char *)realloc(str->data, (new_capacity + 1) * sizeof(char));
    if (str->data == NULL) {
      perror("\nMemória insuficiente\n");
      exit(1);
    } 
    str->capacity = new_capacity;
  }
  return 1;
}

/**
 * @brief Adiciona um caractere ao final da String.
 *
 * Essa função anexa um caractere ao final da String. Se a capacidade
 * atual da String não for suficiente, a função redimensiona a String
 * antes de adicionar o novo caractere.
 *
 * @param str Ponteiro para a String.
 * @param c Caractere a ser adicionado.
 * @return 1 se a String não é vazia, 0 caso contrário.
 */
int addChar(String str, char c) {
  if (str == NULL) return 0;
  if (str->size + 1 >= str->capacity)resizeString(str, str->capacity * 2);
  str->data[str->size] = c;
  str->size++;
  str->data[str->size] = '\0'; 
  return 1;
}

/**
 * @brief Concatena duas strings.
 *
 * Essa função cria uma nova String resultante da concatenação de duas
 * strings. A nova String terá a soma dos tamanhos das duas strings
 * originais.
 *
 * @param str1 Constante para a primeira String.
 * @param str2 Constante para a segunda String.
 * @return A String resultante da concatenação.
 */
String appendStrings(const String str1, const String str2) {
  if (str1 == NULL || str2 == NULL) return NULL; 
  String append = (String)malloc(sizeof(struct string));
  if (append == NULL) {
    perror("\nMemória insuficiente!\n");
    exit(1);
  }
  append->size = str1->size + str2->size;
  append->capacity = append->size + 10;
  append->data = (char *)malloc((append->capacity + 1) * sizeof(char));
  if (append->data == NULL) {
    perror("\nMemória insuficiente\n");
    exit(1);
  }
  strcpy(append->data, str1->data);
  strcat(append->data, str2->data);
  return append;
}

/**
 * @brief Compara duas strings.
 *
 * Essa função verifica se duas strings são iguais. Retorna 1 se as
 * strings forem iguais, e 0 caso contrário. É uma função útil para
 * validação e verificação de igualdade em comparações.
 *
 * @param str1 Constante para a primeira String.
 * @param str2 Constante para a segunda String.
 * @return 1 se as strings forem iguais, 0 caso contrário.
 */
int isStringEqual(const String str1, const String str2) {
  if (str1 == NULL || str2 == NULL) return 0; 
  return (strcmp(str1->data, str2->data) == 0);
}

/**
 * @brief Lê uma String do teclado.
 *
 * Essa função solicita ao usuário que insira uma String pelo teclado.
 * A entrada é lida até que o usuário pressione a tecla Enter. A String
 * resultante é retornada para uso posterior.
 *
 * @return A String lida.
 */
String inputString() {
  String input = (String)malloc(sizeof(struct string));
  if (input == NULL) {
    perror("\nMemória insuficiente!\n");
    exit(1);
  }
  input->data = NULL; 
  size_t len = 0;
  if (getline(&input->data, &len, stdin) == -1) {
    input->size = 0;
    input->capacity = 0;
    return input;
  }
  input->data[strcspn(input->data, "\n")] = '\0'; 
  input->size = strlen(input->data); 
  input->capacity = len;
  return input;
}

/**
 * @brief Substitui todas as ocorrências de um caractere por outro.
 *
 * Essa função percorre a String e substitui todas as ocorrências do
 * caractere especificado por outro. Retorna o número de substituições
 * realizadas, o que pode ser útil para relatórios ou verificações.
 *
 * @param str Ponteiro para a String.
 * @param a Caractere a ser substituído.
 * @param b Caractere que irá substituir.
 * @return O número de substituições realizadas.
 */
size_t replaceChar(String str, const char a, const char b) {
  size_t cont = 0;
  for (size_t i = 0; i < str->size; i++) {
    if (str->data[i] == a) { 
      str->data[i] = b;
      cont++;
    }
  }
  return cont;
}

/**
 * @brief Encontra uma substring.
 *
 * Essa função verifica a existência de uma substring dentro de uma String
 * principal. Retorna o índice da primeira ocorrência, ou -1 se a
 * substring não for encontrada. É uma função útil para pesquisa de
 * padrões ou validação de conteúdo.
 *
 * @param str Constante para a String.
 * @param substr Ponteiro para a substring a ser encontrada.
 * @return O índice da substring, ou -1 se não encontrada.
 */
int indexOfSubstring(const String str, const char *substr) {
  if (str == NULL || substr == NULL) return -1;
  char *pos = strstr(str->data, substr);
  return pos ? (int)(pos - str->data) : -1; 
}

/**
 * @brief Inverte o conteúdo da String.
 *
 * Essa função inverte a ordem dos caracteres dentro da String, criando
 * uma nova String. É útil em situações onde se deseja manipular ou
 * transformar a representação da String.
 *
 * @param str A String a ser invertida.
 * @return A String invertida.
 */
String reverseString(const String str) {
  if (str == NULL || str->size == 0 || str->data == NULL) return str;
  String reverse = newString(); 
  for (size_t i = 0; i < str->size; i++) {
    addChar(reverse, str->data[str->size - 1 - i]);
  }
  return reverse; 
}

/**
 * @brief Divide uma String em tokens usando um delimitador.
 *
 * Essa função separa a String original em substrings com base em um
 * delimitador especificado. O resultado é um vetor de strings, que
 * pode ser utilizado para processamento adicional.
 *
 * @param str Constante para a String a ser dividida.
 * @param dlm Delimitador utilizado na divisão.
 * @return Um vetor de strings resultantes da divisão.
 */
String *splitString(const String str, const char *dlm) {
  if (str == NULL || str->data == NULL || dlm == NULL) return NULL;
  char *temp = strdup(str->data);
  if (temp == NULL) {
    perror("Erro ao alocar memória");
    exit(1);
  }
  char *token, *rest = temp; 
  size_t count = 0;
  while ((token = strtok(rest, dlm))) { 
    count++;
    rest = NULL;
  }
  String *split = malloc((count + 1) * sizeof(String));
  if (split == NULL) {
    free(temp);
    perror("Memória insuficiente");
    exit(1);
  }
  rest = temp; 
  size_t i = 0;
  while ((token = strtok(rest, dlm))) {
    split[i] = initString(token); 
    i++;
    rest = NULL; 
  }
  split[i] = NULL;
  free(temp); 
  return split; 
}

/**
 * @brief Localiza um caractere dentro de uma String.
 *
 * Essa função procura por um caractere em uma posição específica dentro
 * da String. Retorna um ponteiro para o caractere localizado ou NULL se
 * não encontrado.
 *
 * @param str Constante para a String.
 * @param pos Posição do caractere a ser localizado.
 * @return Ponteiro para o caractere localizado, ou NULL se não encontrado.
 */
char *getCharAt(const String str, size_t pos) {
  if (str == NULL || pos >= str->size) return NULL;
  return (pos < str->size) ? &str->data[pos] : NULL; 
}

/**
 * @brief Simula o snprintsf usando o tipo String.
 *
 * Essa função formata uma String com base em um modelo especificado e
 * armazena o resultado em uma String de destino. É útil para
 * manipulações de strings onde a formatação é necessária.
 *
 * @param dest Ponteiro para a String de destino.
 * @param format Formato da String.
 */
int snprintsf(String dest, const char *format, ...) {
  if (dest == NULL) return 0;
  va_list args;
  va_start(args, format);
  va_list args_copy;
  va_copy(args_copy, args);
  int size = vsnprintf(NULL, 0, format, args_copy) + 1;
  va_end(args_copy);
  if (size > dest->size) {
    char *new_data = (char *)realloc(dest->data, size);
    if (new_data == NULL) {
      perror("\nMemória insuficiente\n");
      exit(1);
    }
    dest->data = new_data;
    dest->size = size;
  }
  vsnprintf(dest->data, dest->size, format, args);
  va_end(args);
  return 1;
}

/**
 * @brief Pega o conteúdo de uma String
 * 
 * @param str Ponteiro para a String.
 * @return Conteúdo da String.
 */
const char *getString(const String str) {
  if (str == NULL) return NULL;
  return str->data;
}

/** 
* @brief Simula o printf usando o tipo String.
* @param str Ponteiro para a String.
* @return 1 se a String não é vazia, 0 caso contrário.
*/
int printString(String str) {
  if (str == NULL) return 0;
  printf("%s", str->data);
  return 1;
}