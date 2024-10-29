#include <stdio.h>
#include "list.h"
#include "stringlib.h"
#include "utils.h"

int main() {
  printf("\nInicio\n");
  char palavra[50];
  try {
    printf("Digite uma palavra: ");
    scanf("%49[^\n]", palavra);
    throw;
    printf("\nErro\n");
  } catch cleanBuffer();
  printf("\nContinua: ");
  scanf("%49[^\n]", palavra);
  string nome = stringInit("Ana");
  obj o = toObj(nome);
  string temp = objGetData(o);
  printfs("\nNome: %S | Size: %lu\n", temp, stringSize(temp));
  stringPrint(toStr(nome));
  printf("\nFim\n");
}