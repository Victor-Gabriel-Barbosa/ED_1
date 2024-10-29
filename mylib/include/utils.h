/**
 * @file utils.h
 * @brief Conjunto de utilitários gerais para facilitar operações comuns.
 *
 * Este arquivo contém funções e macros úteis para operações variadas como manipulação de strings,
 * interação com o usuário, operações de terminal e validações.
 * 
 * As funções incluem impressão formatada, captura de entrada do usuário, manipulação de arquivos, 
 * e operações auxiliares como limpar o buffer de entrada e validar alocações de memória.
 * 
 * Macros:
 * - 'sizeArray': Calcula o número de elementos em um array.
 * - 'randInt': Seleciona aleatoriamente um elemento do array dado.
 * - 'timeInt':  Mede o tempo de execução de uma função ou bloco de código.
 * - 'foreach': Permite a iteração sobre arrays de tamanho conhecido em tempo de compilação.
 * - 'print': Conta automaticamente o número de argumentos e chama a função printArgs para exibir.
 *
 * Funções principais:
 * - 'printsf': Imprime uma string formatada com suporte a novos tipos de dados.
 * - 'input': Exibe uma mensagem formatada e captura a entrada do usuário.
 * - 'cleanBuffer': Limpa o buffer do teclado.
 * - 'cleanScreen': Limpa a tela do terminal.
 * - 'waitCleanScreen': Exibe uma mensagem e espera antes de limpar a tela.
 * - 'chooseInt': Solicita ao usuário um número dentro de um intervalo.
 * - 'confirm': Solicita a confirmação de uma ação.
 * - 'fileExists': Verifica se um arquivo existe no sistema.
 * - 'fileSize': Obtém o tamanho do arquivo em bytes.
 * - 'fileName': Garante que o nome do arquivo é único e válido.
 * - 'fileDelete': Deleta o arquivo especificado pelo nome.
 * - 'filePrint': Exibe o conteúdo de um arquivo com uma cor especificada.
 * - 'fileRename': Renomeia um arquivo.
 * - 'fileAppend': Adiciona texto ao final de um arquivo.
 * - 'fileCompare': Compara dois arquivos para verificar se são idênticos.
 * 
 * 
 * @note Funções que interagem com o terminal podem ser dependentes da plataforma.
 * 
 * @warning Algumas funções requerem o uso correto de ponteiros e strings. 
 * Certifique-se de passar os parâmetros corretamente para evitar falhas.
 * 
 * @version 2.0
 * @date 12/10/2024
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <time.h>
#include <setjmp.h>
#include "stringlib.h"

jmp_buf jump_buffer;

/**
 * @brief Inicia um bloco de código onde exceções podem ser capturadas.
 *
 * Este macro define um ponto de salvamento para o estado do programa usando 'setjmp'.
 * Se uma exceção for lançada usando 'throw', o controle será transferido para o bloco
 * 'catch' associado. Caso contrário, o código dentro do bloco 'try' é executado normalmente.
 *
 * @note Este macro deve ser seguido por um bloco 'catch' para capturar exceções.
 */
#define try if (setjmp(jump_buffer) == 0)

/**
 * @brief Captura exceções lançadas dentro de um bloco 'try'.
 *
 * O código dentro deste bloco será executado apenas se uma exceção for lançada no
 * bloco 'try' associado. Isso ocorre quando 'throw' é chamado, pulando o restante do
 * código no bloco 'try' e transferindo o controle para o bloco 'catch'.
 */
#define catch else

/**
 * @brief Lança uma exceção dentro de um bloco 'try'.
 *
 * Este macro usa 'longjmp' para transferir o controle de volta para o ponto definido
 * pelo 'try', interrompendo o fluxo normal do programa e ativando o bloco 'catch'.
 *
 * @note 'throw' só deve ser chamado dentro de um bloco 'try', pois depende do estado
 * salvo por 'setjmp'.
 */
#define throw longjmp(jump_buffer, 1)

/**
 * @brief Calcula o número de elementos em um array.
 * 
 * @param arr O array do qual calcular o tamanho.
 * @return O número de elementos no array.
 */
#define sizeArray(arr) (sizeof(arr) / sizeof((arr)[0]))

/**
 * @brief Seleciona aleatoriamente um elemento do array dado.
 * 
 * @param arr O array do qual selecionar um elemento.
 * @return Um elemento selecionado aleatoriamente do array.
 */
#define randInt(arr) (arr[rand() % sizeArray(arr)])

/**
 * @brief Mede o tempo de execução de uma função ou bloco de código.
 *
 * Executa o código fornecido e exibe o tempo gasto em segundos.
 * Usa 'clock()' da biblioteca '<time.h>' para medir o tempo em ciclos
 * de clock e converte para segundos com 'CLOCKS_PER_SEC'.
 *
 * @param func Função ou bloco de código a ser medido.
 */
#define timer(func)                                                 \
  ({                                                                \
    clock_t start, end;                                             \
    start = clock();                                                \
    if (start == (clock_t)-1) {                                     \
      perror("Erro ao iniciar o temporizador");                     \
      return;                                                       \
    }                                                               \
    func;                                                           \
    end = clock();                                                  \
    if (end == (clock_t)-1) {                                       \
      perror("Erro ao parar o temporizador");                       \
      return;                                                       \
    }                                                               \
    double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC; \
    printf("Tempo de execução: %g segundos\n", elapsed_time);       \
    elapsed_time;                                                   \
  })

/**
 * @def foreach(item, array)
 * @brief Itera sobre cada elemento de um array estático.
 *
 * @param item Ponteiro que armazena o elemento atual do array.
 * @param array O array a ser iterado.
 *
 * @warning Funciona apenas para arrays de tamanho conhecido em tempo de compilação.
 */
#define foreach(item, array) \
  for (typeof((array)[0]) *ptr = (array), *item = ptr; \
    item < ptr + (sizeof(array) / sizeof((array)[0])); \
    item++)

/**
 * @brief Imprime um número variável de strings.
 *
 * Esta função aceita um número variável de argumentos do tipo string e os imprime
 * um por um. Se algum argumento for nulo, imprime "NULL".
 *
 * @param count O número de argumentos passados para a função.
 * @param ... Os argumentos do tipo string que devem ser impressos.
 */
int printArgs(int count, ...);

/**
 * @brief Imprime um número variável de strings.
 *
 * Esta macro facilita a impressão de múltiplas strings, calculando automaticamente
 * o número de argumentos passados e chamando a função 'printArgs'.
 *
 * @param ... As strings que devem ser impressas.
 */
#define print(...) printArgs(sizeof((string[]){__VA_ARGS__}) / sizeof(string), __VA_ARGS__)

/** 
 * @brief Imprime uma string formatada com suporte a novos tipos de dado.
 * 
 * @param format A string de formato.
 * @param ... Os argumentos a serem formatados.
 */
void printfs(const char* format, ...); 

/**
 * @brief Exibe uma mensagem formatada e obtém a entrada do usuário.
 *
 * @brief A função imprime uma mensagem formatada e retorna a entrada como uma 'string'.
 *
 * @param format string de formato para a mensagem.
 * @param ... Argumentos para a formatação da mensagem.
 * @return string contendo a entrada do usuário.
 */
string input(const char* format, ...);

/** 
 * @brief Limpa o buffer do teclado.
 */
void cleanBuffer(); 

/** 
 * @brief Limpa a tela do terminal.
 */
void cleanScreen();

/** 
 * @brief Espera uma entrada do usuário antes de limpar a tela do terminal.
 * @param msg Mensagem a ser exibida ao usuário.
 */
void waitCleanScreen(const char* msg);

/** 
 * @brief Escolhe um número inteiro dentro de um intervalo.
 * 
 * @param msg Mensagem a ser exibida ao usuário.
 * @param min O valor mínimo do intervalo.
 * @param max O valor máximo do intervalo.
 * @return O número escolhido pelo usuário.
 */
int64_t chooseInt(const char* msg, const int64_t min, const int64_t max);

/**
 * @brief Solicita confirmação do usuário com mensagem formatada.
 *
 * @param msg Mensagem formatada (como em printf) para exibir ao usuário.
 * @param ... Argumentos variáveis para formatar a mensagem.
 *
 * @return 1 se o usuário confirmar (responder 'S'), ou 0 se o usuário
 * negar (responder 'N').
 */
int confirm(const char* msg, ...); 

/**
 * @brief Verifica se um arquivo existe no sistema.
 *
 * @param fileName Nome do arquivo a ser verificado.
 * @return 1 se o arquivo existe, caso contrário 0.
 */
int fileExists(const char* fileName);

/**
 * @brief Obtém o tamanho do arquivo em bytes.
 *
 * @param fileName Nome do arquivo.
 * @return O tamanho do arquivo em bytes, ou -1 se houver erro.
 */
long fileSize(const char* fileName);

/** 
 * @brief Garante que o nome do arquivo é único e válido.
 * 
 * @param fileName O nome base do arquivo.
 * @return Um ponteiro para uma string com o nome do arquivo único.
 */
char* fileName(const char* fileName);

/**
 * @brief Deleta o arquivo especificado pelo nome.
 *
 * @param fileName Nome do arquivo a ser deletado.
 * @return 1 se o arquivo foi deletado com sucesso, ou 0 se houve erro.
 */
int fileDelete(const char* fileName);
 
/** 
 * @brief Exibe o conteúdo de um arquivo.
 * 
 * @param nome O nome do arquivo a ser exibido.
 * @param cor A cor a ser utilizada na exibição.
 * @return 1 se a impressão for bem-sucedida, 0 caso contrário.
 */
int filePrint(const char* nome);

/**
 * @brief Renomeia um arquivo.
 *
 * @param oldName Nome atual do arquivo.
 * @param newName Novo nome para o arquivo.
 * @return 1 se o arquivo foi renomeado com sucesso, ou 0 se houve erro.
 */
int fileRename(const char* oldName, const char* newName);

/**
 * @brief Adiciona texto ao final de um arquivo.
 *
 * @param fileName Nome do arquivo.
 * @param text Texto a ser adicionado ao final do arquivo.
 * @return 1 se o texto foi adicionado com sucesso, ou 0 se houve erro.
 */
int fileAppend(const char* fileName, const char* text);

/**
 * @brief Compara dois arquivos para verificar se são idênticos.
 *
 * @param file1 Nome do primeiro arquivo.
 * @param file2 Nome do segundo arquivo.
 * @return 1 se os arquivos são idênticos, ou 0 caso contrário.
 */
int fileCompare(const char* file1, const char* file2);

#endif