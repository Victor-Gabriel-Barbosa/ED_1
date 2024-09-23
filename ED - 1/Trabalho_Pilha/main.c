#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "cores.h"
#include "pilha_encadeada.h"
#include "pilha_estatica.h"

int main() {
  srand(time(NULL));
  cls();
  printArquivo("arte.txt", C_NEGRITO C_MAGENTA);
  do {  
    limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ iniciar...");
    printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[INÍCIO]\n"));
    clock_t inicio, fim, tempoEnc[3], tempoEst[3];
    int i, j;
    RPG temp, turno_ganhador;
    int qtd_f = escolheInt("Digite a " C_FMT(C_NEGRITO C_LARANJA, "quantidade de partidas"), 1, 9);
    int qtd_p = escolheInt("Digite a " C_FMT(C_NEGRITO C_LARANJA, "quantidade de turnos"), 1, 999999);
    int qtd_t = escolheInt("Digite a " C_FMT(C_NEGRITO C_LARANJA, "quantidade de testes"), 1, 9);
    for (int b = 0; b < qtd_t; b++) {
      PilhaEnc *pilhasEnc[qtd_f];
      PilhaEst *pilhasEst[qtd_f];
      for (i = 0; i < qtd_f; i++) { // Cria as pilhas encadeadas e estáticas
        pilhasEnc[i] = pilhaCriaEnc();
        pilhasEst[i] = pilhaCriaEst();
      } 
      // limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ continuar...");
      printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[PILHAS - INSERIR]\n")); 
      inicio = clock();
      for (i = 0; i < qtd_f; i++) { // Percorre as pilhas encadeadas
        for (j = 0; j < qtd_p; j++) { // Insere todos os jogos
          pilhasEnc[i] = pilhaInsereEnc(pilhasEnc[i], ((j == 0) ? rpgAleatoriza(j + 1) : rpgBatalha(temp)));
          pilhaConsultaEnc(pilhasEnc[i], &temp);
        }
      }
      fim = clock(); 
      tempoEnc[0] = (fim - inicio);
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_VERDE, "inserção (pilha encadeada): %ld clocks\n"), tempoEnc[0]);
      inicio = clock();
      for (i = 0; i < qtd_f; i++) { // Percorre as pilhas encadeadas
        for (j = 0; j < qtd_p; j++) { // Insere todos os jogos
          pilhasEst[i] = pilhaInsereEst(pilhasEst[i], ((j == 0) ? rpgAleatoriza(j + 1) : rpgBatalha(temp)));
          pilhaConsultaEst(pilhasEst[i], &temp);
        }
      }
      fim = clock();
      tempoEst[0] = (fim - inicio);
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_AZUL, "inserção (pilha estática): %ld clocks\n"), tempoEst[0]);
      // limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ continuar...");
      printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[PILHAS - EXIBIR]\n")); 
      inicio = clock();
      for (i = 0; i < qtd_f; i++) { // Mostra os jogos da pilha encadeada
        printf("\nPilha %sencadeada %s(%d)%s[%d]%s: ", C_NEGRITO C_VERDE, C_MAGENTA, i + 1, C_LARANJA, pilhaTamanhoEnc(pilhasEnc[i]), C_RESET);
        pilhaExibeEnc(pilhasEnc[i]);
      } 
      fim = clock();
      tempoEnc[1] = (fim - inicio);
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_VERDE, "exibição (pilha encadeada): %ld clocks\n"), tempoEnc[1]);
      // limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ continuar...");
      printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[PILHAS - EXIBIR]\n")); 
      inicio = clock();
      for (i = 0; i < qtd_f; i++) { // Mostra os jogos da pilha estática
        printf("\nPilha %sestática %s(%d)%s[%d]%s: ", C_NEGRITO C_AZUL, C_MAGENTA, i + 1, C_LARANJA, pilhaTamanhoEst(pilhasEst[i]), C_RESET);
        pilhaExibeEst(pilhasEst[i]);
      }
      fim = clock();
      tempoEst[1] = (fim - inicio);
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_AZUL, "exibição (pilha estática): %ld clocks\n"), tempoEst[1]);
      // limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ continuar...");
      printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[BATALHA!]\n")); 
      inicio = clock();
      for (i = 0; i < qtd_f; i++) { // Percorre o vetor de pilhas
        pilhaConsultaEnc(pilhasEnc[i], &turno_ganhador);
        for (j = 0; j < qtd_p; j++) { // Remove cada um dos jogos
          pilhasEnc[i] = pilhaRemoveEnc(pilhasEnc[i], &temp);
          if (temp.p1.hp == 0 || temp.p2.hp == 0) turno_ganhador = temp;
        }
        printf(C_FMT(C_NEGRITO C_SUBLINHADO C_ROXO, "\n✯ Turno do Ganhador ✯\n"));
        rpgExibe(turno_ganhador);
      } 
      fim = clock();
      tempoEnc[2] = (fim - inicio);
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_VERDE, "remoção (pilha encadeada): %ld clocks\n"), tempoEnc[2]);
      inicio = clock();
      for (i = 0; i < qtd_f; i++) { // Percorre as pilhas encadeadas
        pilhaConsultaEst(pilhasEst[i], &turno_ganhador);
        for (j = 0; j < qtd_p; j++) { // Remove cada um dos jogos
          pilhasEst[i] = pilhaRemoveEst(pilhasEst[i], &temp);
          if (temp.p1.hp == 0 || temp.p2.hp == 0) turno_ganhador = temp;
        }
        printf(C_FMT(C_NEGRITO C_SUBLINHADO C_ROXO, "\n✯ Turno do Ganhador ✯\n"));
        rpgExibe(turno_ganhador);
      }
      fim = clock(); 
      tempoEst[2] = (fim - inicio);
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_AZUL, "remoção (pilha estática): %ld clocks\n"), tempoEst[2]);
      for (i = 0; i < qtd_f; i++) { // Percorre as pilhas encadeadas e estáticas
        pilhaLiberaEnc(pilhasEnc[i]);
        pilhaLiberaEst(pilhasEst[i]);
      }
      arquivoSalva("pilhaEnc_t.csv", b + 1, qtd_p, tempoEnc);
      arquivoSalva("pilhaEst_t.csv", b + 1, qtd_p, tempoEst);
    }
  } while (simOuNao("testar novamente"));
  limpaTela("Aperte " C_FMT(C_NEGRITO C_VERMELHO, "[ENTER]") " p/ terminar...");
  return 0;
}