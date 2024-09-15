#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lladae2_cocktail_sort.h"

#define sizeofvet(vet) (sizeof(vet) / sizeof((vet)[0]))

int main() {
  cls();
  printArquivo("arte.txt", C_MAGE);
  srand(time(NULL)); 
  clock_t inicio, fim;
  double tempo;  
  int i, qtd_l = intervalo("a quantidade de listas p/ testar...", 1, 5);
  int qtd_n = potencia(10, intervalo("a complexidade p/ testar...", 0, 6)); 
  int prev = !simOuNao("alterar o nome dos arquivos");
  char *nome_arquivos[] = {prev ? "base_dados.csv" : arquivoNome("base"), 
                           prev ? "lista_desordenada.csv" : arquivoNome("lista desordenada"), 
                           prev ? "lista_ordenada.csv" : arquivoNome("lista ordenada")};

  for (i = 0; i < sizeofvet(nome_arquivos); i++) {
    arquivoExclui(nome_arquivos[i]);
  }

  Lista *listas[qtd_l], *mesclada; 
  arquivoAleatoriza(nome_arquivos[0], 1, 99999, qtd_n);

  for (i = 0; i < qtd_l; i++) { // Inicializa cada uma das listas
   listas[i] = listaCria();
  }
  mesclada = listaCria();

  for (i = 0; i < qtd_l; i++) { // Percorre o vetor de listas
    listas[i] = arquivoCarrega(listas[i], nome_arquivos[0], qtd_n);
  }

  for (i = 0; i < qtd_l; i++) { // Salva as listas em arquivos
    arquivoSalva(listas[i], nome_arquivos[1]);
  }
   
  /* 
  for (i = 0; i < qtd_l; i++) { // Mostra os elementos de cada lista
    printf("\n\nLista %soriginal%s(%d)%s[%d]%s:\n", C_VERD, C_MAGE, i + 1, C_AMAR, listaSize(listas[i]), C_RSET);
    listaImprime(listas[i]);
  } 
  */

  inicio = clock();
  for (i = 0; i < qtd_l; i++) { // Ordena cada uma das listas usando o Cocktail Sort
    printf("\n%sOrdenando%s a lista%s(%d)%s...\n", C_AZUL, C_RSET, C_MAGE, i + 1, C_RSET);
    listas[i] = listaCocktailSort(listas[i]);
  }
  fim = clock();
  tempo =  (double) (fim - inicio) / CLOCKS_PER_SEC;

  /* 
  for (i = 0; i < qtd_l; i++) { // Mostra os elementos de cada lista depois de ordenar
    printf("\n\nLista %sordenada%s(%d)%s[%d]%s:\n", C_AZUL, C_MAGE, i + 1, C_AMAR, listaSize(listas[i]), C_RSET);
    listaImprime(listas[i]);
  } 
  */

  /* 
  printf("\n\n%sMesclando%s listas...\n", C_AZUL, C_RSET);
  for (i = 0; i < qtd_l; i++) { // Mescla todas as listas
    mesclada = listaMescla(mesclada, listas[i]);
  } 
  printf("\nLista %sresultante%s[Tam.:%d]%s:\n", C_AZUL, C_AMAR, listaSize(mesclada), C_RSET);
  listaImprime(mesclada); 
  */

  printf("\nTempo p/ ordenar: %.4f segundos\n", tempo);

  for (i = 0; i < qtd_l; i++) { // Salva as listas ordenadas em arquivos
    arquivoSalva(listas[i], nome_arquivos[2]);
  }

  for (i = 0; i < qtd_l; i++) { // Libera a memória de todas as listas
    listas[i] = listaLibera(listas[i]);
  }
  mesclada = listaLibera(mesclada);

  limpaTela("Aperte [ENTER] p/ fechar...");
  return 0;
}