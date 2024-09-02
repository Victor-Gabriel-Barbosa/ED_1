#include "lista_encadeada.h"
#include <stdio.h>

int main() {
  Lista *lista = cria_lista();
  menu(lista);
  libera_lista(lista);
  limpa_tela();
  printf("\n\033[38;5;51m[Obrigado por usar o meu programa :)]\033[0m\n");
  return 0;
}