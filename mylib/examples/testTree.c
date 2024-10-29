#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"
#include "utils.h"
#include "colors.h"

int main() {
  srand(time(NULL));
  char *nomes[] = {
    "Alice", "Bob", "Carol", "David", "Eve", "Frank",
    "Grace", "Harry", "Ivy", "Jack", "Kate", "Lisa"
  };
  tree arvore = treeNew();
  foreach(nome, nomes) treeAdd(arvore, *nome);
  printfs(f(GREEN, "Arvore: %A"), arvore);
  treeDelete(arvore, "Alice");
  printfs(f(RED, "\nArvore após remover Alice: %A"), arvore);
  arvore = treeInvert(arvore);
  printfs(f(BLUE, "\nArvore invertida: %A"), arvore);
  print(toStr("\nPrint: "), toStr(arvore));
  arvore = treeDestroy(arvore);
  return 0;
}