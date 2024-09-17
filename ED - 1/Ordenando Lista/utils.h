#ifndef UTILS_H
#define UTILS_H

/* Limpa o buffer do teclado */
void limpaBuffer(); 

/* Limpa a tela */
void cls();

/* Espera uma entrada do usuário p/ limpar a tela */
void limpaTela(const char *msg);

/* Faz uma operação de potência */ 
double potencia(double a, int b);

/* Confirma uma ação */
int simOuNao(const char *msg);

/* Pede um nº dentro de um intervalo ao usuário */
int intervalo(const char *msg, int min, int max);

#endif