#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "all_headers.h"

int main() {
  List *mylist = newList();
  insertEndList(mylist, 1);
  insertEndList(mylist, 2);
  insertEndList(mylist, 3);
  printsf("%L\n", mylist);  
  destroyList(mylist);
  String nome = inputString();
  printsf("%S%d\n", nome, sizeString(nome));
  String nomes = initString("Ana Maria Mara Vania");
  printsf("%S%d\n", nomes, sizeString(nomes));
  String *tokens = splitString(&nomes, " ");
  for (int i = 0; tokens[i].data != NULL; i++) {
    printsf(C_MAGENTA "%s" C_RESET, tokens[i]);
  }
  for (int i = 0; tokens[i].data != NULL; i++) {
    destroyString(&tokens[i]);
  }
  free(tokens);
  String teste = newString();
  char *sobrenome = "Clara";
  snprintsf(&teste, "1 %s 3.1", sobrenome);
  printsf(C_GREEN "%S" C_RESET, teste);
  destroyString(&teste);
  return 0;
}  