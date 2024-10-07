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

/* Garante que o nome do arquivo é único e válido */
char *arqvNome(const char *nome_a);

/* Exibe o conteúdo de um arquivo */
int arqvPrint(const char *nome, const char *cor);

/* Salva o tempo de execução em um arquivo */
int arqvSalvaTempo(const char *nome_a, const int qtd_t, const int qtd, const long int *temp);

/* Analisa se a alocação foi bem-sucedida */
void *verAlloc(void *pt);

/* Recria o print */
void print(const char *texto, ...);

#endif