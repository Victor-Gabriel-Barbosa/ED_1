#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore.h"

int main() {
  srand(time(NULL));
  Arvore arv = arvoreCria();
  for (int i = 0; i < 100; i++) {
    int num = rand() % 1000;
    arv = arvoreInsere(arv, num);
  }
  printf("Arvore em ordem crescente:\n");
  arvoreExibe(arv, 0);
  arv = arvoreLibera(arv);
}