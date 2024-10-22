#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <cplus.h>

/**
 * @brief Captura exceções e exibe uma mensagem de erro.
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
 * @brief Limpa o buffer do teclado.
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
 * @brief Limpa a tela do terminal.
 *
 * Essa função executa um comando do sistema para limpar a tela do
 * terminal, proporcionando uma interface mais limpa para o usuário.
 * É útil para melhorar a legibilidade durante a interação com o
 * programa.
 */
void cleanScreen() {
  #ifdef _WIN32
    system("cls");
  #else 
    system("clear");
  #endif 
} 

/**
 * @brief Espera uma entrada do usuário antes de limpar a tela do terminal.
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
  cleanScreen();
}

/**
 * @brief Escolhe um número inteiro dentro de um intervalo.
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
 * @brief Confirma uma ação com o usuário.
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
 * @brief Analisa se a alocação foi bem-sucedida.
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
    exit(EXIT_FAILURE);
  }
  return pt;
}

/**
 * @brief Simula o printf e aceita novos tipos.
 *
 * Essa função permite a formatação e exibição de strings, com suporte
 * para tipos personalizados. Pode ser usada para gerar saídas formatadas
 * de maneira flexível.
 *
 * @param format Formato da string.
 */
void printfs(const char *format, ...) {
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
        case 's': // string (char*)
          printf("%s", va_arg(args, char*));
          break;
        case 'S': { // string (tipo personalizado)
          string S = va_arg(args, string);
          stringPrint(S); 
          break;
        }
        case 'L': { // list (tipo personalizado)
          list L = va_arg(args, list);
          listPrint(L);
          break;
        }
        case 'Q': { // queue (tipo personalizado)
          queue Q = va_arg(args, queue);
          queuePrint(Q);
          break;
        }
        case 'K': { // stack (tipo personalizado)
          stack K = va_arg(args, stack);
          stackPrint(K);
          break;
        }
        default: 
          putchar('%'); 
          putchar(*format);
      }
    } else putchar(*format);
    format++;
  }
  va_end(args);
}

/**
 * @brief Exibe o texto correspondente a múltiplos objetos 'obj'.
 *
 * A função converte cada objeto 'obj' para uma 'string' e exibe seus textos.
 * Aceita múltiplos argumentos.
 *
 * @param count Número de objetos obj.
 * @param ... Lista de objetos obj.
 * @return int 1 se todos os textos foram exibidos corretamente, 0 caso algum falhar.
 */
int printMultiple(int count, ...) {
  va_list args;
  int allPrinted = 1;
  va_start(args, count); // Inicializa a lista de argumentos variáveis
  for (int i = 0; i < count; i++) { // Converte cada objeto para string e exibe na tela
    obj a = va_arg(args, obj);
    if (a == NULL) { // Se o objeto for NULL, marca falha e continua
      allPrinted = 0;
      continue;
    }
    string str = toString(a); // Converte o objeto para string
    objDestroy(a); // Destrói o objeto original
    if (str == NULL) allPrinted = 0; // Verifica se a conversão foi bem-sucedida
    else { // Exibe a string e destrói após o uso
      stringPrint(str);
      stringDestroy(str);
    }
  }
  va_end(args); // Finaliza a lista de argumentos variáveis
  return allPrinted;
}

/**
 * @brief Exibe uma mensagem formatada e obtém a entrada do usuário.
 *
 * A função imprime uma mensagem formatada e retorna a entrada como uma 'string'.
 *
 * @param format string de formato para a mensagem.
 * @param ... Argumentos para a formatação da mensagem.
 * @return string contendo a entrada do usuário.
 */
string input(const char *format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  return stringInput();
}

/**
 * @brief Garante que o nome do arquivo é único e válido.
 *
 * Essa função analisa um nome de arquivo fornecido e gera um nome único
 * para evitar conflitos em operações de entrada/saída. Isso é útil em
 * situações onde arquivos podem ter nomes duplicados.
 *
 * @param nome_a Nome do arquivo original.
 * @return Nome único e válido do arquivo.
 */
char *fileName(const char *nome_a) {
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
 * @brief Exibe o conteúdo de um arquivo.
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
int filePrint(const char *nome_a, const char *cor) {
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