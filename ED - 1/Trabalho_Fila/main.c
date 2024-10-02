#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "cores.h"
#include "fila_encadeada.h"
#include "fila_estatica.h"

int main() {
  limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ iniciar...");
  int i, j, t, qtd_f, qtd_p, qtd_t;
  long int tempoEnc[3], tempoEst[3];
  char *nomes_a[2];
  FilaEst **filasEst;
  FilaEnc **filasEnc;
  Planeta temp, estrela; 
  srand(time(NULL));
  arqvPrint("arte.txt", C_NEGRITO C_MAGENTA);
  do { 
    nomes_a[0] = arqvNome("filaEnc_tempo.csv");
    nomes_a[1] = arqvNome("filaEst_tempo.csv");
    for (i = 0; i < 3; i++) { // Zera os contadores de tempo
      tempoEnc[i] = 0;
      tempoEst[i] = 0;
    }
    limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ continuar...");
    printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[INÍCIO]\n"));
    qtd_f = escolheInt("Digite a " C_FMT(C_NEGRITO C_LARANJA, "quantidade de sistemas solares (2x)"), 1, 9);
    qtd_p = escolheInt("Digite a " C_FMT(C_NEGRITO C_LARANJA, "quantidade de planetas"), 1, 999999);
    qtd_t = escolheInt("Digite a " C_FMT(C_NEGRITO C_LARANJA, "quantidade de testes"), 1, 9);
    for (t = 0; t < qtd_t; t++) { // Faz os testes
      filasEst = verAlloc((FilaEst **) malloc(qtd_f * sizeof(FilaEst *)));
      filasEnc = verAlloc((FilaEnc **) malloc(qtd_f * sizeof(FilaEnc *)));
      for (i = 0; i < qtd_f; i++) { // Cria as filas estáticas e encadeadas
        filasEst[i] = filaCriaEst();
        filasEnc[i] = filaCriaEnc();
      }
      for (i = 0; i < qtd_f; i++) { // Insere planetas nas filas estáticas e encadeadas
        tempoEst[0] += tempoInsereFilaEst(filasEst[i], qtd_p);
        tempoEnc[0] += tempoInsereFilaEnc(filasEnc[i], qtd_p); 
      }
      for (i = 0; i < qtd_f; i++) { // Exibe os planetas das filas estáticas e encadeadas
        tempoEst[1] += tempoExibeFilaEst(filasEst[i], qtd_p);
        tempoEnc[1] += tempoExibeFilaEnc(filasEnc[i], qtd_p); 
      }
      for (i = 0; i < qtd_f; i++) { // Remove os planetas das filas estáticas e encadeadas
        tempoEst[2] += tempoRemoveFilaEst(filasEst[i], qtd_p);
        tempoEnc[2] += tempoRemoveFilaEnc(filasEnc[i], qtd_p); 
      } 
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_AZUL, "inserção (fila estática): %ld clocks\n"), tempoEst[0]);
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_VERDE, "inserção (fila encadeada): %ld clocks\n"), tempoEnc[0]); 
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_AZUL, "listagem (fila estática): %ld clocks\n"), tempoEst[1]);
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_VERDE, "listagem (fila encadeada): %ld clocks\n"), tempoEnc[1]); 
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_AZUL, "remoção (fila estática): %ld clocks\n"), tempoEst[2]);
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_VERDE, "remoção (fila encadeada): %ld clocks\n"), tempoEnc[2]); 
      if (simOuNao("salvar o tempo das listas encadeadas")) arqvSalvaTempo(nomes_a[0], t + 1, qtd_p, tempoEnc);
      if (simOuNao("salvar o tempo das listas estáticas")) arqvSalvaTempo(nomes_a[1], t + 1, qtd_p, tempoEst);
      for (i = 0; i < qtd_f; i++) { // Libera a memória alocada p/ as filas estáticas e encadeadas
        filaLiberaEst(filasEst[i]);
        filaLiberaEnc(filasEnc[i]);
      }
      free(filasEst);
      free(filasEnc);
    }
  } while (simOuNao("testar novamente"));
  limpaTela("Aperte " C_FMT(C_NEGRITO C_VERMELHO, "[ENTER]") " p/ terminar...");
  return 0;
}