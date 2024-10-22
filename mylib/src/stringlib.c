#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <list.h>
#include <queue.h>
#include <stack.h>
#include <stringlib.h>
 
/**
 * @brief Estrutura para representação de uma string.
 * 
 * Esta estrutura contém um ponteiro para os dados da string ('data'), 
 * o tamanho atual da string ('size'), e a capacidade alocada 
 * para armazenar os dados ('capacity').
 */
typedef struct string_t {
  char* data;       /**< Ponteiro para os dados da string. */
  size_t size;      /**< Tamanho atual da string (número de caracteres armazenados). */
  size_t capacity;  /**< Capacidade total alocada para a string (inclui espaço extra). */
} *string;

/**
 * @brief Obtém o tamanho da struct string.
 * 
 * @return O tamanho da struct string.
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
    // Aloca memória para string
    string newStr = (string)malloc(sizeof(struct string_t));
    if (newStr == NULL) return NULL;

    // Define o tamanho inicial e a capacidade
    newStr->size = 0;
    newStr->capacity = 32;

    // Aloca memória para os dados da string
    newStr->data = (char*)malloc((newStr->capacity + 1) * sizeof(char));
    if (newStr->data == NULL) return newStr;  

    // Inicializa a string vazia
    newStr->data[0] = '\0'; 
    return newStr;
}

/**
 * @brief Inicializa uma string com o conteúdo de uma string literal.
 *
 * Essa função copia o conteúdo de uma string literal para uma nova
 * string, alocando a memória necessária para armazenar o conteúdo. 
 *
 * @param str Objeto string literal.
 * @return A nova string inicializada.
 */
string stringInit(const char* str) {
  // Aloca memória para string
  string newStr = (string)malloc(sizeof(struct string_t));
  if (newStr == NULL) return NULL;

  // Define o tamanho da string e capacidade
  newStr->size = strlen(str);
  newStr->capacity = newStr->size + 1;

  // Aloca memória para os dados da string
  newStr->data = (char*)malloc(newStr->capacity * sizeof(char));
  if (newStr->data == NULL) return NULL;

  // Copia a string passada para 'data'
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
 * @param str Objeto string a ser liberado.
 * @return 1 se a string não é vazia, 0 caso contrário.
 */
int stringDestroy(string str) {
  // Verifica se a string existe
  if (str == NULL) return 0;
  
  // Desaloca os dados da string e libera a memória alocada
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
 * @param str Objeto string.
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
 * @param str Objeto string a ser redimensionado.
 * @param new_capacity Nova capacidade da string.
 * @return 1 se a string não é vazia, 0 caso contrário.
 */
int stringResize(string str, size_t newCapacity) {
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
 * @param str Objeto string.
 * @param c Caractere a ser adicionado.
 * @return 1 se a string não é vazia, 0 caso contrário.
 */
int stringAddChar(string str, char c) {
  if (str == NULL) return 0; 
  if (str->size + 1 >= str->capacity && !stringResize(str, str->capacity * 2)) return 0;  
  str->data[str->size] = c;
  str->size++;
  str->data[str->size] = '\0'; 
  return 1; 
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
 * @return A string modificada (str1).
 */
string stringAppend(string str1, const string str2) {
  if (str1 == NULL || str2 == NULL || str1->data == NULL || str2->data == NULL) return str1; 
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
 * @return A string modificada (str1).
 */
string stringCat(string str1, const char* str2) {
  if (str1 == NULL || str2 == NULL) return str1;
  size_t newSize = str1->size + strlen(str2);
  if (!stringResize(str1, newSize)) return 0;
  strcat(str1->data, str2);
  str1->size = newSize;
  str1->data[newSize] = '\0'; 
  return str1; 
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
 * @return Retorna um valor inteiro conforme a relação entre as Strings.
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
 * @return A string lida.
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
 * @param str Objeto string.
 * @param a Caractere a ser substituído.
 * @param b Caractere que irá substituir.
 * @return O número de substituições realizadas.
 */
size_t stringReplace(string str, const char a, const char b) {
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
 * Essa função verifica a existência de uma substring dentro de uma string
 * principal. Retorna o índice da primeira ocorrência, ou -1 se a
 * substring não for encontrada. É uma função útil para pesquisa de
 * padrões ou validação de conteúdo.
 *
 * @param str Constante para a string.
 * @param substr Objeto substring a ser encontrada.
 * @return O índice da substring, ou -1 se não encontrada.
 */
int stringIndexOf(const string str, const char* substr) {
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
 * @return A string invertida.
 */
string stringReverse(const string str) {
  if (str == NULL || str->size == 0 || str->data == NULL) return str;
  string reverse = stringNew(); 
  for (size_t i = 0; i < str->size; i++) stringAddChar(reverse, str->data[str->size - 1 - i]);
  return reverse; 
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
  // Verifica se a string de entrada ou o delimitador são inválidos.
  if (str == NULL || str->data == NULL || dlm == NULL) return NULL;

  // Faz uma cópia temporária da string original para ser manipulada.
  char* temp = strdup(str->data);  
  if (temp == NULL) return NULL; // Verifica se a cópia foi bem-sucedida.

  char* token;   // Armazena os tokens extraídos.
  char* rest = temp;  // 'rest' mantém a posição atual na string.
  size_t count = 0;   // Contador para o número de tokens.

  // Conta quantos tokens a string terá usando o delimitador.
  while ((token = strtok(rest, dlm))) { 
    count++;
    rest = NULL; // Passa NULL nas chamadas subsequentes para continuar o strtok.
  }

  // Aloca memória para o vetor de strings (incluso espaço para NULL no final).
  string* split = malloc((count + 1) * sizeof(string));  
  if (split == NULL) {  // Verifica se a alocação foi bem-sucedida.
    free(temp);  // Libera a memória temporária em caso de falha.
    return NULL;
  }

  // Reinicializa a variável rest para processar novamente a string.
  rest = temp;  
  size_t i = 0;

  // Divide a string original em tokens e armazena cada um no vetor de strings.
  while ((token = strtok(rest, dlm))) {  
    split[i] = stringInit(token);  // Cria uma nova string para cada token.
    i++;
    rest = NULL;  // Continuar a extração a partir do próximo token.
  }

  split[i] = NULL;  // Marca o final do vetor de strings com NULL.

  // Libera a memória temporária usada para manipulação da string original.
  free(temp);  

  // Retorna o vetor de strings resultante da divisão.
  return split;  
}

/**
 * @brief Pega o conteúdo de uma string
 * 
 * @param str Objeto string.
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
 * @param dest Objeto string de destino.
 * @param format Formato da string.
 * @return Retorna 1 em caso de sucesso ou 0 em caso de falha.
 */
int stringSnprintf(string dest, const char* format, ...) {
  // Verifica se a string de destino é nula, retornando 0 caso seja.
  if (dest == NULL) return 0;

  // Inicializa a lista de argumentos variáveis com base no format.
  va_list args;
  va_start(args, format);

  // Cria uma cópia da lista de argumentos para calcular o tamanho necessário.
  va_list args_copy;
  va_copy(args_copy, args);

  // Calcula o tamanho necessário da string formatada (vsnprintf retorna o tamanho).
  size_t size = vsnprintf(NULL, 0, format, args_copy) + 1; // +1 para o terminador nulo.
  
  // Encerra a cópia da lista de argumentos.
  va_end(args_copy);

  // Se o tamanho necessário for maior que o tamanho atual da string, realoca memória.
  if (size > dest->size) {
      // Realoca a memória da string para armazenar a nova string formatada.
      char* new_data = (char*)realloc(dest->data, size);
      // Se a realocação falhar, retorna 0.
      if (new_data == NULL) return 0;
      // Atualiza o ponteiro e o tamanho da string.
      dest->data = new_data;
      dest->size = size;
  }

  // Escreve a string formatada na string de destino.
  vsnprintf(dest->data, dest->size, format, args);

  // Encerra a lista de argumentos variáveis.
  va_end(args);

  // Retorna 1 indicando sucesso.
  return 1;
}

/** 
 * @brief Exibe uma string na tela.
 * @param str Objeto string.
 * @return 1 se a string não é vazia, 0 caso contrário.
 */
int stringPrint(string str) {
  if (str == NULL) return 0;
  printf("%s", str->data);
  return 1;
}

/**
 * @brief Transforma um dado qualquer em uma string.
 * 
 * A função converte diferentes tipos de dados (como int, float, char, etc.)
 * em uma instância da struct string. Ela utiliza um sistema de verificação
 * de tipo dinâmico para determinar qual conversão realizar.
 * 
 * @param info Tipo do dado que será transformado.
 * @return Uma nova instância da struct string contendo o conteúdo transformado.
 */
string toString(obj info) {
  // Cria uma nova string vazia
  string str = stringNew();

  // Define a capacidade inicial da string para 64 caracteres
  size_t initialCapacity = 64; 

  // Redimensiona a string para a capacidade inicial e verifica se foi bem-sucedido
  if (!stringResize(str, initialCapacity)) return NULL;

  // Obtém o ponteiro para o dado armazenado em 'info'
  void* data = objGetData(info);
  
  // Variável para armazenar o tamanho necessário da string
  size_t requiredSize = 0;

  // Verifica o tipo de dado armazenado em 'info' para decidir como convertê-lo
  switch (objGetType(info)) {

    // Caso o dado seja do tipo int
    case TYPE_INT: {
      // Converte o inteiro em string e armazena na string
      requiredSize = snprintf(str->data, str->capacity, "%d", *(int*)data);
      break;
    }

    // Caso o dado seja do tipo float
    case TYPE_FLOAT: {
      // Converte o float em string
      requiredSize = snprintf(str->data, str->capacity, "%f", *(float*)data);
      break;
    }

    // Caso o dado seja do tipo double
    case TYPE_DOUBLE: {
      // Converte o double em string
      requiredSize = snprintf(str->data, str->capacity, "%lf", *(double*)data);
      break;
    }

    // Caso o dado seja do tipo char
    case TYPE_CHAR: {
      // Converte o caractere em string
      requiredSize = snprintf(str->data, str->capacity, "%c", *(char*)data);
      break;
    }

    // Caso o dado seja uma string literal (char*)
    case TYPE_CHAR_PTR: {
      // Converte o ponteiro de char para string
      requiredSize = snprintf(str->data, str->capacity, "%s", (char*)data);
      break;
    }

    // Caso o dado seja um booleano
    case TYPE_BOOL: {
      // Verifica o valor do booleano e converte para "true" ou "false"
      const char* boolStr = (*(bool*)data) ? "true" : "false";
      requiredSize = strlen(boolStr);
      // Redimensiona a string para acomodar a nova string
      if (!stringResize(str, requiredSize + 1)) return NULL;
      strcpy(str->data, boolStr);  // Copia o valor "true" ou "false" para a string
      str->size = requiredSize;
      return str;
    }

    // Caso o dado já seja do tipo string
    case TYPE_STRING: {
      string srcStr = *(string *)data;
      if (srcStr == NULL) return NULL;
      // Redimensiona a string se necessário e copia o conteúdo
      if (srcStr->size + 1 > str->capacity && !stringResize(str, srcStr->size + 1)) return NULL;
      memcpy(str->data, srcStr->data, srcStr->size);
      str->data[srcStr->size] = '\0';  // Adiciona o caractere de terminação
      str->size = srcStr->size;
      return str;
    }

    // Caso o dado seja uma lista
    case TYPE_LIST: {
      list lst = (list)objGetData(info);  
      if (lst != NULL) {
        string strList = listToString(lst);
        // Converte a lista para string e redimensiona a string principal
        if (!strList || !stringResize(str, strList->size + 1)) return NULL;
        memcpy(str->data, strList->data, strList->size);
        str->data[strList->size] = '\0';
        str->size = strList->size;
        stringDestroy(strList);  // Libera a string temporária
      } else { // Caso a lista seja inválida, retorna "Invalid list"
        const char* invalidStr = "Invalid list";
        requiredSize = strlen(invalidStr);
        if (!stringResize(str, requiredSize + 1)) return NULL;
        strcpy(str->data, invalidStr);
        str->size = requiredSize;
      }
      return str;
    }

    // Caso o dado seja uma fila (queue)
    case TYPE_QUEUE: {
      queue qeu = (queue)objGetData(info);
      if (qeu != NULL) {
        string strQueue = queueToString(qeu);
        // Converte a fila para string e redimensiona a string principal
        if (!strQueue || !stringResize(str, strQueue->size + 1)) return NULL;
        memcpy(str->data, strQueue->data, strQueue->size);
        str->data[strQueue->size] = '\0';
        str->size = strQueue->size;
        stringDestroy(strQueue);  // Libera a string temporária
      } else {
        // Caso a fila seja inválida, retorna "Invalid queue"
        const char* invalidStr = "Invalid queue";
        requiredSize = strlen(invalidStr);
        if (!stringResize(str, requiredSize + 1)) return NULL;
        strcpy(str->data, invalidStr);
        str->size = requiredSize;
      }
      return str;
    }

    // Caso o dado seja uma pilha (stack)
    case TYPE_STACK: {
      stack stk = (stack)objGetData(info);
      if (stk != NULL) {
        string strStack = stackToString(stk);
        // Converte a pilha para string e redimensiona a string principal
        if (!strStack || !stringResize(str, strStack->size + 1)) return NULL;
        memcpy(str->data, strStack->data, strStack->size);
        str->data[strStack->size] = '\0';
        str->size = strStack->size;
        stringDestroy(strStack);  // Libera a string temporária
      } else {
        // Caso a pilha seja inválida, retorna "Invalid stack"
        const char* invalidStr = "Invalid stack";
        requiredSize = strlen(invalidStr);
        if (!stringResize(str, requiredSize + 1)) return NULL;
        strcpy(str->data, invalidStr);
        str->size = requiredSize;
      }
      return str;
    }

    // Caso o tipo de dado seja desconhecido
    case TYPE_UNKNOWN: {
      size_t dataSize = objGetSize(info);
      // Redimensiona a string e copia os dados brutos
      if (dataSize + 1 > str->capacity && !stringResize(str, dataSize + 1)) return NULL;
      memcpy(str->data, data, dataSize);
      str->data[dataSize] = '\0';
      str->size = dataSize;
      return str;
    }

    // Tipo de dado inválido ou não suportado
    default: {
      const char* invalidStr = "Invalid Type";
      requiredSize = strlen(invalidStr);
      if (!stringResize(str, requiredSize + 1)) return NULL;
      strcpy(str->data, invalidStr);
      str->size = requiredSize;
      return str;
    }
  }

  // Verifica se o tamanho necessário excede a capacidade da string e redimensiona se necessário
  if (requiredSize >= str->capacity) {
    if (!stringResize(str, requiredSize + 1)) return NULL;
    // Reexecuta a conversão após o redimensionamento
    snprintf(str->data, str->capacity, "%d", *(int*)data);
  }

  // Define o tamanho da string e retorna
  str->size = requiredSize;
  return str;
}
