#include <stdio.h>
#include <c_plus.h>

int main() {
  String n1 = inputString();
  String n2 = inputString();
  String nome = (appendStrings(n1, n2));
  printsf("Nome concatenado: %S\n", nome);
  Stack stk = newStack();
  push(stk, 1);
  push(stk, 2);
  printsf("%Q", stk);
  destroyStack(stk);
  Queue fila = newQueue();
  enqueue(fila, 1);
  enqueue(fila, 2);
  int temp = 0;
  dequeue(fila, &temp);
  printsf("\nDequeue: %d\n", temp);
  printsf("%Q", fila);
  printf("Digite vários nomes (Separados por espaço): ");
  String nomes = inputString();
  String *tokens = splitString(nomes, " ");
  for (int i = 0; getString(tokens[i]) != NULL; i++) {
    printsf("Nome: %S\n", tokens[i]);
  }
  int num = 0;
  dequeue(fila, &num);
  printsf("%S %d\n", nomes, num);
  destroyString(nomes);
  for (int i = 0; getString(tokens[i]) != NULL; i++) {
    destroyString(tokens[i]);
  }
  destroyQueue(fila);
  return 0; 
}