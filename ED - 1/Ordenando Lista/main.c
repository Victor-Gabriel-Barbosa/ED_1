#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lladae2_cocktail_sort.h"

int main() {
  srand(time(NULL));
  int i, k, qtd_l = 4, qtd_n = 10;
  Lista *listas[qtd_l], *mesclada; 

  for (i = 0; i < qtd_l; i++) { // Inicializa cada uma das listas
   listas[i] = listaCria();
  }
  mesclada = listaCria();

  for (k = 0; k < qtd_n; k++) { // Insere elementos de forma aleatória nas listas
    for (i = 0; i < qtd_l; i++) { // Percorre o vetor de listas
      listas[i] = (k % 2 == 0) ? listaInsereFim(listas[i], rand() % (k + 1)) : listaInsereInicio(listas[i], rand() % (k + 1));
    }
  }
  
  for (i = 0; i < qtd_l; i++) { // Mostra os elementos de cada lista
    printf("\n\nLista %soriginal%s(%d)%s[%d]%s:\n", C_VERD, C_MAGE, i + 1, C_AMAR, listaSize(listas[i]), C_RSET);
    listaImprime(listas[i]);
  }

  for (i = 0; i < qtd_l; i++) { // Ordena cada uma das listas usando o Cocktail Sort
    printf("\n\n%sOrdenando%s a lista%s(%d)%s...\n", C_AZUL, C_RSET, C_MAGE, i + 1, C_RSET);
    listas[i] = listaCocktailSortV2(listas[i]);
  }

  for (i = 0; i < qtd_l; i++) { // Mostra os elementos de cada lista depois de ordenar
    printf("\n\nLista %sordenada%s(%d)%s[%d]%s:\n", C_AZUL, C_MAGE, i + 1, C_AMAR, listaSize(listas[i]), C_RSET);
    listaImprime(listas[i]);
  }

  printf("\n\n%sRemovendo%s o elemento %s3%s...\n", C_VERM, C_RSET, C_VERM, C_RSET);
  for (i = 0; i < qtd_l; i++) { // Remove o elemento 3 de cada uma das listas
    listas[i] = listaRemove(listas[i], 3);
    listaImprime(listas[i]);
  }

  printf("\n\n%sInserindo%s o elemento %s10%s no início...\n", C_CIAN, C_RSET, C_CIAN, C_RSET);
  for (i = 0; i < qtd_l; i++) { // Insere o elemento 10 no início de cada uma das listas de forma ordenada
    listas[i] = listaCocktailSortV2(listaInsereInicio(listas[i], 10));
    listaImprime(listas[i]);
  }

  printf("\n\n%sInserindo%s o elemento %s7%s no fim...\n", C_CIAN, C_RSET, C_CIAN, C_RSET);
  for (i = 0; i < qtd_l; i++) { // Insere o elemento 7 no fim de cada uma das listas de forma ordenada
    listas[i] = listaCocktailSortV2(listaInsereFim(listas[i], 7));
    listaImprime(listas[i]);
  }

  printf("\n\n%sMesclando%s listas...\n", C_AZUL, C_RSET);
  for (i = 0; i < qtd_l; i++) { // Mescla todas as listas
    mesclada = listaMescla(mesclada, listas[i]);
  } 
  printf("\nLista %sresultante%s[Tam.:%d]%s:\n", C_AZUL, C_AMAR, listaSize(mesclada), C_RSET);
  listaImprime(mesclada);

  for (i = 0; i < qtd_l; i++) { // Libera a memória de todas as listas
    listas[i] = listaLibera(listas[i]);
  }
  mesclada = listaLibera(mesclada);

  return 0;
}
