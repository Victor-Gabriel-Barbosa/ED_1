#include <stdio.h>
#include <string_ext.h>
#include <queue.h>

int main() {
  Queue fila = newQueue();
  enqueue(fila, 1);
  enqueue(fila, 2);
  printsf("%Q", fila);
  printf("Digite vários nomes (Separados por espaço): ");
  String nomes = inputString();
  String *tokens = splitString(&nomes, " ");
  for (int i = 0; tokens[i].data != NULL; i++) {
    printf("Nome: %s\n", tokens[i]);
  }
  int num = 0;
  dequeue(fila, &num);
  printsf("%S %d\n", nomes, num);
  destroyString(&nomes);
  for (int i = 0; tokens[i].data != NULL; i++) {
    destroyString(&tokens[i]);
  }
  destroyQueue(fila);
  return 0; 
}