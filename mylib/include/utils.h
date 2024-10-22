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
 * - `foreach`: Permite a iteração sobre arrays de tamanho conhecido em tempo de compilação.
 *
 * Funções principais:
 * - `printsf`: Imprime uma string formatada com suporte a novos tipos de dados.
 * - `input`: Exibe uma mensagem formatada e captura a entrada do usuário.
 * - `cleanBuffer`: Limpa o buffer do teclado.
 * - `cleanScreen`: Limpa a tela do terminal.
 * - `waitCleanScreen`: Exibe uma mensagem e espera antes de limpar a tela.
 * - `choose`: Solicita ao usuário um número dentro de um intervalo.
 * - `confirm`: Solicita a confirmação de uma ação.
 * - `fileName`: Gera um nome de arquivo único.
 * - `filePrint`: Exibe o conteúdo de um arquivo com uma cor especificada.
 * - `verAlloc`: Verifica se a alocação de memória foi bem-sucedida.
 * 
 * @note Funções que interagem com o terminal podem ser dependentes da plataforma.
 * 
 * @warning Algumas funções requerem o uso correto de ponteiros e strings. 
 * Certifique-se de passar os parâmetros corretamente para evitar falhas.
 * 
 * @version 1.0
 * @date 12/10/2024
 */
#ifndef UTILS_H
#define UTILS_H

#include <stringlib.h>

/**
 * @brief Calcula o número de elementos em um array.
 * 
 * @param arr O array do qual calcular o tamanho.
 * @return O número de elementos no array.
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/**
 * @brief Seleciona aleatoriamente um elemento do array dado.
 * 
 * @param arr O array do qual selecionar um elemento.
 * @return Um elemento selecionado aleatoriamente do array.
 */
#define RAND(arr) (arr[rand() % ARRAY_SIZE(arr)])

/**
 * @brief Macro para contar automaticamente o número de argumentos e chamar a função printMultiple.
 */
#define print(...) printMultiple(sizeof((obj[]){__VA_ARGS__}) / sizeof(obj), __VA_ARGS__)

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
 * @brief Simula o printf e aceita novos tipos.
 * 
 * @param format A string de formato.
 * @param ... Os argumentos a serem formatados.
 */
void printfs(const char *format, ...); 

/**
 * @brief Exibe o texto correspondente a múltiplos objetos `obj`.
 *
 * A função converte cada objeto `obj` para uma `string` e exibe seus textos.
 * Aceita múltiplos argumentos.
 *
 * @param count Número de objetos obj.
 * @param ... Lista de objetos obj.
 * @return int 1 se todos os textos foram exibidos corretamente, 0 caso algum falhar.
 */
int printMultiple(int count, ...);

/**
 * @brief Exibe uma mensagem formatada e obtém a entrada do usuário.
 *
 * @brief A função imprime uma mensagem formatada e retorna a entrada como uma `string`.
 *
 * @param format string de formato para a mensagem.
 * @param ... Argumentos para a formatação da mensagem.
 * @return string contendo a entrada do usuário.
 */
string input(const char *format, ...);

/** 
 * @brief Limpa o buffer do teclado.
 */
void cleanBuffer(); 

/** 
 * Limpa a tela do terminal.
 */
void cleanScreen();

/** 
 * @brief Espera uma entrada do usuário antes de limpar a tela do terminal.
 * 
 * @param msg Mensagem a ser exibida ao usuário.
 */
void waitCleanScreen(const char *msg);

/** 
 * @brief Escolhe um número inteiro dentro de um intervalo.
 * 
 * @param msg Mensagem a ser exibida ao usuário.
 * @param min O valor mínimo do intervalo.
 * @param max O valor máximo do intervalo.
 * @return Um número inteiro escolhido pelo usuário.
 */
int choose(const char *msg, const int min, const int max);

/** 
 * @brief Confirma uma ação.
 * 
 * @param msg Mensagem a ser exibida ao usuário.
 * @return 1 se a confirmação for positiva, 0 caso contrário.
 */
int confirm(const char *msg); 

/** 
 * @brief Garante que o nome do arquivo é único e válido.
 * 
 * @param nome_a O nome base do arquivo.
 * @return Um ponteiro para uma string com o nome do arquivo único.
 */
char *fileName(const char *nome_a);
 
/** 
 * @brief Exibe o conteúdo de um arquivo.
 * 
 * @param nome O nome do arquivo a ser exibido.
 * @param cor A cor a ser utilizada na exibição.
 * @return 1 se a impressão for bem-sucedida, 0 caso contrário.
 */
int filePrint(const char *nome, const char *cor);

/** 
 * @brief Analisa se a alocação foi bem-sucedida.
 * 
 * @param pt O ponteiro a ser analisado.
 * @return O ponteiro analisado.
 */
void *verAlloc(void *pt);

#endif