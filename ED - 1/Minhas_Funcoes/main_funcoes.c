#include <stdio.h>
#include "funcoes.h"

#define sizeofvet(vet) (sizeof(vet) / sizeof((vet)[0]))

int main() {
  // Nome dos arquivos
  char *nome_arquivos[] = {"funcionarios.csv"};
  
  // Exclui arquivos existentes
  for (int i = 0; i < sizeofvet(nome_arquivos); i++) {
    arquivoExclui(nome_arquivos[i]);
  }
  
  // Cria e popula a lista
  Lista *lista1 = listaCria();
  Info dados[] = {{3, "Ana", 39, 14000},
                  {2, "Maria", 21, 14000},
                  {1, "Mara", 32, 12255},
                  {4, "João", 45, 13000}};

  int num_dados = sizeofvet(dados);
  for (int i = 0; i < num_dados; i++) {
    listaInsereFim(lista1, dados[i]);
  }
  
  // Imprime e ordena a lista
  printf("\nLista Desordenada: ");
  listaImprime(lista1);
  lista1 = listaTimSort(lista1);
  printf("\nLista Ordenada: ");
  listaImprime(lista1);
  
  // Salva a lista em um arquivo
  arquivoSalva(lista1, nome_arquivos[0]);
  
  // Cria uma nova lista e carrega dados do arquivo
  Lista *lista2 = listaCria();
  arquivoCarrega(lista2, nome_arquivos[0], 1);
  listaImprime(lista2);
  
  return 0;
}
