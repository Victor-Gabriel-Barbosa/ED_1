#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

typedef struct ponto { // Definição da estrutura do nó da lista
  int dado;
  struct ponto *proximo;
} ponto;

typedef struct Lista { // Definição da estrutura da lista
  ponto *cabeca;
} Lista;

// Funções para manipular a lista encadeada:
Lista *criar_lista();
int inserir_no_inicio(Lista *lista, int valor);
int inserir_no_final(Lista *lista, int valor);
int remover_ponto(Lista *lista, int valor);
int consultar_ponto(Lista *lista, int valor);
void imprimir_lista(Lista *lista);
void liberar_lista(Lista *lista);
void limpBuffer(void);
void limpTela();
void barra(char *ini, char *fin);

#endif // LISTA_ENCADEADA_H