#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

/* Estrutura do nó */
typedef struct No {
  int dado;
  struct No *proximo;
} No;

/* Estrutura da lista */
typedef struct Lista { 
  No *cabeca;
} Lista;

/* Cria uma lista vazia */
Lista *cria_lista(); 

/* Insere um novo nó no início da lista */
int insere_no_inicio(Lista *lista, int valor);  

/* Insere um novo nó no final da lista */
int insere_no_final(Lista *lista, int valor); 

/* Remove um nó com o valor especificado */
int remove_No(Lista *lista, int valor); 

/* Consulta se um nó com o valor especificado está na lista */
int consultar_No(Lista *lista, int valor); 

/* Imprime a lista */
void imprime_lista(Lista *lista);

/* Libera a memória alocada pela lista */
void libera_lista(Lista *lista); 

/* Limpa o buffer do teclado */
void limpa_buffer();

/* Limpa a tela */
void limpa_tela();

/* Confirmação de ação */
int sim_ou_nao(char *msg);

/* Salva a lista em um arquivo */
void salva_lista(Lista *lista, char *nome_arqv);

/* Escolha do menu */
int escolha_menu();

/* Funcionalidade do menu */
void menu(Lista *lista); 

#endif // LISTA_ENCADEADA_H