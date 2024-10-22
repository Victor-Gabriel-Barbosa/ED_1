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
  foreach(nome, nomes) listAddEnd(lista, toObj(*nome));
  foreach(nome, nomes) queueEnqueue(fila, toObj(*nome));
  for (size_t i = 0; i < ARRAY_SIZE(nomes) / 2; i++) {
    stackPush(pilha, toObj(RAND(nomes)));
  }
  stackTop(pilha, &temp);
  temp = toObj(RAND(nomes));
  print(toObj("\nPessoa Consultada: "), temp);
  queueEnqueue(fila, toObj(pilha));
  listAddEnd(lista, toObj(fila));
  printf("\nNomes (Não Ordenados):\n");
  print(toObj(lista));
  listSort(lista);
  printf("\nNomes (Ordenados):\n");
  print(toObj(lista), toObj("\nOutra Vez:\n"), toObj(lista));
  lista = listDestroy(lista);
  fila = queueDestroy(fila);
  pilha = stackDestroy(pilha);
  foreach(nome, nomes) stringDestroy(*nome);
  printf("\nFIM\n");
  return 0;
}