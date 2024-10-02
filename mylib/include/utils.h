#ifndef UTILS_H
#define UTILS_H

/** 
 * Simula o printf e aceita novos tipos.
 * 
 * @param format A string de formato.
 * @param ... Os argumentos a serem formatados.
 */
void printsf(const char *format, ...); 

/** 
 * Limpa o buffer do teclado.
 */
void cleanBuffer(); 

/** 
 * Limpa a tela do terminal.
 */
void cleanScreen();

/** 
 * Espera uma entrada do usuário antes de limpar a tela do terminal.
 * 
 * @param msg Mensagem a ser exibida ao usuário.
 */
void waitCleanScreen(const char *msg);

/** 
 * Escolhe um número inteiro dentro de um intervalo.
 * 
 * @param msg Mensagem a ser exibida ao usuário.
 * @param min O valor mínimo do intervalo.
 * @param max O valor máximo do intervalo.
 * @return Um número inteiro escolhido pelo usuário.
 */
int choose(const char *msg, const int min, const int max);

/** 
 * Confirma uma ação.
 * 
 * @param msg Mensagem a ser exibida ao usuário.
 * @return 1 se a confirmação for positiva, 0 caso contrário.
 */
int confirm(const char *msg); 

/** 
 * Garante que o nome do arquivo é único e válido.
 * 
 * @param nome_a O nome base do arquivo.
 * @return Um ponteiro para uma string com o nome do arquivo único.
 */
char *FileName(const char *nome_a);

/** 
 * Exibe o conteúdo de um arquivo.
 * 
 * @param nome O nome do arquivo a ser exibido.
 * @param cor A cor a ser utilizada na exibição.
 * @return 1 se a impressão for bem-sucedida, 0 caso contrário.
 */
int FilePrint(const char *nome, const char *cor);

/** 
 * Analisa se a alocação foi bem-sucedida.
 * 
 * @param pt O ponteiro a ser analisado.
 * @return O ponteiro analisado.
 */
void *verAlloc(void *pt);

#endif