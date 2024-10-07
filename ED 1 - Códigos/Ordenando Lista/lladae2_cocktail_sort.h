#ifndef LLADAE2_COCKTAIL_SORT_H
#define LLADAE2_COCKTAIL_SORT_H

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

/* Insere todos os nºs de um arquivo em uma lista */
Lista *arquivoCarrega(Lista *Ptd, const char *nome_arqv, int qtd); 
 
/* Gera nºs aleatórios e armazena em um arquivo */
int arquivoAleatoriza(const char *nome_arqv, const int min, const int max, const int qtd);

/* Salva os dados da lista em um arquivo */
int arquivoSalva(Lista *Ptd, const char *nome_arqv);

/* Exclui todas as ocorrências de um arquivo */
int arquivoExclui(const char *nome_arqv);

/* Pede o nome de um arquivo ao usuário */
char *arquivoNome(const char *msg);
 
/* Mostra todo o conteúdo de um arquivo na tela */
int printArquivo(const char *nome, const char *cor);

#endif  