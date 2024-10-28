#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include "cplus.h"

/**
 * @brief Captura exceções e exibe uma mensagem de erro.
 *
 * Essa função verifica o valor de errno para determinar o tipo de erro
 * ocorrido e exibe uma mensagem formatada no stderr, encerrando o programa
 * com um código de falha. É útil para tratar erros de alocação de memória
 * ou de operações de arquivo.
 */
void catchError() { 
  fprintf(stderr, fError("\nErro: %s\n"), strerror(errno));
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
void waitCleanScreen(const char* msg) {
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
int64_t chooseInt(const char* msg, const int64_t min, const int64_t max) {
  int64_t num = min - 1;
  int aux = 1;
  while (aux) {
    printf("%s [%lld-%lld]: ", msg, min, max);
    scanf("%lld", &num);
    cleanBuffer();
    if (num >= min && num <= max) aux = 0;
    else printf("Número inválido...\n");
  }
  return num;
}

/**
 * @brief Solicita confirmação do usuário com mensagem formatada.
 *
 * A função exibe uma mensagem formatada para o usuário e solicita
 * que ele responda com 'S' (sim) ou 'N' (não). Ela continua perguntando
 * até que uma resposta válida seja fornecida.
 *
 * @param msg Mensagem formatada (como em printf) para exibir ao usuário.
 * @param ... Argumentos variáveis para formatar a mensagem.
 *
 * @return 1 se o usuário confirmar (responder 'S'), ou 0 se o usuário
 * negar (responder 'N').
 */
int confirm(const char* msg, ...) {
  char op;
  int aux = 1;
  va_list args; 
  while (aux) {
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);
    printf(" [S/N]? ");
    op = tolower(getchar());
    cleanBuffer(); 
    if (op == 's' || op == 'n') aux = 0;
    else printf("Opção inválida...\n");
  }
  return (op == 's');
}

/**
 * @brief Imprime um número variável de strings.
 *
 * Esta função aceita um número variável de argumentos do tipo string e os imprime
 * um por um. Se algum argumento for nulo, imprime "NULL".
 *
 * @param count O número de argumentos passados para a função.
 * @param ... Os argumentos do tipo string que devem ser impressos.
 */
int printArgs(int count, ...) {
  va_list args;
  int allPrinted = 1;
  va_start(args, count); 
  for (int i = 0; i < count; i++) { 
    string str = va_arg(args, string);
    if (str == NULL) { 
      allPrinted = 0;
      continue;
    }
    stringPrint(str);
  }
  va_end(args);
  return allPrinted;
}

/**
 * @brief Imprime strings formatadas com suporte a tipos personalizados.
 *
 * A função exibe uma string formatada como 'printf', com suporte adicional
 * para tipos personalizados (string, lista, fila, pilha, árvore e objeto).
 *
 * @param format String de formatação.
 * @param ...    Lista de argumentos de diversos tipos.
 */
void printfs(const char *format, ...) {
  va_list args;
  va_start(args, format);
  while (*format) {
    if (*format == '%') {
      format++;
      int long_flag = 0;
      if (*format == 'l') {
        long_flag = 1;
        format++;
        if (*format == 'l') {
          long_flag = 2;
          format++;
        }
      }
      else if (*format == 'L') {
        long_flag = 3;
        format++;
      }
      switch (*format) {
        case 'd':
          if (long_flag == 1) printf("%ld", va_arg(args, long int));
          else if (long_flag == 2) printf("%lld", va_arg(args, long long int));
          else printf("%d", va_arg(args, int));
          break;
        case 'u':
          if (long_flag == 1) printf("%lu", va_arg(args, unsigned long int));
          else if (long_flag == 2) printf("%llu", va_arg(args, unsigned long long int));
          else printf("%u", va_arg(args, unsigned int));
          break;
        case 'f':
          if (long_flag == 3) printf("%Lf", va_arg(args, long double));
          else printf("%f", va_arg(args, double));
          break;
        case 'e':
          if (long_flag == 3) printf("%Le", va_arg(args, long double));
          else printf("%e", va_arg(args, double));
          break;
        case 'g':
          if (long_flag == 3) printf("%Lg", va_arg(args, long double));
          else printf("%g", va_arg(args, double));
          break;
        case 'o':
          printf("%o", va_arg(args, unsigned int));
          break;
        case 'x':
          printf("%x", va_arg(args, unsigned int));
          break;
        case 'X':
          printf("%X", va_arg(args, unsigned int));
          break;
        case 'c':
          putchar(va_arg(args, int));
          break;
        case 's':
          printf("%s", va_arg(args, char *));
          break;
        case 'S': 
          stringPrint(va_arg(args, string));
          break;
        case 'G': 
          listPrint(va_arg(args, list));
          break;
        case 'F': 
          queuePrint(va_arg(args, queue));
          break;
        case 'P': 
          stackPrint(va_arg(args, stack));
          break;
        case 'A': 
          treePrint(va_arg(args, tree));
          break;
        case 'O': 
          objPrint(va_arg(args, obj));
          break;
        default:
          putchar('%');
          putchar(*format);
      }
    }
    else putchar(*format);
    format++;
  }
  va_end(args);
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
string input(const char* format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  return stringInput();
}

/**
 * @brief Verifica se um arquivo existe no sistema.
 *
 * @param fileName Nome do arquivo a ser verificado.
 * @return 1 se o arquivo existe, caso contrário 0.
 */
int fileExists(const char* fileName) {
  return (access(fileName, F_OK) == 0);
}

/**
 * @brief Obtém o tamanho do arquivo em bytes.
 *
 * @param fileName Nome do arquivo.
 * @return O tamanho do arquivo em bytes, ou -1 se houver erro.
 */
long fileSize(const char* fileName) {
  FILE* file = fopen(fileName, "r");
  if (file == NULL) {
    printf("Erro ao abrir arquivo: %s\n", fileName);
    return -1;
  }
  fseek(file, 0, SEEK_END);
  long size = ftell(file);  
  fclose(file);
  return size;
}

/**
 * @brief Garante que o nome do arquivo é único e válido.
 *
 * Essa função analisa um nome de arquivo fornecido e gera um nome único
 * para evitar conflitos em operações de entrada/saída. Isso é útil em
 * situações onde arquivos podem ter nomes duplicados.
 *
 * @param fileName Nome do arquivo original.
 * @return Nome único e válido do arquivo.
 */
char* fileName(const char* fileName) {
  int cont_a = 0;
  size_t fileName_len = strlen(fileName);
  char* nome_f;
  size_t tamanho = fileName_len + 10;  
  nome_f = malloc(tamanho);
  if (nome_f == NULL) return NULL;
  do {
    if (cont_a == 0) snprintf(nome_f, tamanho, "%s", fileName);  
    else {
      char* ext = strrchr(fileName, '.');  
      if (ext != NULL) snprintf(nome_f, tamanho, "%.*s(%d)%s", (int)(ext - fileName), fileName, cont_a, ext); 
      else snprintf(nome_f, tamanho, "%s(%d)", fileName, cont_a); 
    }
    cont_a++;
  } while (access(nome_f, F_OK) == 0);  
  return nome_f;
}

/**
 * @brief Deleta o arquivo especificado pelo nome.
 *
 * A função tenta deletar o arquivo cujo nome é passado como argumento.
 * Se o arquivo for deletado com sucesso, uma mensagem de confirmação
 * é exibida. Caso contrário, uma mensagem de erro descrevendo o motivo
 * da falha é exibida.
 *
 * @param fileName Nome do arquivo a ser deletado.
 * @return 1 se o arquivo foi deletado com sucesso, ou 0 se houve erro.
 */
int fileDelete(const char* fileName) {
  if (!confirm("Tem certeza que deseja excluir o arquivo '%s'", fileName)) {
    printf("Exclusão cancelada\n");
    return 0; 
  }
  if (remove(fileName) == 0) {
    printf("Arquivo '%s' deletado com sucesso\n", fileName);
    return 1;  
  } else {
    printf("Erro ao deletar o arquivo '%s': %s\n", fileName, strerror(errno));
    return 0;  
  }
}

/**
 * @brief Exibe o conteúdo de um arquivo. 
 *
 * Essa função abre um arquivo especificado e exibe seu conteúdo na
 * saída padrão. Ela também pode aplicar formatação de cor ao conteúdo
 * exibido, conforme especificado. É uma ferramenta útil para depuração
 * ou visualização de dados.
 *
 * @param fileName Nome do arquivo a ser exibido.
 * @param cor Cor a ser utilizada na exibição.
 * @return 1 se o arquivo foi exibido com sucesso, 0 caso contrário.
 */
int filePrint(const char* fileName) {
  FILE* arquivo = fopen(fileName, "r");
  if (arquivo == NULL) { 
    printf("Arquivo '%s' não encontrado: %s\n", fileName, strerror(errno));
    return 0;
  }
  char *linha = NULL;
  size_t tam = 0;
  while (getline(&linha, &tam, arquivo) != -1) printf("%s", linha);
  free(linha);
  fclose(arquivo);
  return 1; 
} 

/**
 * @brief Renomeia um arquivo.
 *
 * @param oldName Nome atual do arquivo.
 * @param newName Novo nome para o arquivo.
 * @return 1 se o arquivo foi renomeado com sucesso, ou 0 se houve erro.
 */
int fileRename(const char* oldName, const char* newName) {
  if (!confirm("Tem certeza que deseja renomear o arquivo '%s' para '%s'", oldName, newName)) {
    printf("Renomeação cancelada\n");
    return 0;
  }
  if (rename(oldName, newName) == 0) {
    printf("Arquivo renomeado de '%s' para '%s'.\n", oldName, newName);
    return 1;
  } else {
    printf("Erro ao renomear o arquivo '%s': %s\n", oldName, strerror(errno));
    return 0;
  }
}

/**
 * @brief Adiciona texto ao final de um arquivo.
 *
 * @param fileName Nome do arquivo.
 * @param text Texto a ser adicionado ao final do arquivo.
 * @return 1 se o texto foi adicionado com sucesso, ou 0 se houve erro.
 */
int fileAppend(const char* fileName, const char* text) {
  FILE *file = fopen(fileName, "a");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo '%s': %s\n", fileName, strerror(errno));
    return 0;
  }
  fprintf(file, "%s\n", text);
  fclose(file);
  return 1;
}

/**
 * @brief Compara dois arquivos para verificar se são idênticos.
 *
 * @param file1 Nome do primeiro arquivo.
 * @param file2 Nome do segundo arquivo.
 * @return 1 se os arquivos são idênticos, ou 0 caso contrário.
 */
int fileCompare(const char* file1, const char* file2) {
  FILE *f1 = fopen(file1, "r");
  FILE *f2 = fopen(file2, "r");
  if (f1 == NULL || f2 == NULL) {
    printf("Erro ao abrir arquivos para comparação\n");
    if (f1) fclose(f1);
    if (f2) fclose(f2);
    return 0;
  }
  int ch1, ch2;
  int identical = 1;
  while (((ch1 = fgetc(f1)) != EOF) && ((ch2 = fgetc(f2)) != EOF)) {
    if (ch1 != ch2) {
      identical = 0;
      break;
    }
  }
  if (fgetc(f1) != EOF || fgetc(f2) != EOF) identical = 0;
  fclose(f1);
  fclose(f2);
  return identical;
}