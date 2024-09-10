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
  if (Ptl == NULL) return Ptl;
  No *atual = Ptl->inicio;
  while (atual != NULL) { // Percorre a lista
    if (atual->dado == dado) { // Se encontrou o dado, remove e retorna a lista
      if (atual->ant != NULL) atual->ant->prox = atual->prox;
      else Ptl->inicio = atual->prox;
      if (atual->prox != NULL) atual->prox->ant = atual->ant;
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
  if (Ptl == NULL) return Ptl;
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
  int cont = 0;
  No *atual = Ptl->inicio;
  while (atual != NULL) { // Mostra todos os elementos da lista
    printf("%d", atual->dado);
    printf((cont + 1) % 10 == 0 ? "\n" : " ");
    cont == 9 ? cont = 0 : cont++;
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
    while (atual != fim) { // Percorre da esquerda para a direita
      if (atual->dado > atual->prox->dado) { // Troca os valores dos nós se o dado atual for maior que o próximo
        temp = atual->dado;
        atual->dado = atual->prox->dado;
        atual->prox->dado = temp;
        trocou = 1;
      }
      atual = atual->prox;
    }
    if (!trocou) continue; // A lista já está ordenada se não houve trocas
    fim = fim->ant; // Atualiza o ponteiro fim para a próxima iteração
    trocou = 0;
    atual = fim;
    while (atual != inicio) {  // Percorre da direita para a esquerda
      if (atual->dado < atual->ant->dado) { // Troca os valores dos nós se o dado atual for menor que o anterior
        temp = atual->dado;
        atual->dado = atual->ant->dado;
        atual->ant->dado = temp;
        trocou = 1;
      }
      atual = atual->ant;
    }
    inicio = inicio->prox; // Atualiza o ponteiro início para a próxima iteração
  } while (trocou);
  return Ptl;
}

/* Mescla duas listas */
Lista *listaMescla(Lista *Ptl1, Lista *Ptl2) {
  No *n1 = Ptl1->inicio;
  No *n2 = Ptl2->inicio;
  Lista *novaLista = listaCria();
  while (n1 != NULL && n2 != NULL) { // Percorre as duas listas
    if (n1->dado < n2->dado) { // Insere o menor elemento das listas
      novaLista = listaInsereFim(novaLista, n1->dado);
      n1 = n1->prox;
    } else if (n1->dado == n2->dado) { // Insere apenas um dos dados repetidos na lista
      novaLista = listaInsereFim(novaLista, n1->dado);
      n1 = n1->prox;
      n2 = n2->prox;
    } else {
      novaLista = listaInsereFim(novaLista, n2->dado);
      n2 = n2->prox;
    }
  }
  while (n1 != NULL) { // Insere os elementos restantes da lista 1
    novaLista = listaInsereFim(novaLista, n1->dado);
    n1 = n1->prox;
  }
  while (n2 != NULL) { // Insere os elementos restantes da lista 2
    novaLista = listaInsereFim(novaLista, n2->dado);
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

/* Insere todos os números de um arquivo em uma lista */
Lista *arquivoCarrega(Lista *Ptl, const char *nome, int qtde) {
  FILE *arqv = fopen(nome, "r");
  if (arqv == NULL) {
    printf("\nErro ao abrir o arquivo!\n");
    return Ptl;
  }
  int dado;
  printf("\nQtde %d\n", qtde);
  while (fscanf(arqv, "%d", &dado) == 1 && qtde > 0) {
    Ptl = (rand() % 2 == 0) ? listaInsereInicio(Ptl, dado) : listaInsereFim(Ptl, dado);
    qtde--;
  }
  fclose(arqv); 
  return Ptl;
}

void geraNumerosAleatorios(const char *nome, const int qtde, const int min, const int max) { 
    FILE *arquivo;
    arquivo = fopen(nome, "w"); // Abre o arquivo para escrita
    if (arquivo == NULL) {
      printf("Erro ao criar o arquivo!\n");
      return;
    }
    for (int i = 0; i < qtde; i++) { // Gera números aleatórios entre min e max
      int numero = rand() % (max - min + 1) + min; 
      fprintf(arquivo, "%d", numero);
      fprintf(arquivo, (i + 1) % 10 == 0 ? "\n" : " "); // Quebra de linha a cada 10 números
    }
    fclose(arquivo); // Fecha o arquivo
    printf("Arquivo '%s' gerado com sucesso!\n", nome);
}

/* Faz uma operação de pontência */
double potencia(double a, double b) {
  double resultado = 1;
  for (int i = 0; i < b; i++) {
    resultado *= a;
  }
  return resultado;
}