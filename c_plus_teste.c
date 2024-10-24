#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <cplus.h>

typedef struct Medicos {
  char nome[50];
  int crm;
} Medico;

int main() {
  srand(time(NULL));
  print(toObj(&((Medico){"Mara", 124})));
  string nomes[] = {
    stringInit("Ana"), stringInit("Mara"), stringInit("Sara"),
    stringInit("Pedro"), stringInit("João"), stringInit("José"),
    stringInit("Luisa"), stringInit("Maria"), stringInit("Carlos")
  };
  obj temp;
  list lista = listNew();
  queue fila = queueNew();
  stack pilha = stackNew();
  tree arvore = treeNew();
  foreach(nome, nomes) arvore = treeAdd(arvore, toObj(*nome));
  foreach(nome, nomes) listAddEnd(lista, toObj(*nome));
  foreach(nome, nomes) queueEnqueue(fila, toObj(*nome));
  printf("Por aqui: ");
  treePrint(arvore);
  printf("\nAcima\n");
  stackPush(pilha, toObj(randInt(nomes)));
  stackTop(pilha, &temp);
  temp = toObj(randInt(nomes));
  print(toObj("\nPessoa Consultada: "), temp);
  print(toObj("\nPessoa Consultada: "), temp);
  queueEnqueue(fila, toObj(pilha));
  listAddEnd(lista, toObj(fila));
  printf("\nNomes (Não Ordenados):\n");
  print(toObj(lista));
  listSort(lista);
  printf("\nNomes (Ordenados):\n");
  print(toObj(lista), toObj("\nOutra Vez:\n"), toObj(lista));
  print(toObj("\nElemento da lista: "), listGet(lista, 3));
  printfs("\n\nElemento da posição %d: %O\n\n", 9, listGet(lista, 9));
  objPrint(toObj(lista));
  lista = listDestroy(lista);
  fila = queueDestroy(fila);
  pilha = stackDestroy(pilha);
  foreach(nome, nomes) stringDestroy(*nome);
  printf("\nFIM\n");
  return 0;
}