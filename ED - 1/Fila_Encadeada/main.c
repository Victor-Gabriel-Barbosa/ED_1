/* Programando Fila
Nesta atribuição, você escreverá um programa para manipular uma fila com alocação dinâmica. Siga as etapas abaixo para concluir a tarefa:

Entrada:
Solicite que o usuário preencha uma linha F com números inteiros.
Separação de Valores:

Mova todos os valores em F para as seguintes filas com base em seus múltiplos:
Os valores múltiplos de 3 devem ser movidos para a fila F3.
Valores múltiplos de 2 devem ser movidos para a fila F2.
Os valores restantes devem ser movidos para a fila F4.
Nota: Se um número for um múltiplo de 2 e 3, ele deve ser inserido em F2 e F3.
Exibição:

Exibir a fila original F.
No final do processamento, exiba o conteúdo de F, F2, F3 e F4.
Certifique-se de implementar o programa para executar as operações especificadas com precisão. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cores.h"
#include "fila_encadeada.h"

int main() {
  Fila *F2 = filaCria();
  Fila *F3 = filaCria();
  Fila *F4 = filaCria();
  Fila *F = filaCria();
  char *linha = NULL;
  int num;
  size_t tam = 0;
  
  printf("\nInsira uma " C_FMT(C_MAGENTA, "linha de números") " inteiros separados por espaço:\n");
  getline(&linha, &tam, stdin);
  char *token = strtok(linha, " \n"); 
  while (token != NULL) { // Converte todos as strings separadas por espaço ou '\n' p/ int
    int num = atoi(token);
    filaInsere(F, num); 
    token = strtok(NULL, " \n"); 
  }
  free(linha);

  printf(C_FMT(C_VERDE, "\nFila original F (antes):\n"));
  filaExibe(F);

  while (!filaVazia(F)) { // Move todos os valores de F p/ as listas correspondentes
    filaRemove(F, &num);
    if (num % 2 == 0 && num % 3 == 0) filaInsere(F2, num); 
    else if (num % 2 == 0) filaInsere(F2, num); 
    else if (num % 3 == 0) filaInsere(F3, num);
    else filaInsere(F4, num);
  }

  printf(C_FMT(C_VERDE, "\nFila original F (depois):\n"));
  filaExibe(F);
  printf(C_FMT(C_AZUL, "\nFila F2 (múltiplos de 2):\n"));
  filaExibe(F2);
  printf(C_FMT(C_ROXO, "\nFila F3 (múltiplos de 3):\n"));
  filaExibe(F3);
  printf(C_FMT(C_CIANO, "\nFila F4 (outros valores):\n"));
  filaExibe(F4);

  F = filaLibera(F);
  F2 = filaLibera(F2);
  F3 = filaLibera(F3);
  F4 = filaLibera(F4);
  return 0;
}
