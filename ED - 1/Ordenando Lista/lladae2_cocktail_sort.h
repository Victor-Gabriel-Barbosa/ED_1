#ifndef LLADAE2_COCKTAIL_SORT_H
#define LLADAE2_COCKTAIL_SORT_H

#include <stddef.h>

/* Variáveis que armazenam cores de texto */
extern const char *C_RSET;
extern const char *C_AZUL;
extern const char *C_VERD;
extern const char *C_CIAN; 
extern const char *C_VERM; 
extern const char *C_MAGE;
extern const char *C_AMAR;

typedef struct lista Lista;

/* Cria uma nova lista vazia */ 
Lista *listaCria();

/* Tamanho da lista */
int listaSize(Lista *Ptd);

/* Insere um novo elemento no início da lista */
Lista *listaInsereInicio(Lista *Ptd, const int dado);

/* Insere um novo elemento no fim da lista */
Lista *listaInsereFim(Lista *Ptd, const int dado);

/* Remove um elemento da lista */
Lista *listaRemove(Lista *Ptd, const int dado);

/* Libera toda a memória alocada p/ a lista */
Lista *listaLibera(Lista *Ptd); 

/* Imprime a lista */
int listaImprime(Lista *Ptd); 

/* Ordena a lista usando o algoritmo Cocktail Sort */
Lista *listaCocktailSort(Lista *Ptd);

/* Mescla duas listas */
Lista *listaMescla(Lista *list1, Lista *list2);

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

/* Insere todos os nºs de um arquivo em uma lista */
Lista *arquivoCarrega(Lista *Ptd, const char *nome_arqv, int qtd); 
 
/* Gera nºs aleatórios e armazena em um arquivo */
int arquivoAleatoriza(const char *nome_arqv, const int min, const int max, const int qtd);

/* Salva os dados da lista em um arquivo */
int arquivoSalva(Lista *Ptd, const char *nome_arqv);

/* Exclui todas as ocorrências de um arquivo */
int arquivoExclui(const char *nome_arqv);
 
/* Pede um nº dentro de um intervalo ao usuário */
int intervalo(const char *msg, int min, int max);

/* Pede o nome de um arquivo ao usuário */
char *arquivoNome(const char *msg);

/* Mostra todo o conteúdo de um arquivo na tela */
int printArquivo(const char *nome, const char *cor);

#endif  