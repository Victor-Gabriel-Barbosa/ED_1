#ifndef UTILS_H
#define UTILS_H

#include <time.h>

#define NUM_ELEMS(x) (sizeof(x) / sizeof((x)[0]))

/* Limpa o buffer do teclado */
void limpaBuffer(); 

/* Limpa a tela do terminal */
void cls();

/* Espera uma entrado do usuário antes de limpar a tela do terminal */
void limpaTela(const char *msg);

/* Escolhe um número inteiro dentro de um intervalo */
int escolheInt(const char *msg, const int min, const int max);

/* Confirma uma ação */
int simOuNao(const char *msg);

/* Exibe o conteúdo de um arquivo */
int printArquivo(const char *nome, const char *cor);

/* Salva o tempo de execução em um arquivo */
int arquivoSalva(const char *nome_arqv, const int num_bat, const int qtd, const clock_t *temp);

/* Exclui todas as ocorrências de um arquivo */
int arquivoExclui(const char *nome_arqv);

#endif