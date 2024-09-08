#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lladae2_cocktail_sort.h"

int main() {
  srand(time(NULL));
  int i, j, qtd_l = 4, qtd_n = 10;
  Lista *listas[qtd_l], *mesclada; 

  for (i = 0; i < qtd_l; i++) { // Inicializa cada uma das listas
   listas[i] = listaCria();
  }
  mesclada = listaCria();

  for (j = 0; j < qtd_n; j++) { // Insere elementos de forma aleatória nas listas
    for (i = 0; i < qtd_l; i++) { // Percorre o vetor de listas
      listas[i] = (j % 2 == 0) ? listaInsereFim(listas[i], rand() % (j + 1)) : listaInsereInicio(listas[i], rand() % (j + 1));
    }
  }
  
  for (i = 0; i < qtd_l; i++) { // Mostra os elementos de cada lista
    printf("\n\nLista original(Lis.:%d)[Tam.:%d]:\n", i + 1, listaSize(listas[i]));
    listaImprime(listas[i]);
  }

  for (i = 0; i < qtd_l; i++) { // Ordena cada uma das listas usando o Cocktail Sort
    printf("\n\nOrdenando a lista(%d) ...\n", i + 1);
    listas[i] = listaCocktailSort(listas[i]);
  }

  for (i = 0; i < qtd_l; i++) { // Mostra os elementos de cada lista depois de ordenar
    printf("\n\nLista ordenada(Lis.:%d)[Tam.:%d]:\n", i + 1, listaSize(listas[i]));
    listaImprime(listas[i]);
  }

  printf("\n\nRemovendo o elemento 3...\n");
  for (i = 0; i < qtd_l; i++) { // Remove o elemento 3 de cada uma das listas
    listas[i] = listaRemove(listas[i], 3);
    listaImprime(listas[i]);
  }

  printf("\n\nInserindo 10 no início...\n");
  for (i = 0; i < qtd_l; i++) { // Insere o elemento 10 no início de cada uma das listas
    listas[i] = listaInsereInicio(listas[i], 10);
    listaImprime(listas[i]);
  }

  printf("\n\nInserindo 7\n");
  for (i = 0; i < qtd_l; i++) { // Insere o elemento 7 no fim de cada uma das listas
    listas[i] = listaInsereFim(listas[i], 7);
    listaImprime(listas[i]);
  }

  printf("\n\nMesclando listas...\n");
  for (i = 0; i < qtd_l; i++) { // Mescla todas as listas
    mesclada = listaMescla(mesclada, listas[i]);
  } 
  printf("\n\nLista resultante[Tam.:%d]:\n", listaSize(mesclada));
  listaImprime(mesclada);

  for (i = 0; i < qtd_l; i++) { // Libera a memória de todas as listas
    listas[i] = listaLibera(listas[i]);
  }
  mesclada = listaLibera(mesclada);

  return 0;
}
