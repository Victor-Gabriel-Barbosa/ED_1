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
int listaSize(Lista *Ptl);

/* Insere um novo elemento no início da lista */
Lista *listaInsereInicio(Lista *list, const int dado);

/* Insere um novo elemento no fim da lista */
Lista *listaInsereFim(Lista *list, const int dado);

/* Remove um elemento da lista */
Lista *listaRemove(Lista *list, const int dado);

/* Libera toda a memória alocada para a lista */
Lista *listaLibera(Lista *list); 

/* Imprime a lista */
int listaImprime(Lista *list); 

/* Ordena a lista usando o algoritmo Cocktail Sort */
Lista *listaCocktailSort(Lista *list);

/* Mescla duas listas */
Lista *listaMescla(Lista *list1, Lista *list2);

/* Limpa o buffer do teclado */
void limpaBuffer(); 

/* Limpa a tela do terminal */
void limpaTela(const char *msg);

/* Insere todos os números de um arquivo em uma lista */
Lista *arquivoCarrega(Lista *Ptl, const char *nome, int qtde);

/* Gera números aleatórios e armazena em um arquivo */
void geraNumerosAleatorios(const char *nome, const int qtde, const int min, const int max);

/* Faz uma operação de pontência */
double potencia(double a, double b);

#endif 
