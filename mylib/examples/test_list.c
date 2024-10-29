#include <stdio.h>
#include <stdlib.h>
#include "cplus.h"

int main() {
  // Testa a criação de uma nova lista
  list minhaLista = listNew();
  if (minhaLista == NULL) {
    fprintf(stderr, "Falha ao criar a lista\n");
    return 1;
  }

  // Adiciona valores à lista
  int qtd = chooseInt("Digite a quantidade de números: ", 1, 10000000);
  timer(for (int i = 0; i < qtd; i++) {
    listAdd(minhaLista, rand() % qtd);
  });

  // Imprime a lista
  if (confirm("Imprimir lista")) {
    timer(
      printf("Lista após adições: ");
      listPrint(minhaLista);
      printf("\n");
    );
  }

  // Teste de inserção no início
  int valorInicio = 5;
  listAddIni(minhaLista, toObj(valorInicio));
  printf("Lista após adicionar 5 no início: ");
  if (confirm("Imprimir lista")) {
    timer(
      listPrint(minhaLista);
      printf("\n");
    );
  }

  // Teste de remoção
  printf("Removendo o elemento na posição 2:\n");
  minhaLista = listRemove(minhaLista, 2);
  if (confirm("Imprimir lista")) {
    timer(
      listPrint(minhaLista);
      printf("\n");
    );
  }

  // Teste de busca
  obj encontrado;
  printf("Buscando o elemento na posição 1...\n");
  timer(
    if (listSearch(minhaLista, 1, &encontrado) == 1) printfs("Elemento na posição 1 encontrado: %O\n", encontrado);
    else printf("Elemento na posição 1 não encontrado\n");
  );

  // Teste de ordenação
  printf("Ordenando a lista...\n");
  timer(
    minhaLista = listSort(minhaLista);
  );
  printf("Lista ordenada: ");
  if (confirm("Imprimir lista")) {
    timer(
      listPrint(minhaLista);
      printf("\n");
    );
  }

  // Teste de mesclagem de listas
  list lista2 = listNew();
  int moreValues[] = {60, 70, 80, 11};
  string nome = stringInit("Mara");
  listAdd(lista2, nome);
  listAdd(lista2, nome);
  listAdd(lista2, nome);

  printf("Lista 2: ");
  objPrint(toObj(lista2));
  printf("\n");

  list listaMesclada;
  timer(
    listaMesclada = listMerge(minhaLista, lista2);
  );
  printf("Lista mesclada: ");
  if (confirm("Imprimir lista")) {
    timer(
      listPrint(listaMesclada);
      printf("\n");
    );
  }

  // Limpa as listas
  timer(
    minhaLista = listDestroy(minhaLista);
    lista2 = listDestroy(lista2);
    listaMesclada = listDestroy(listaMesclada);
  );

  return 0;
}