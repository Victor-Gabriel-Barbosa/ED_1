#ifndef FUNCOES_H
#define FUNCOES_H

#include <stddef.h>

/* Variáveis que armazenam cores de texto */
extern const char *C_RSET;
extern const char *C_AZUL;
extern const char *C_VERD;
extern const char *C_CIAN; 
extern const char *C_VERM;
extern const char *C_MAGE;
extern const char *C_AMAR;

typedef struct info {
  int id;
  char *nome;
  int idade;
  float salario;
} Info;

typedef struct lista Lista;

/* Cria uma nova lista vazia */ 
Lista *listaCria();

/* Tamanho da lista */
int listaSize(Lista *Ptd);

/* Insere um novo elemento no início da lista */
Lista *listaInsereInicio(Lista *Ptd, const Info inof);

/* Insere um novo elemento no fim da lista */
Lista *listaInsereFim(Lista *Ptd, const Info info);

/* Remove um elemento da lista */
Lista *listaRemove(Lista *Ptd, const Info info);

/* Libera toda a memória alocada para a lista */
Lista *listaLibera(Lista *Ptd); 

/* Imprime a lista */
int listaImprime(Lista *Ptd); 

/* Função principal do Tim Sort */
Lista* listaTimSort(Lista *Ptd);

/* Mescla duas listas */
Lista *listaMescla(Lista *list1, Lista *list2);

/* Limpa o buffer do teclado */
void limpaBuffer(); 

/* Limpa a tela */
void cls();

/* Espera uma entrada do usuário para limpar a tela */
void limpaTela(const char *msg);

/* Faz uma operação de potência */
double potencia(double a, double b);

/* Confirma uma ação */
int simOuNao(const char *msg);

/* Insere todos os números de um arquivo em uma lista */
Lista *arquivoCarrega(Lista *Ptd, const char *nome_arqv, int qtde); 
 
/* Gera números aleatórios e armazena em um arquivo */
int arquivoAleatoriza(const char *nome_arqv, const int min, const int max, const int qtde);

/* Salva os dados da lista em um arquivo */
int arquivoSalva(Lista *Ptd, const char *nome_arqv);

/* Exclui todas as ocorrências de um arquivo */
int arquivoExclui(const char *nome_arqv);

#endif  