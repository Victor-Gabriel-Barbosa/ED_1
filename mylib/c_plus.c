#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include "include/c_plus.h"

/**
 * Captura exceções e exibe uma mensagem de erro.
 *
 * Essa função verifica o valor de errno para determinar o tipo de erro
 * ocorrido e exibe uma mensagem formatada no stderr, encerrando o programa
 * com um código de falha. É útil para tratar erros de alocação de memória
 * ou de operações de arquivo.
 */
void catchError() { 
  fprintf(stderr, C_FMT_ERROR("\n[Erro: %s!]\n"), strerror(errno));
  exit(EXIT_FAILURE);
}

/**
 * Cria uma nova string com capacidade inicial.
 *
 * Essa função aloca memória para uma nova string e define sua capacidade
 * inicial. A string é inicializada com um tamanho de 0, pronta para ser
 * utilizada. É importante chamar essa função antes de realizar outras
 * operações de string.
 *
 * @return A nova string criada.
 */
String newString() {
  String new;
  new.size = 0;
  new.capacity = 32; 
  new.data = (char *)malloc((new.capacity + 1) * sizeof(char));
  new.data[0] = '\0'; 
  return new;
}

/**
 * Inicializa uma string com o conteúdo de uma string existente.
 *
 * Essa função copia o conteúdo de uma string existente para uma nova
 * string, alocando a memória necessária para armazenar a cópia. A função
 * é útil para duplicar strings quando necessário.
 *
 * @param str Ponteiro para a string existente.
 * @return A nova string inicializada.
 */
String initString(const char *str) {
  String new;
  new.size = strlen(str);
  new.capacity = new.size + 1; 
  new.data = verAlloc((char *)malloc((new.capacity) * sizeof(char)));
  strcpy(new.data, str);
  return new;
}

/**
 * Libera a memória alocada para a string.
 *
 * Essa função é responsável por desalocar a memória usada pela string,
 * evitando vazamentos de memória. Deve ser chamada sempre que uma string
 * não for mais necessária.
 *
 * @param str Ponteiro para a string a ser liberada.
 */
void destroyString(String *str) {
  free(str->data);
  str->data = NULL;
  str->size = 0;
  str->capacity = 0;
}

/**
 * Obtém o tamanho da string.
 *
 * Essa função retorna o número de caracteres presentes na string, sem
 * contar o terminador nulo. É uma maneira de verificar quantos caracteres
 * estão efetivamente armazenados na string.
 *
 * @param str Ponteiro para a string.
 * @return O tamanho da string.
 */
size_t sizeString(const String str) {
  return str.size;
}

/**
 * Redimensiona a capacidade da string.
 *
 * Essa função altera a capacidade da string, permitindo que ela armazene
 * mais ou menos caracteres, conforme necessário. É importante garantir que
 * a nova capacidade seja maior que o tamanho atual da string, se
 * caracteres adicionais forem a serem adicionados.
 *
 * @param str Ponteiro para a string a ser redimensionada.
 * @param new_capacity Nova capacidade da string.
 */
void resizeString(String *str, size_t new_capacity) {
  if (new_capacity > str->capacity) {
    str->data = (char *)realloc(str->data, (new_capacity + 1) * sizeof(char));
    str->capacity = new_capacity;
  }
}

/**
 * Adiciona um caractere ao final da string.
 *
 * Essa função anexa um caractere ao final da string. Se a capacidade
 * atual da string não for suficiente, a função redimensiona a string
 * antes de adicionar o novo caractere.
 *
 * @param str Ponteiro para a string.
 * @param c Caractere a ser adicionado.
 */
void addChar(String *str, char c) {
  if (str->size + 1 >= str->capacity)resizeString(str, str->capacity * 2);
  str->data[str->size] = c;
  str->size++;
  str->data[str->size] = '\0'; 
}

/**
 * Concatena duas strings.
 *
 * Essa função cria uma nova string resultante da concatenação de duas
 * strings. A nova string terá a soma dos tamanhos das duas strings
 * originais.
 *
 * @param str1 Constante para a primeira string.
 * @param str2 Constante para a segunda string.
 * @return A string resultante da concatenação.
 */
String appendStrings(const String str1, const String str2) {
  String append = newString();
  append.size = str1.size + str2.size;
  append.capacity = append.size;
  append.data = verAlloc((char *)malloc((append.capacity + 1) * sizeof(char)));
  strcpy(append.data, str1.data);
  strcat(append.data, str2.data);
  return append;
}

/**
 * Compara duas strings.
 *
 * Essa função verifica se duas strings são iguais. Retorna 1 se as
 * strings forem iguais, e 0 caso contrário. É uma função útil para
 * validação e verificação de igualdade em comparações.
 *
 * @param str1 Constante para a primeira string.
 * @param str2 Constante para a segunda string.
 * @return 1 se as strings forem iguais, 0 caso contrário.
 */
int isStringEqual(const String str1, const String str2) {
  return strcmp(str1.data, str2.data) == 0;
}

/**
 * Lê uma string do teclado.
 *
 * Essa função solicita ao usuário que insira uma string pelo teclado.
 * A entrada é lida até que o usuário pressione a tecla Enter. A string
 * resultante é retornada para uso posterior.
 *
 * @return A string lida.
 */
String inputString() {
  String str; 
  str.data = NULL; 
  size_t len = 0;
  if (getline(&str.data, &len, stdin) == -1) {
    str.size = 0;
    str.capacity = 0;
    return str;
  }
  str.data[strcspn(str.data, "\n")] = '\0'; 
  str.size = strlen(str.data); 
  str.capacity = len;
  return str;
}

/**
 * Substitui todas as ocorrências de um caractere por outro.
 *
 * Essa função percorre a string e substitui todas as ocorrências do
 * caractere especificado por outro. Retorna o número de substituições
 * realizadas, o que pode ser útil para relatórios ou verificações.
 *
 * @param str Ponteiro para a string.
 * @param a Caractere a ser substituído.
 * @param b Caractere que irá substituir.
 * @return O número de substituições realizadas.
 */
size_t replaceChar(String *str, const char a, const char b) {
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
 * Encontra uma substring.
 *
 * Essa função verifica a existência de uma substring dentro de uma string
 * principal. Retorna o índice da primeira ocorrência, ou -1 se a
 * substring não for encontrada. É uma função útil para pesquisa de
 * padrões ou validação de conteúdo.
 *
 * @param str Constante para a string.
 * @param substr Ponteiro para a substring a ser encontrada.
 * @return O índice da substring, ou -1 se não encontrada.
 */
int indexOfSubstring(const String str, const char *substr) {
  char *pos = strstr(str.data, substr);
  return pos ? (int)(pos - str.data) : -1; 
}

/**
 * Inverte o conteúdo da string.
 *
 * Essa função inverte a ordem dos caracteres dentro da string, criando
 * uma nova string. É útil em situações onde se deseja manipular ou
 * transformar a representação da string.
 *
 * @param str A string a ser invertida.
 * @return A string invertida.
 */
String reverseString(const String str) {
  if (str.size == 0 || str.data == NULL) return str;
  String reverse = newString(); 
  for (size_t i = 0; i < str.size; i++) {
    addChar(&reverse, str.data[str.size - 1 - i]);
  }
  return reverse; 
}

/**
 * Divide uma string em tokens usando um delimitador.
 *
 * Essa função separa a string original em substrings com base em um
 * delimitador especificado. O resultado é um vetor de strings, que
 * pode ser utilizado para processamento adicional.
 *
 * @param str Constante para a string a ser dividida.
 * @param dlm Delimitador utilizado na divisão.
 * @return Um vetor de strings resultantes da divisão.
 */
String *splitString(const String str, const char *dlm) {
  char *temp = strdup(str.data);
  char *token, *rest = temp; 
  size_t count = 0;
  while ((token = strtok(rest, dlm))) { 
    count++;
    rest = NULL;
  }
  free(temp); 
  temp = strdup(str.data);
  rest = temp; 
  String *split = verAlloc((String *)malloc((count + 1) * sizeof(String)));
  size_t i = 0;
  while ((token = strtok(rest, dlm))) {
    split[i] = initString(token);
    i++;
    rest = NULL; 
  }
  split[i].data = NULL; 
  split[i].size = 0; 
  free(temp); 
  return split; 
}

/**
 * Localiza um caractere dentro de uma string.
 *
 * Essa função procura por um caractere em uma posição específica dentro
 * da string. Retorna um ponteiro para o caractere localizado ou NULL se
 * não encontrado.
 *
 * @param str Constante para a string.
 * @param pos Posição do caractere a ser localizado.
 * @return Ponteiro para o caractere localizado, ou NULL se não encontrado.
 */
char *getCharAt(const String str, size_t pos) {
  return (pos < str.size) ? &str.data[pos] : NULL; 
}

/**
 * Limpa o buffer do teclado.
 *
 * Essa função é utilizada para descartar qualquer entrada pendente no
 * buffer de entrada do teclado, evitando problemas em leituras
 * subsequentes. É frequentemente chamada após a leitura de caracteres
 * para limpar o buffer.
 */
void cleanBuffer() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Limpa a tela do terminal.
 *
 * Essa função executa um comando do sistema para limpar a tela do
 * terminal, proporcionando uma interface mais limpa para o usuário.
 * É útil para melhorar a legibilidade durante a interação com o
 * programa.
 */
void cleanScreen() {
  #ifdef _WIN32
    system("clean");
  #else 
    system("clear");
  #endif 
} 

/**
 * Espera uma entrada do usuário antes de limpar a tela do terminal.
 *
 * Essa função exibe uma mensagem e aguarda a confirmação do usuário
 * antes de limpar a tela. Isso permite que o usuário veja informações
 * importantes antes de continuar.
 *
 * @param msg Mensagem a ser exibida antes de limpar a tela.
 */
void waitCleanScreen(const char *msg) {
  printf("\n%s", msg);
  cleanBuffer();
  clean();
}

/**
 * Escolhe um número inteiro dentro de um intervalo.
 *
 * Essa função solicita ao usuário que escolha um número dentro de um
 * intervalo especificado. A função garante que a entrada seja válida e
 * dentro dos limites estabelecidos. Retorna o número escolhido pelo
 * usuário.
 *
 * @param msg Mensagem a ser exibida.
 * @param min Valor mínimo do intervalo.
 * @param max Valor máximo do intervalo.
 * @return O número escolhido pelo usuário.
 */
int choose(const char *msg, const int min, const int max) {
  while (1) { // Verifica se o número é válido
    int num;
    printf("\n%s\n", msg);
    printf("%s[%d%s-%s%d]%s: ", C_BOLD C_BLUE, min, C_MAGENTA, C_RED, max, C_RESET);
    scanf("%d", &num);
    cleanBuffer();
    if (num >= min && num <= max) return num;
    printf(C_FMT_ERROR("\n[Número inválido! Tente novamente...]\n"));
  }
}

/**
 * Confirma uma ação com o usuário.
 *
 * Essa função exibe uma mensagem ao usuário, solicitando uma
 * confirmação. O usuário pode responder com um 'sim' ou 'não', e a
 * função retorna 1 para confirmação e 0 caso contrário.
 *
 * @param msg Mensagem a ser exibida.
 * @return 1 se o usuário confirmou, 0 caso contrário.
 */
int confirm(const char *msg) { 
  while (1) { // Confirma uma ação
    printf("\nDeseja %s%s%s?\n", C_BOLD C_RED, msg, C_RESET);
    printf("%s[S%s/%sN]%s: ", C_BOLD C_BLUE, C_MAGENTA, C_RED, C_RESET);
    char op = tolower(getchar());
    cleanBuffer();
    if (op == 's') return 1;
    if (op == 'n') return 0;
    printf(C_FMT_ERROR("\n[Opção inválida!]\n"));
  } 
}

/**
 * Analisa se a alocação foi bem-sucedida.
 *
 * Essa função verifica se um ponteiro resultante de uma alocação de
 * memória é NULL. Se for, exibe uma mensagem de erro e encerra o
 * programa. Essa função é crucial para garantir que o programa não
 * continue a executar com ponteiros inválidos.
 *
 * @param pt Ponteiro para o bloco de memória alocado.
 * @return O ponteiro original, se bem-sucedido.
 */
void *verAlloc(void *pt) {
  if (pt == NULL) {
    catchError();
    exit(1);
  }
  return pt;
}

/**
 * Simula o printf e aceita novos tipos.
 *
 * Essa função permite a formatação e exibição de strings, com suporte
 * para tipos personalizados. Pode ser usada para gerar saídas formatadas
 * de maneira flexível.
 *
 * @param format Formato da string.
 */
void printsf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  while (*format) {
    if (*format == '%') {
      format++; 
      switch (*format) {
        case 'd': // Int
          printf("%d", va_arg(args, int));
          break;
        case 'f': // Float
          printf("%f", va_arg(args, double));
          break;
        case 'c': // Char
          putchar(va_arg(args, int)); // Char é promovido a int
          break;
        case 's': // String (char*)
          printf("%s", va_arg(args, char*));
          break;
        case 'S': { // String (tipo personalizado)
          String S = va_arg(args, String);
          printf("%s", S.data);
          break;
        }
        case 'L': { // List (tipo personalizado)
          List L = va_arg(args, List);
          showList(L);
          break;
        }
        case 'Q': { // Queue (tipo personalizado)
          Queue Q = va_arg(args, Queue);
          showQueue(Q);
          break;
        }
        default:
          putchar('%');
          putchar(*format);
          break;
      }
    } else putchar(*format);
    format++;
  }
  va_end(args);
}

/**
 * Simula o snprintsf usando o tipo string.
 *
 * Essa função formata uma string com base em um modelo especificado e
 * armazena o resultado em uma string de destino. É útil para
 * manipulações de strings onde a formatação é necessária.
 *
 * @param dest Ponteiro para a string de destino.
 * @param format Formato da string.
 */
void snprintsf(String *dest, const char *format, ...) {
  va_list args;
  va_start(args, format);
  va_list args_copy;
  va_copy(args_copy, args);
  int size = vsnprintf(NULL, 0, format, args_copy) + 1;
  va_end(args_copy);
  if (size > dest->size) {
    char *new_data = verAlloc(realloc(dest->data, size));
    dest->data = new_data;
    dest->size = size;
  }
  vsnprintf(dest->data, dest->size, format, args);
  va_end(args);
}

/**
 * Garante que o nome do arquivo é único e válido.
 *
 * Essa função analisa um nome de arquivo fornecido e gera um nome único
 * para evitar conflitos em operações de entrada/saída. Isso é útil em
 * situações onde arquivos podem ter nomes duplicados.
 *
 * @param nome_a Nome do arquivo original.
 * @return Nome único e válido do arquivo.
 */
char *FileName(const char *nome_a) {
  char nome_b[256], EXT[10] = ".txt", *ext = strrchr(nome_a, '.');
  int cont_a = 0;
  if (ext != NULL) { // Verifica se o arquivo possui extensão
    strncpy(nome_b, nome_a, ext - nome_a);
    nome_b[ext - nome_a] = '\0';
    snprintf(EXT, sizeof(EXT), "%s", ext);
  } else strcpy(nome_b, nome_a);
  char *nome_f = verAlloc(malloc(strlen(nome_b) + strlen(EXT) + 10));
  do {
    snprintf(nome_f, strlen(nome_b) + strlen(EXT) + 10, cont_a == 0 ? "%s%s" : "%s(%d)%s", nome_b, cont_a++, EXT);
  } while (access(nome_f, F_OK) == 0);
  return nome_f;
}

/**
 * Exibe o conteúdo de um arquivo.
 *
 * Essa função abre um arquivo especificado e exibe seu conteúdo na
 * saída padrão. Ela também pode aplicar formatação de cor ao conteúdo
 * exibido, conforme especificado. É uma ferramenta útil para depuração
 * ou visualização de dados.
 *
 * @param nome_a Nome do arquivo a ser exibido.
 * @param cor Cor a ser utilizada na exibição.
 * @return 1 se o arquivo foi exibido com sucesso, 0 caso contrário.
 */
int FilePrint(const char *nome_a, const char *cor) {
  FILE *arquivo = fopen(nome_a, "r");
  if (arquivo == NULL) { // Verifica se o arquivo foi aberto com sucesso
    printf(C_FMT_ERROR("\n[Arquivo '%s' não encontrado!]: %s%s\n"), nome_a, strerror(errno), C_RESET);
    return 0;
  }
  char *linha = NULL;
  size_t tam = 0;
  printf("%s", cor);
  while (getline(&linha, &tam, arquivo) != -1) { // Lê todas as linhas do arquivo
    printf("%s", linha);
  }
  printf("%s", C_RESET);
  free(linha);
  fclose(arquivo);
  return 1; 
} 

/**
 * @brief Estrutura do nó da lista.
 * 
 * Cada nó contém um valor `info` e um ponteiro para o próximo e e anterior nó da lista.
 */
typedef struct nodeL {
  int info;
  struct nodeL *prox;
  struct nodeL *ant;
} NodeL;

/**
 * @brief Estrutura da lista (List).
 * 
 * A lista contém um ponteiro para o início (`inicio`), o fim (`fim`), 
 * e um contador de elementos (`N`).
 */
typedef struct list { 
  NodeL *head;
  NodeL *tail;
  size_t N;
} *List;

/**
 * @brief Cria uma nova lista encadeada.
 * @return Um ponteiro para a nova lista criada.
 */
List newList() {
  List Ptd = verAlloc((List)malloc(sizeof(struct list)));
  Ptd->head = NULL;
  Ptd->tail = NULL;
  Ptd->N = 0;
  return Ptd;
}

/**
 * @brief Destrói a lista encadeada e libera a memória alocada.
 * @param list Ponteiro para a lista a ser destruída.
 * @return NULL após a liberação da lista.
 */
List destroyList(List Ptd) {
  if (Ptd == NULL) return NULL;
  NodeL *aux = Ptd->head;
  while (aux!= NULL) {
    NodeL *temp = aux;
    aux = aux->prox;
    free(temp);
  }
  free(Ptd);
  return NULL;
}

/**
 * @brief Verifica se a lista está vazia.
 * @param Ptd Ponteiro para a lista a ser verificada.
 * @return 1 se a lista estiver vazia, caso contrário, 0.
 */
int isEmptyList(List Ptd) {
  if (Ptd == NULL || Ptd->head == NULL) return 1;
  return 0;
}

/**
 * @brief Retorna o tamanho da lista.
 * @param Ptd Ponteiro para a lista.
 * @return O número de elementos na lista.
 */
size_t sizeList(List Ptd) { 
  if (Ptd == NULL) return 0;  
  return Ptd->N;
}

/**
 * @brief Insere um novo elemento no início da lista.
 * @param Ptd Ponteiro para a lista.
 * @param info O valor a ser inserido.
 * @return Ponteiro para a lista após a inserção.
 */
List insertAtBegin(List Ptd, const int info) {
  NodeL *novo = (NodeL *)malloc(sizeof(NodeL)); 
  if (novo == NULL) return Ptd; 
  novo->info = info;
  novo->prox = Ptd->head;
  novo->ant = NULL;
  if (Ptd->head != NULL) Ptd->head->ant = novo; 
  Ptd->head = novo;
  if (Ptd->tail == NULL) Ptd->tail = novo; 
  Ptd->N++;
  return Ptd;
}

/**
 * @brief Insere um novo elemento no final da lista.
 * @param Ptd Ponteiro para a lista.
 * @param info O valor a ser inserido.
 * @return Ponteiro para a lista após a inserção.
 */
List insertAtEnd(List Ptd, const int info) {
  NodeL *novo = (NodeL *)malloc(sizeof(NodeL));
  if (novo == NULL) return Ptd;
  novo->info = info;
  novo->prox = NULL;
  novo->ant = Ptd->tail;
  if (Ptd->tail != NULL) Ptd->tail->prox = novo;
  Ptd->tail = novo;
  if (Ptd->head == NULL) Ptd->head = novo;
  Ptd->N++;
  return Ptd;
}

/**
 * @brief Remove um elemento da lista na posição especificada.
 * @param Ptd Ponteiro para a lista.
 * @param pos Posição do elemento a ser removido.
 * @return Ponteiro para a lista após a remoção.
 */
List removeAt(List Ptd, const int pos) {
  if (Ptd == NULL || Ptd->head == NULL || pos < 0 || pos >= Ptd->N) return Ptd;
  NodeL *atual = Ptd->head;
  if (pos == 0) {
    Ptd->head = atual->prox;
    if (Ptd->head != NULL) Ptd->head->ant = NULL;
    else Ptd->tail = NULL;
    free(atual);
  } else {
    NodeL *anterior = atual;
    for (int i = 0; i < pos; i++) {
      anterior = anterior->prox;
    }
    NodeL *proximo = anterior->prox;
    anterior->prox = proximo->prox;
    if (proximo->prox != NULL) proximo->prox->ant = anterior;
    else Ptd->tail = anterior;
    free(proximo);
  }
  Ptd->N--;
  return Ptd; 
}

/**
 * @brief Busca um elemento na lista na posição especificada.
 * @param Ptd Ponteiro para a lista.
 * @param pos Posição do elemento a ser buscado.
 * @param info Ponteiro onde o valor encontrado será armazenado.
 * @return 0 se encontrado, -1 se não encontrado.
 */
int searchAt(List Ptd, const int pos, int *info) {
  if (Ptd == NULL || Ptd->head == NULL || pos < 0 || pos >= Ptd->N) return -1;
  NodeL *atual = Ptd->head;
  for (int i = 0; i < pos; i++) {
    atual = atual->prox;
  }
  *info = atual->info;
  return 0;
}

/**
 * @brief Exibe todos os elementos da lista.
 * @param Ptd Ponteiro para a lista.
 * @return 1 se a lista foi exibida com sucesso, 0 se estiver vazia.
 */
int showList(List Ptd) {
  if (Ptd == NULL || Ptd->head == NULL) return 0;
  int cont = 0;
  NodeL *atual = Ptd->head;
  while (atual != NULL) { 
    printf("%d ", atual->info);
    atual = atual->prox;
  }
  return 1;
} 

/**
 * @brief Estrutura do nó da fila.
 * 
 * Cada nó contém um valor `info` e um ponteiro para o próximo nó da fila.
 */
typedef struct nodeQ { 
  int info;
  struct nodeQ *prox;
} NodeQ;

/**
 * @brief Estrutura da fila (Queue).
 * 
 * A fila contém um ponteiro para o início (`inicio`), o fim (`fim`), 
 * e um contador de elementos (`N`).
 */
typedef struct queue { 
  NodeQ *head;
  NodeQ *tail;
  int N;
} *Queue;

/**
 * @brief Cria uma nova fila vazia.
 * 
 * Aloca memória para uma nova fila, inicializando os ponteiros de início e fim como `NULL`
 * e o contador de elementos como zero.
 * 
 * @return Queue Um ponteiro para a nova fila criada.
 */
Queue newQueue() {
  Queue Ptq = (Queue)malloc(sizeof(struct queue));
  if (Ptq != NULL) {
    Ptq->head = NULL;
    Ptq->tail = NULL;
    Ptq->N = 0;
  }
  return Ptq;
}

/**
 * @brief Destrói a fila e libera a memória associada.
 * 
 * Remove todos os nós da fila e libera a memória alocada para a estrutura da fila.
 * 
 * @param Ptq Um ponteiro para a fila a ser destruída.
 * @return Queue Retorna `NULL` após liberar a memória.
 */
Queue destroyQueue(Queue Ptq) {
  if (Ptq == NULL) return Ptq;
  NodeQ *temp = Ptq->head;
  while (temp != NULL) {
    NodeQ *proximo = temp->prox;
    free(temp);
    temp = proximo;
  }
  free(Ptq);
  return NULL; 
}

/**
 * @brief Verifica se a fila está vazia.
 * 
 * @param Ptq Um ponteiro para a fila a ser verificada.
 * @return int Retorna 1 se a fila estiver vazia, ou 0 caso contrário.
 */
int isEmptyQueue(Queue Ptq) {
  return (Ptq == NULL || Ptq->head == NULL);
}

/**
 * @brief Insere um novo elemento na fila.
 * 
 * Aloca um novo nó contendo o valor passado e o insere no fim da fila.
 * 
 * @param Ptq Um ponteiro para a fila onde o elemento será inserido.
 * @param info O valor a ser inserido na fila.
 * @return Queue Retorna a fila após a inserção do novo elemento.
 */
Queue enqueue(Queue Ptq, int info) {
  if (Ptq == NULL) return Ptq;
  NodeQ *novo = (NodeQ*) malloc(sizeof(NodeQ));
  if (novo == NULL) return Ptq; 
  novo->info = info;
  novo->prox = NULL;
  if (isEmptyQueue(Ptq)) Ptq->head = novo; 
  else Ptq->tail->prox = novo; 
  Ptq->tail = novo;
  Ptq->N++;
  return Ptq;
} 

/**
 * @brief Remove o primeiro elemento da fila.
 * 
 * Remove o nó que está no início da fila e retorna o valor removido através de um ponteiro.
 * 
 * @param Ptq Um ponteiro para a fila de onde o elemento será removido.
 * @param info Um ponteiro para onde o valor removido será armazenado.
 * @return Queue Retorna a fila após a remoção.
 */
Queue dequeue(Queue Ptq, int *info) {
  if (Ptq == NULL || isEmptyQueue(Ptq)) return Ptq;
  NodeQ *temp = Ptq->head;
  *info = temp->info;
  Ptq->head = temp->prox;
  if (Ptq->head == NULL) Ptq->tail = NULL;
  free(temp);
  Ptq->N--;
  return Ptq;
}

/**
 * @brief Obtém o valor do primeiro elemento da fila sem removê-lo.
 * 
 * Armazena o valor do primeiro nó da fila no ponteiro `info` passado por parâmetro.
 * 
 * @param Ptq Um ponteiro para a fila.
 * @param info Um ponteiro onde o valor será armazenado.
 * @return int Retorna 1 se o valor foi obtido com sucesso, ou 0 se a fila estiver vazia.
 */
int peek(Queue Ptq, int *info) {
  if (Ptq == NULL || isEmptyQueue(Ptq)) return 0;
  *info = Ptq->head->info;
  return 1;
}

/**
 * @brief Exibe os elementos da fila.
 * 
 * Percorre todos os nós da fila e imprime os valores armazenados.
 * 
 * @param Ptq Um ponteiro para a fila a ser exibida.
 * @return int Retorna 1 se a fila foi exibida com sucesso, ou 0 se a fila estiver vazia.
 */
int showQueue(Queue Ptq) {
  if (isEmptyQueue(Ptq)) return 0;
  NodeQ *temp = Ptq->head;
  while (temp != NULL) {
    printf("%d ", temp->info);
    temp = temp->prox;
  }
  return 1;
}

/**
 * @brief Retorna o número de elementos na fila.
 * 
 * @param Ptq Um ponteiro para a fila.
 * @return size_t O número de elementos na fila.
 */
size_t sizeQueue(Queue Ptq) {
  if (Ptq == NULL) return 0;
  return Ptq->N;
}