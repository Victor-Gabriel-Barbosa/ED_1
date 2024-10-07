/* Implementando a fila TAD com alocação estática
Nesta atribuição, você implementará uma Fila TAD com alocação estática. Isso significa que você criará uma estrutura de fila e usará a alocação de memória estática para gerenciar os elementos da fila.

Escrevendo um programa para manipulação de filas
Sua tarefa é escrever um programa que usa duas filas, F1 e F2, ambas contendo valores inteiros, e criar uma terceira fila, F, que contém elementos de F1 e F2 com base no maior valor.

Movendo elementos para a nova fila
Para conseguir isso, você comparará os elementos no início de F1 e F2 e, em seguida, moverá o valor maior para a nova fila, F. Esse processo continuará até que F1 e F2 estejam vazios.

Imprimindo as filas
Você deve imprimir as filas originais F1 e F2, bem como a fila F resultante.

Certifique-se de seguir a implementação da Fila do TAD e o processo de movimentação do elemento, conforme descrito acima. Boa sorte! */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fila_estatica.h"
#include "cores.h"
 
int main() {
  srand(time(NULL));
  Fila *F1 = filaCria();
  Fila *F2 = filaCria();
  Fila *F = filaCria();

  for (int i = 0; i < MAX / 2; i++) {
    F1 = filaInsere(F1, (rand() % 100));
    F2 = filaInsere(F2, (rand() % 100));
  }
  printf(C_FMT(C_MAGENTA, "FILA 1: "));
  filaExibe(F1);
  printf(C_FMT(C_VERDE, "FILA 2: "));
  filaExibe(F2);
  F = filaInsereMaior(F1, F2);
  printf(C_FMT(C_CIANO, "FILA RESULTANTE: "));
  filaExibe(F);

  F1 = filaLibera(F1);
  F2 = filaLibera(F2);
  F = filaLibera(F);
  return 0;
}