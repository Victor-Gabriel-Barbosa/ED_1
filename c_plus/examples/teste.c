#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cplus.h"

typedef struct testes {
  char nome[50];
  int num;
} teste;

int main() {
  printf(fLn(BOLD UNDERLINE CYAN, "TESTE DA BIBLIOTECA C_PLUS"));
  srand(time(NULL));
  list lista = listNew();
  queue fila = queueNew();
  stack pilha = stackNew();
  tree arvore = treeNew();
  obj temp;
  int teste = chooseInt("Digite o número de valores", 1, 100000000);
  timer(for(int i = 0; i < teste; i++) listAdd(lista, rand() % teste); printf("Lista Inserção - "));
  timer(for(int i = 0; i < teste; i++) queueAdd(fila, rand() % teste); printf("Fila Inserção - "));
  timer(for(int i = 0; i < teste; i++) stackAdd(pilha, rand() % teste); printf("Pilha Inserção - "));
  timer(for(int i = 0; i < teste; i++) treeAdd(arvore, rand() % teste); printf("Árvore Inserção - "));
  timer(listSort(lista); printf("Lista Ordenação - "));
  if(confirm("Deseja exibir a lista")) timer(print(toString(toString(lista))); printf("\nLista Listagem - "));
  if(confirm("Deseja exibir a fila")) timer(printfs("%F", fila); printf("\nFila Listagem - "));
  if(confirm("Deseja exibir a pilha")) timer(printfs("%P", pilha); printf("\nPilha Listagem - "));
  if(confirm("Deseja exibir a árvore")) timer(printfs("%A", arvore); printf("\nÁrvore Listagem - "));
  timer(while (!listIsEmpty(lista)) {
    listPopBack(lista, &temp); 
    printfs("%O, ", temp);
  });
  lista = listFree(lista);
  fila = queueFree(fila);
  pilha = stackFree(pilha);
  arvore = treeFree(arvore);
  printf("\nFim\n");
  return 0;
}