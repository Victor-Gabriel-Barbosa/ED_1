#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "cores.h"
#include "pilha_estatica.h"

int main() {
  PilhaEst *palavra;
  size_t tam = 0; 
  char *token, *frase = NULL;
  printf("Digite uma frase: ");
  getline(&frase, &tam, stdin);
  token = strtok(frase, " \n");
  while (token != NULL) {
    palavra = pilhaCriaEst();
    for (size_t i = 0; i < strlen(token); i++) {
      palavra = pilhaInsereEst(palavra, token[i]);
    }
    printf("A palavra: '%s' ", token);
    if (pilhaPalinEst(palavra, token)) printf(C_FMT(C_VERDE, "é um palíndromo!\n"));
    else printf(C_FMT(C_VERMELHO, "não é um palíndromo!\n"));
    token = strtok(NULL, " \n");
    palavra = pilhaLiberaEst(palavra);
  }
  palavra = pilhaLiberaEst(palavra);
  free(frase);
  return 0;
}