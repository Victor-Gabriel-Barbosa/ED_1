#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "stringlib.h"
#include "list.h"
#include "queue.h"
#include "stack.h"
#include "tree.h"

 
/**
 * @brief Estrutura para representação de uma string.
 * 
 * Esta estrutura contém um ponteiro para os dados da string ('data'), 
 * o tamanho atual da string ('size'), e a capacidade alocada 
 * para armazenar os dados ('capacity').
 */
typedef struct string_t {
  char* data;      /**< Ponteiro para os dados da string. */
  size_t size;     /**< Tamanho atual da string (número de caracteres armazenados). */
  size_t capacity; /**< Capacidade total alocada para a string (inclui espaço extra). */
} *string;

/**
 * @brief Calcula o tamanho em bytes da estrutura de dados 'string_t'.
 * 
 * Esta função utiliza o operador 'sizeof' para retornar o tamanho em bytes da estrutura
 * 'string_t', que representa uma string. Ela não retorna o tamanho da string, mas sim a 
 * quantidade de memória que essa estrutura ocupa.
 * 
 * @return O tamanho em bytes da estrutura 'string_t'.
 */
size_t sizeofString() {
  return sizeof(struct string_t);
}

/**
 * @brief Cria uma nova string com capacidade inicial.
 *
 * Essa função aloca memória para uma nova string e define sua capacidade
 * inicial. A string é inicializada com um tamanho de 0, pronta para ser
 * utilizada. É importante chamar essa função antes de realizar outras
 * operações de string.
 *
 * @return A nova string criada.
 */
string stringNew() {
  string newStr = (string)malloc(sizeof(struct string_t));
  if (newStr == NULL) return NULL;
  newStr->size = 0;
  newStr->capacity = 32;
  newStr->data = (char*)malloc((newStr->capacity + 1) * sizeof(char));
  if (newStr->data == NULL) return newStr;
  newStr->data[0] = '\0'; 
  return newStr;
}

/**
 * @brief Inicializa uma string com o conteúdo de uma string literal.
 *
 * Essa função copia o conteúdo de uma string literal para uma nova
 * string, alocando a memória necessária para armazenar o conteúdo. 
 *
 * @param str String literal.
 * @return A nova string inicializada.
 */
string stringInit(const char* str) {
  string newStr = (string)malloc(sizeof(struct string_t));
  if (newStr == NULL) return NULL;
  newStr->size = strlen(str);
  newStr->capacity = newStr->size + 1;
  newStr->data = (char*)malloc(newStr->capacity * sizeof(char));
  if (newStr->data == NULL) return NULL;
  strcpy(newStr->data, str);
  return newStr;
}


/**
 * @brief Libera a memória alocada para a string.
 *
 * Essa função é responsável por desalocar a memória usada pela string,
 * evitando vazamentos de memória. Deve ser chamada sempre que uma string
 * não for mais necessária.
 *
 * @param str String a ser liberado.
 * @return 1 se a string não é vazia, 0 caso contrário.
 */
int stringDestroy(string str) {
  if (str == NULL) return 0;
  free(str->data);
  str->data = NULL;
  str->size = 0;
  str->capacity = 0;
  free(str);
  return 1;
}

/**
 * @brief Obtém o tamanho da string.
 *
 * Essa função retorna o número de caracteres presentes na string, sem
 * contar o terminador nulo. É uma maneira de verificar quantos caracteres
 * estão efetivamente armazenados na string.
 *
 * @param str String.
 * @return O tamanho da string.
 */
size_t stringSize(const string str) {
  return (str == NULL) ? 0 : str->size;
}

/**
 * @brief Redimensiona a capacidade da string.
 *
 * Essa função altera a capacidade da string, permitindo que ela armazene
 * mais ou menos caracteres, conforme necessário. É importante garantir que
 * a nova capacidade seja maior que o tamanho atual da string, se
 * caracteres adicionais forem ser adicionados.
 *
 * @param str String a ser redimensionada.
 * @param new_capacity Nova capacidade da string.
 * @return 1 se a string não é vazia, 0 caso contrário.
 */
int stringResize(string str, const size_t newCapacity) {
  if (str == NULL) return 0; 
  if (newCapacity > str->capacity) {
    char* newData = (char*)realloc(str->data, (newCapacity + 1) * sizeof(char));
    if (newData == NULL) return 0;  
    str->data = newData; 
    str->capacity = newCapacity;  
  }
  return 1;  
}

/**
 * @brief Adiciona um caractere ao final da string.
 *
 * Essa função anexa um caractere ao final da string. Se a capacidade
 * atual da string não for suficiente, a função redimensiona a string
 * antes de adicionar o novo caractere.
 *
 * @param str String.
 * @param c Caractere a ser adicionado.
 * @return A string modificada, ou NULL se ocorrer um erro.
 */
string stringAddChar(string str, const char c) {
  if (str == NULL) return NULL; 
  if (str->size + 1 >= str->capacity && !stringResize(str, str->capacity * 2)) return NULL; 
  str->data[str->size] = c;
  str->size++;
  str->data[str->size] = '\0'; 
  return str;
}

/**
 * @brief Concatena a segunda string na primeira string.
 *
 * Essa função concatena o conteúdo da segunda string (str2) no final
 * da primeira string (str1). A capacidade de str1 será ajustada, se
 * necessário, para acomodar a nova string resultante.
 *
 * @param str1 Ponteiro para a primeira string que será modificada.
 * @param str2 Constante para a segunda string que será concatenada.
 * @return A string modificada (str1), ou NULL se ocorrer um erro.
 */
string stringAppend(string str1, const string str2) {
  if (str1 == NULL || str2 == NULL || str1->data == NULL || str2->data == NULL) return NULL; 
  size_t newSize = str1->size + str2->size;
  if (!stringResize(str1, newSize)) return NULL;
  strcat(str1->data, str2->data);
  str1->size = newSize;
  str1->data[newSize] = '\0'; 
  return str1;
}

/**
 * @brief Concatena uma string com uma string literal.
 *
 * Essa função concatena o conteúdo da primeira string (str1) com uma string
 * literal (str2). A primeira string (str1) será modificada para incluir
 * o conteúdo da segunda string.
 *
 * @param str1 Ponteiro para a primeira string que será modificada.
 * @param str2 Constante para a segunda string literal que será concatenada.
 * @return A string modificada (str1), ou NULL se ocorrer um erro.
 */
string stringCat(string str1, const char* str2) {
  if (str1 == NULL || str2 == NULL) return NULL;
  size_t newSize = str1->size + strlen(str2);
  if (!stringResize(str1, newSize)) return NULL;
  strcat(str1->data, str2);
  str1->size = newSize;
  str1->data[newSize] = '\0'; 
  return str1; 
}

/**
 * @brief Cria uma cópia de uma string.
 *
 * @param str A string a ser copiada.
 * @return Uma cópia da string, ou NULL se a alocação de memória falhar.
 */
string stringCopy(const string str) {
  if (str == NULL) return NULL;
  string newStr = (string)malloc(sizeof(struct string_t));
  if (newStr == NULL) return NULL;
  newStr->size = str->size;
  newStr->capacity = newStr->size + 1;
  newStr->data = (char*)malloc(newStr->capacity * sizeof(char));
  if (newStr->data == NULL) return NULL;
  strcpy(newStr->data, str->data);
  return newStr;
}

/**
 * @brief Compara duas strings lexicograficamente.
 *
 * Esta função compara duas instâncias da struct string e retorna um valor
 * inteiro que indica a relação lexicográfica entre elas:
 * - Menor que 0: str1 é menor que str2
 * - Igual a 0: str1 é igual a str2
 * - Maior que 0: str1 é maior que str2
 *
 * @param str1 Constante para a primeira string.
 * @param str2 Constante para a segunda string.
 * @return Um valor inteiro conforme a relação entre as Strings.
 */
int stringCmp(const string str1, const string str2) {
  return (str1 == NULL || str2 == NULL) ? 0 : strcmp(str1->data, str2->data);
}

/**
 * @brief Lê uma string do teclado.
 *
 * Essa função solicita ao usuário que insira uma string pelo teclado.
 * A entrada é lida até que o usuário pressione a tecla Enter. A string
 * resultante é retornada para uso posterior.
 *
 * @return A string lida, ou NULL se ocorrer um erro.
 */
string stringInput() {
  string input = (string)malloc(sizeof(struct string_t));
  if (input == NULL) return NULL;
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
 * Essa função percorre a string e substitui todas as ocorrências do
 * caractere especificado por outro. Retorna o número de substituições
 * realizadas, o que pode ser útil para relatórios ou verificações.
 *
 * @param str String.
 * @param a Caractere a ser substituído.
 * @param b Caractere que irá substituir.
 * @return O número de substituições realizadas.
 */
size_t stringReplace(string str, const char a, const char b) {
  size_t count = 0;
  for (size_t i = 0; i < str->size; i++) {
    if (str->data[i] == a) { 
      str->data[i] = b;
      count++;
    }
  }
  return count;
}

/**
 * @brief Encontra uma substring.
 *
 * Essa função verifica a existência de uma substring dentro de uma string
 * principal. Retorna o índice da primeira ocorrência, ou -1 se a
 * substring não for encontrada. É uma função útil para pesquisa de
 * padrões ou validação de conteúdo.
 *
 * @param str Constante para a string.
 * @param substr Substring a ser encontrada.
 * @return O índice da substring, ou -1 se não encontrada.
 */
int stringIndex(const string str, const char* substr) {
  if (str == NULL || substr == NULL) return -1;
  char* pos = strstr(str->data, substr);
  return pos ? (int)(pos - str->data) : -1; 
}

/**
 * @brief Inverte o conteúdo da string.
 *
 * Essa função inverte a ordem dos caracteres dentro da string, criando
 * uma nova string. É útil em situações onde se deseja manipular ou
 * transformar a representação da string.
 *
 * @param str A string a ser invertida.
 * @return A string invertida, ou NULL se ocorrer um erro.
 */
string stringReverse(string str) {
  if (str == NULL || str->size == 0 || str->data == NULL) return NULL;
  size_t left = 0;
  size_t right = str->size - 1;
  while (left < right) {
    char temp = str->data[left];
    str->data[left] = str->data[right];
    str->data[right] = temp;
    left++;
    right--;
  }
  return str;
}

/**
 * @brief Divide uma string em tokens usando um delimitador.
 *
 * Essa função separa a string original em substrings com base em um
 * delimitador especificado. O resultado é um vetor de strings, que
 * pode ser utilizado para processamento adicional.
 *
 * @param str Constante para a string a ser dividida.
 * @param dlm Delimitador utilizado na divisão.
 * @return Um vetor de strings resultantes da divisão.
 */
string* stringSplit(const string str, const char* dlm) {
  if (str == NULL || str->data == NULL || dlm == NULL) return NULL;
  char* temp = strdup(str->data);  
  if (temp == NULL) return NULL; 
  char* token;   
  char* rest = temp; 
  size_t count = 0;  
  while ((token = strtok(rest, dlm))) { 
    count++;
    rest = NULL;
  }
  string* split = malloc((count + 1) * sizeof(string));  
  if (split == NULL) {  
    free(temp); 
    return NULL;
  }
  rest = temp;  
  size_t i = 0;
  while ((token = strtok(rest, dlm))) {  
    split[i] = stringInit(token); 
    i++;
    rest = NULL; 
  }
  split[i] = NULL;  
  free(temp);  
  return split;  
}

/**
 * @brief Pega o conteúdo de uma string
 * 
 * @param str String.
 * @return Conteúdo da string.
 */
const char* stringGet(const string str) {
  return (str == NULL) ? NULL : str->data;
}

/**
 * @brief Localiza um caractere dentro de uma string.
 *
 * Essa função procura por um caractere em uma posição específica dentro
 * da string. Retorna um ponteiro para o caractere localizado ou NULL se
 * não encontrado.
 *
 * @param str Constante para a string.
 * @param pos Posição do caractere a ser localizado.
 * @return Ponteiro para o caractere localizado, ou NULL se não encontrado.
 */
char* stringGetChar(const string str, size_t pos) {
  if (str == NULL || pos >= str->size) return NULL;
  return (pos < str->size) ? &str->data[pos] : NULL; 
}

/**
 * @brief Simula o snprintf usando o tipo string.
 *
 * Essa função formata uma string com base em um modelo especificado e
 * armazena o resultado em uma string de destino. É útil para
 * manipulações de strings onde a formatação é necessária.
 *
 * @param dest String de destino.
 * @param format Formato da string.
 * @return A string modificada (str1), ou NULL se ocorrer um erro.
 */
string stringSnprintf(string dest, const char* format, ...) {
  if (dest == NULL) return NULL;
  va_list args;
  va_start(args, format);
  va_list args_copy;
  va_copy(args_copy, args);
  size_t size = vsnprintf(NULL, 0, format, args_copy) + 1;
  va_end(args_copy);
  if (size > dest->size) {
    char* new_data = (char*)realloc(dest->data, size);
    if (new_data == NULL) return NULL;
    dest->data = new_data;
    dest->size = size;
  }
  vsnprintf(dest->data, dest->size, format, args);
  va_end(args);
  return dest;
}

/**
 * @brief Transforma um dado qualquer em uma string.
 * 
 * A função converte diferentes tipos de dados (como int, float, char, etc.)
 * em uma instância da struct string. Ela utiliza um sistema de verificação
 * de tipo dinâmico para determinar qual conversão realizar.
 * 
 * @param info Tipo do dado que será transformado.
 * @return Uma nova instância de string contendo o conteúdo transformado.
 */
string toString(const obj info) {
  string str = stringNew();
  size_t initialCapacity = 64; 
  if (!stringResize(str, initialCapacity)) return NULL;
  void* data = objGetData(info);
  size_t requiredSize = 0;
  switch (objGetType(info)) {
    case TYPE_CHAR: {
      requiredSize = snprintf(str->data, str->capacity, "%c", *(char*)data);
      break;
    }
    case TYPE_BOOL: {
      const char* boolStr = (*(bool*)data) ? "true" : "false";
      requiredSize = strlen(boolStr);
      if (!stringResize(str, requiredSize + 1)) return NULL;
      strcpy(str->data, boolStr); 
      str->size = requiredSize;
      return str;
    }
    case TYPE_INT: {
      requiredSize = snprintf(str->data, str->capacity, "%d", *(int*)data);
      break;
    }
    case TYPE_FLOAT: {
      requiredSize = snprintf(str->data, str->capacity, "%f", *(float*)data);
      break;
    }
    case TYPE_DOUBLE: {
      requiredSize = snprintf(str->data, str->capacity, "%lf", *(double*)data);
      break;
    }
    case TYPE_CHAR_PTR: {
      requiredSize = snprintf(str->data, str->capacity, "%s", (char*)data);
      break;
    }
    case TYPE_STRING: {
      string srcStr = (string)data;
      if (srcStr == NULL) return NULL;
      if (srcStr->size + 1 > str->capacity && !stringResize(str, srcStr->size + 1)) return NULL;
      memcpy(str->data, srcStr->data, srcStr->size);
      str->data[srcStr->size] = '\0'; 
      str->size = srcStr->size;
      return str;
    }
    case TYPE_LIST: {
      list lst = (list)data;  
      if (lst == NULL) return NULL;
      string strList = listToString(lst);
      if (!strList || !stringResize(str, strList->size + 1)) return NULL;
      memcpy(str->data, strList->data, strList->size);
      str->data[strList->size] = '\0';
      str->size = strList->size;
      stringDestroy(strList); 
      return str;
    }
    case TYPE_QUEUE: {
      queue qeu = (queue)data;
      if (qeu == NULL) return NULL;
      string strQueue = queueToString(qeu);
      if (!strQueue || !stringResize(str, strQueue->size + 1)) return NULL;
      memcpy(str->data, strQueue->data, strQueue->size);
      str->data[strQueue->size] = '\0';
      str->size = strQueue->size;
      stringDestroy(strQueue); 
      return str;
    }
    case TYPE_STACK: {
      stack stk = (stack)data;
      if (stk == NULL) return NULL;
      string strStack = stackToString(stk);
      if (!strStack || !stringResize(str, strStack->size + 1)) return NULL;
      memcpy(str->data, strStack->data, strStack->size);
      str->data[strStack->size] = '\0';
      str->size = strStack->size;
      stringDestroy(strStack); 
      return str;
    }
    case TYPE_TREE: {
      tree tre = (tree)data;
      if (tre == NULL) return NULL; 
      string strTree = treeToString(tre);
      if (!strTree || !stringResize(str, strTree->size + 1)) return NULL;
      memcpy(str->data, strTree->data, strTree->size);
      str->data[strTree->size] = '\0';
      str->size = strTree->size;
      stringDestroy(strTree);
      return str;
    }
    case TYPE_UNKNOWN: {
      size_t dataSize = objGetSize(info);
      if (dataSize + 1 > str->capacity && !stringResize(str, dataSize + 1)) return NULL;
      memcpy(str->data, data, dataSize);
      str->data[dataSize] = '\0';
      str->size = dataSize;
      return str;
    }
    default: 
      return NULL;
  }
  if (requiredSize >= str->capacity) {
    if (!stringResize(str, requiredSize + 1)) return NULL;
    snprintf(str->data, str->capacity, "%d", *(int*)data);
  }
  str->size = requiredSize;
  return str;
}

/** 
 * @brief Exibe uma string na tela.
 * @param str String a ser exibida.
 * @return 1 se a string não é vazia, 0 caso contrário.
 */
int stringPrint(const string str) {
  if (str == NULL) return 0;
  printf("%s", str->data);
  return 1;
}