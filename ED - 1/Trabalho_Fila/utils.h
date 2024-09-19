#ifndef UTILS_H
#define UTILS_H

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

#endif