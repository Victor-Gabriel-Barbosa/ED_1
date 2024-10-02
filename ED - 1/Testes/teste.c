#include <stdio.h>
#include "include/libv.h"

int main() {
  String nome = inputString();
  printsf("Nome: %S\n", nome);
  destroyString(&nome);
  return 0;  // Programa termina aqui
}