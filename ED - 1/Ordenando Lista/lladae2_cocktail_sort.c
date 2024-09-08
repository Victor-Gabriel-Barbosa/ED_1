#include <stdio.h>
#include <stdlib.h>
#include "lladae2_cocktail_sort.h"

/* Variáveis que armazenam cores de texto */
const char *C_RSET = "\033[0m";
const char *C_AZUL = "\033[38;5;39m";
const char *C_VERD = "\033[38;5;46m";
const char *C_CIAN = "\033[38;5;51m";
const char *C_VERM = "\033[38;5;196m";
const char *C_MAGE = "\033[38;5;201m";
const char *C_AMAR = "\033[38;5;220m";

typedef struct no { // Estrutura que armazena os nós da lista
  int dado;
  struct no *prox;
  struct no *ant;
} No;

typedef struct lista { // Estrutura que armazena a lista
  No *inicio;
  No *fim;
  int tam;
} Lista;

No *no_atual = NULL; // Nó atual para destacar
No *no_proximo = NULL; // Próximo nó para destacar

/* Cria uma nova lista vazia */ 
Lista *listaCria() {
  Lista *Ptl = (Lista *)malloc(sizeof(Lista));
  if (Ptl != NULL) { // Inicializa a lista se a alocação for bem sucedida
    Ptl->inicio = NULL;
    Ptl->fim = NULL;
    Ptl->tam = 0;
  }
  return Ptl;
}

/* Tamanho da lista */
int listaSize(Lista *Ptl) { 
  return Ptl->tam;
}

/* Insere um novo elemento no início da lista */
Lista* listaInsereInicio(Lista *Ptl, const int dado) {
  No *novo = (No *)malloc(sizeof(No));
  if (novo == NULL) return Ptl; 
  novo->dado = dado;
  novo->prox = Ptl->inicio;
  novo->ant = NULL;
  if (Ptl->inicio != NULL) Ptl->inicio->ant = novo; 
  Ptl->inicio = novo;
  if (Ptl->fim == NULL) Ptl->fim = novo; 
  Ptl->tam++;
  return Ptl;
}

/* Insere um novo elemento no fim da lista */
Lista *listaInsereFim(Lista *Ptl, const int dado) {
  No *novo = (No *)malloc(sizeof(No));
  if (novo == NULL) return Ptl;
  novo->dado = dado;
  novo->prox = NULL;
  novo->ant = Ptl->fim;
  if (Ptl->fim != NULL) Ptl->fim->prox = novo;
  Ptl->fim = novo;
  if (Ptl->inicio == NULL) Ptl->inicio = novo;
  Ptl->tam++;
  return Ptl;
}

/* Remove um elemento da lista */
Lista *listaRemove(Lista *Ptl, const int dado) {
  if (Ptl == NULL || Ptl->inicio == NULL) return Ptl;
  No *atual = Ptl->inicio;
  while (atual != NULL) { // Percorre a lista
    if (atual->dado == dado) { // Se encontrou o dado, remove e retorna a lista
      if (atual->ant) atual->ant->prox = atual->prox;
      else Ptl->inicio = atual->prox;
      if (atual->prox) atual->prox->ant = atual->ant;
      else Ptl->fim = atual->ant;
      free(atual);
      Ptl->tam--;
      return Ptl;
    }
    atual = atual->prox;
  }
  return Ptl;
}

/* Libera toda a memória alocada para a lista */
Lista *listaLibera(Lista *Ptl) {
  if (Ptl == NULL || Ptl->inicio == NULL) return Ptl;
  No *atual = Ptl->inicio;
  No *prox;
  while (atual != NULL) { // Libera todos os nós da lista
    prox = atual->prox;
    free(atual); 
    atual = prox;
  }
  free(Ptl); 
}

/* Imprime a lista */
int listaImprime(Lista *Ptl) {
  if (Ptl == NULL || Ptl->inicio == NULL) return 0;
  No *atual = Ptl->inicio;
  while (atual != NULL) { // Mostra todos os elementos da lista
    printf("%d ", atual->dado);
    atual = atual->prox;
  }
  return 1;
} 

int listaImprimeTroca(Lista *Ptl, No *Ptatual) {
  if (Ptl == NULL || Ptl->inicio == NULL) return 0;
  No *atual = Ptl->inicio;
  while (atual != NULL) { // Mostra todos os elementos da lista
    if (atual == no_atual) {
      printf("%s%d%s ", C_AZUL, atual->dado, C_RSET);
    } else if (atual == no_atual->prox) {
      printf("%s%d%s ", C_VERD, atual->dado, C_RSET);
    } else {
      printf("%d ", atual->dado);
    }
    atual = atual->prox;
  }
  return 1;
}

/* Ordena a lista usando o algoritmo Cocktail Sort */
Lista *listaCocktailSort(Lista *Ptl) {
  if (Ptl == NULL || Ptl->inicio == NULL) return Ptl;
  int trocou, temp;
  No *inicio = Ptl->inicio; 
  No *fim = Ptl->fim;
  No *atual;
  do { // Repete enquanto houver trocas
    trocou = 0;
    atual = inicio;
    printf("\n%s</>%s Esquerda ⥅ Direita %s</>%s\n", C_MAGE, C_CIAN, C_MAGE, C_RSET);
    while (atual != fim) { // Percorre da esquerda para a direita
      if (atual->dado > atual->prox->dado) { // Troca os valores dos nós se o dado atual for maior que o próximo
        temp = atual->dado;
        atual->dado = atual->prox->dado;
        atual->prox->dado = temp;
        trocou = 1;
        listaImprimeTroca(Ptl, atual);
        printf("%s[%d]%s ⥂ %s[%d]%s\n", C_VERD, atual->prox->dado, C_CIAN, C_AZUL, atual->dado, C_RSET);
      }
      atual = atual->prox;
    }
    if (!trocou) continue; // A lista já está ordenada se não houve trocas
    fim = fim->ant;
    trocou = 0;
    atual = fim;
    printf("\n%s</>%s Esquerda ⥆ Direita %s</>%s\n", C_MAGE, C_CIAN, C_MAGE, C_RSET);
    while (atual != inicio) {  // Percorre da direita para a esquerda
      if (atual->dado < atual->ant->dado) { // Troca os valores dos nós se o dado atual for menor que o anterior
        temp = atual->dado;
        atual->dado = atual->ant->dado;
        atual->ant->dado = temp;
        trocou = 1;
        listaImprimeTroca(Ptl, atual->ant);
        printf("%s[%d]%s ⥃ %s[%d]%s\n", C_VERD, atual->dado, C_CIAN, C_AZUL, atual->ant->dado, C_RSET);
      }
      atual = atual->ant;
    }
    inicio = inicio->prox;
  } while (trocou);
  return Ptl;
}

/* Mescla duas listas */
Lista *listaMescla(Lista *Ptl1, Lista *Ptl2) {
  No *n1 = Ptl1->inicio;
  No *n2 = Ptl2->inicio;
  Lista *novaLista = listaCria();
  while (n1 != NULL && n2 != NULL) { // Percorre as duas listas
    if (n1->dado <= n2->dado) { // Insere o menor elemento da lista
      listaInsereFim(novaLista, n1->dado);
      n1 = n1->prox;
    } else {
      listaInsereFim(novaLista, n2->dado);
      n2 = n2->prox;
    }
  }
  while (n1 != NULL) { // Insere os elementos restantes da lista 1
    listaInsereFim(novaLista, n1->dado);
    n1 = n1->prox;
  }
  while (n2 != NULL) { // Insere os elementos restantes da lista 2
    listaInsereFim(novaLista, n2->dado);
    n2 = n2->prox;
  }
  return novaLista;
}

/* Limpa o buffer do teclado */
void limpaBuffer() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void limpaTela(const char *msg) {
  printf("\n%s", msg);
  limpaBuffer();
  #ifdef _WIN32
    system("cls");
  #else 
    system("clear");
  #endif 
}