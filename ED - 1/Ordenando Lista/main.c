#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lladae2_cocktail_sort.h"

int main() {
  srand(time(NULL)); 
  // geraNumerosAleatorios("numeros.txt", 1000000, 1, 10000);
  clock_t inicio, fim;
  double tempo;
  int i, qtd_l = 1, complex = 5;
  int qtde_n = potencia(10, complex);
  
  Lista *listas[qtd_l], *mesclada; 

  for (i = 0; i < qtd_l; i++) { // Inicializa cada uma das listas
   listas[i] = listaCria();
  }
  mesclada = listaCria();

  for (i = 0; i < qtd_l; i++) { // Percorre o vetor de listas
      listas[i] = arquivoCarrega(listas[i], "numeros.txt", qtde_n);
  }
  
  for (i = 0; i < qtd_l; i++) { // Mostra os elementos de cada lista
    printf("\n\nLista %soriginal%s(%d)%s[%d]%s:\n", C_VERD, C_MAGE, i + 1, C_AMAR, listaSize(listas[i]), C_RSET);
    listaImprime(listas[i]);
  }

  inicio = clock();
  for (i = 0; i < qtd_l; i++) { // Ordena cada uma das listas usando o Cocktail Sort
    printf("\n\n%sOrdenando%s a lista%s(%d)%s...\n", C_AZUL, C_RSET, C_MAGE, i + 1, C_RSET);
    inicio = clock();
    listas[i] = listaCocktailSort(listas[i]);
  }
  fim = clock();
  tempo =  (double) (fim - inicio) / CLOCKS_PER_SEC;

  for (i = 0; i < qtd_l; i++) { // Mostra os elementos de cada lista depois de ordenar
    printf("\n\nLista %sordenada%s(%d)%s[%d]%s:\n", C_AZUL, C_MAGE, i + 1, C_AMAR, listaSize(listas[i]), C_RSET);
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

  printf("\n\nTempo: %.4f segundos p/ ordenar\n", tempo);
  return 0;
}
