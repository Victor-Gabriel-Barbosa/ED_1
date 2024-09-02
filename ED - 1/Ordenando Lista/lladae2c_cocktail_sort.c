#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Estrutura para nó da lista duplamente encadeada */
typedef struct No {
  int dado;
  struct No* anterior;
  struct No* proximo;
} No;

/* Função para criar uma lista vazia */
No* criarLista() {
  return NULL;
}

/* Função para inserir um novo nó no final da lista */
void inserirNoFim(No** cabeca, int valor) {
  No* novoNo = (No*)malloc(sizeof(No));
  novoNo->dado = valor;
  novoNo->anterior = NULL;
  novoNo->proximo = NULL;
  if (*cabeca == NULL) { // Verifica se a lista está vazia
    *cabeca = novoNo;
  } else {
    No* ultimoNo = *cabeca;
    while (ultimoNo->proximo != NULL) { // Percorre a lista
      ultimoNo = ultimoNo->proximo;
    }
    ultimoNo->proximo = novoNo;
    novoNo->anterior = ultimoNo;
  }
}

/* Remove um elemento da lista */
int removerDaLista(No** cabeca, int valor) { 
  No* noAtual = *cabeca;
  No* noAnterior = NULL;
  int removido = 0;

  while (noAtual != NULL) { // Percorrer a lista 
    if (noAtual->dado == valor) { // Verifica se encontrou o valor
      if (noAnterior == NULL) { // Verifica se o nó é o primeiro da lista
        *cabeca = noAtual->proximo;
        if (*cabeca!= NULL) {
          (*cabeca)->anterior = NULL;
        }
      } else { // Se o nó não é o primeiro da lista 
        noAnterior->proximo = noAtual->proximo;
        if (noAtual->proximo != NULL) {
          noAtual->proximo->anterior = noAnterior;
        }
      }
      free(noAtual);
      removido = 1;
      break;
    }
    noAnterior = noAtual;
    noAtual = noAtual->proximo;
  }

  return removido;
}

// Função para imprimir a lista duplamente encadeada
void imprimirLista(No* cabeca) {
  No* noAtual = cabeca;

  while (noAtual != NULL) {
    printf("%d ", noAtual->dado);
    noAtual = noAtual->proximo;
  }

  printf("\n");
}

// Função para ordenar a lista usando o Cocktail Sort
void ordenarCocktailSort(No** cabeca) {
  if (*cabeca == NULL) return;
  
  bool trocou;
  No* inicio = *cabeca;
  No* fim = NULL;

  do { // Loop de ordenação 'Cocktail Sort'
    trocou = false;

    while (inicio->proximo != fim) { // Percorrer da esquerda para a direita
      if (inicio->dado > inicio->proximo->dado) { // Trocar elementos se estiverem na ordem errada 
        int aux = inicio->dado;
        inicio->dado = inicio->proximo->dado;
        inicio->proximo->dado = aux;
        trocou = true;
      }
      inicio = inicio->proximo;
    }

    if (!trocou) // Se nenhuma troca foi feita, a lista já está ordenada
      continue;

    trocou = false;
    fim = inicio;
    inicio = *cabeca;

    while (inicio->proximo != fim) {  // Percorrer da direita para a esquerda 
      if (inicio->dado > inicio->proximo->dado) { // Trocar elementos se estiverem na ordem errada 
        int aux = inicio->dado;
        inicio->dado = inicio->proximo->dado;
        inicio->proximo->dado = aux;
        trocou = true;
      }
      inicio = inicio->proximo;
    }

    fim = inicio->anterior;
    inicio = *cabeca;
  } while (trocou);
}

// Função para mesclar duas listas ordenadas
No* mesclarListas(No* cabeca1, No* cabeca2) {
  No* cabecaResultado = NULL;
  if (cabeca1 == NULL) // Se a lista 1 está vazia, retorne a outra lista
    return cabeca2;
  if (cabeca2 == NULL) // Se a lista 2 está vazia, retorne a outra lista
    return cabeca1;
  if (cabeca1->dado <= cabeca2->dado) {   // Compara os dados dos nós das duas listas e insere o menor no resultado
    cabecaResultado = cabeca1;
    cabecaResultado->proximo = mesclarListas(cabeca1->proximo, cabeca2);
  } else {
    cabecaResultado = cabeca2;
    cabecaResultado->proximo = mesclarListas(cabeca1, cabeca2->proximo);
  }
  cabecaResultado->proximo->anterior = cabecaResultado; // Atualize o anterior do próximo nó
  
  return cabecaResultado; // Retorne a cabeça da lista resultante
}

void limpa_buffer() {
  char c;
  while ((c = getchar())!= '\n' && c!= EOF);
}

// Função principal
int main() {
  No* teste1 = criarLista();
  No* teste2 = criarLista();
  No* result = criarLista();

  // Inserir valores na lista
  inserirNoFim(&teste1, 5);
  inserirNoFim(&teste1, 3);
  inserirNoFim(&teste1, 8);
  inserirNoFim(&teste1, 4);
  inserirNoFim(&teste1, 2);
  inserirNoFim(&teste1, 1);
  inserirNoFim(&teste1, 9);
  inserirNoFim(&teste1, 6);
  inserirNoFim(&teste1, 7);
  if (removerDaLista(&teste1, 5)) {
    printf("Elemento 5 removido da lista [1]\n");
  } else {
    printf("Elemento 5 não encontrado na lista [1]\n");
  }

  inserirNoFim(&teste2, 11);
  inserirNoFim(&teste2, 10);
  inserirNoFim(&teste2, 9);
  inserirNoFim(&teste2, 8);

  printf("Lista desordenada [1]: ");
  imprimirLista(teste1);
  printf("Lista desordenada [2]: ");
  imprimirLista(teste2);

  ordenarCocktailSort(&teste1);
  ordenarCocktailSort(&teste2);

  printf("[😃]Lista ordenada [1]: ");
  imprimirLista(teste1);
  printf("[😃]Lista ordenada [2]: ");
  imprimirLista(teste2);

  result = mesclarListas(teste1, teste2);
  printf("[😃]Resultado da mesclagem: ");
  imprimirLista(result);

  return 0;
}