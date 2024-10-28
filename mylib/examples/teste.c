#include <stdio.h>
#include "list.h"
#include "stringlib.h"
#include "utils.h"

int main() {
  printf("\nInicio\n");
  string nome = stringInit("Ana");
  obj o = toObj(nome);
  string temp = objGetData(o);
  printfs("\nNome: %S | Size: %lu\n", temp, stringSize(temp));
  stringPrint(toStr(nome));
  printf("\nFim\n");
}