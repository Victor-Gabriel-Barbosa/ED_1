#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "cplus.h"

int main() { 
  srand(time(NULL));
  clock_t inicio, fim;
  list vector = listNew();
  map arvore = mapNew();
  int qtd = choose("Digite a quantidade de números", 1, 1000000);
  inicio = clock();
  arvore = mapAdd(arvore, toObj(11));
  for (int i = 0; i < qtd; i++) {
    int num = rand() % 1000;
    listAddEnd(vector, toObj(num));
    if (rand() % 2 == 1) listAddEnd(vector, toObj(arvore));
  }
  fim = clock();
  printf("Tempo gasto p/ inserção: %g segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

  inicio = clock();
  listSort(vector);
  fim = clock();
  printf("Tempo gasto p/ ordenação: %g segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

  if (confirm("imprimir a lista")) {
    inicio = clock();
    print(toObj(vector));
    fim = clock();
    printf("Tempo gasto p/ impressão: %g segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
  }
  vector = listDestroy(vector);


  list String = listNew();
  qtd = choose("Digite a quantidade de letras", 1, 1000000000);
  inicio = clock();
  for (int i = 0; i < qtd; i++) {
    char letra = rand() % 26 + 'a';
    listAddEnd(String, toObj(letra));
  }
  fim = clock();
  printf(f(BLUE, "\nTempo gasto p/ inserção: %g segundos\n"), (double)(fim - inicio) / CLOCKS_PER_SEC);

  inicio = clock();
  listSort(String);
  fim = clock();
  printf("\nTempo gasto p/ ordenação: %g segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
  
  if (confirm("Imprimir a lista")) {
    inicio = clock();
    print(toObj(String));
    fim = clock();
    printf("\nTempo gasto p/ impressão: %g segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
  }
  String = listDestroy(String);
  arvore = mapDestroy(arvore);
}