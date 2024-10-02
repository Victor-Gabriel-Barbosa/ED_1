#include <stdio.h>
#include <c_plus.h>

int main() {
  String nome = inputString();
  printsf("%S", nome);
  destroyString(&nome);
  return 0;
}