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
Lista *listaCocktailSortV1(Lista *list);

/* Ordena a lista usando o algoritmo Cocktail Sort */
Lista *listaCocktailSortV2(Lista *list);

/* Mescla duas listas */
Lista *listaMescla(Lista *list1, Lista *list2);

/* Limpa o buffer do teclado */
void limpaBuffer(); 

/* Limpa a tela do terminal */
void limpaTela(const char *msg);

#endif 
