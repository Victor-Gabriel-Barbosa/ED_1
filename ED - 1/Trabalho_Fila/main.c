#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "cores.h"
#include "fila_encadeada.h"
#include "fila_estatica.h"

int main() {
  srand(time(NULL));
  cls();
  printArquivo("arte.txt", C_NEGRITO C_MAGENTA);
  do { 
    /****************************************** Cria as variáveis ******************************************/
    limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ iniciar...");
    printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[INÍCIO]\n"));
    clock_t inicio, fim, tempoEnc[3], tempoEst[3];
    int i, j;
    Planeta temp, estrela;
    int qtd_f = escolheInt("Digite a " C_FMT(C_NEGRITO C_LARANJA, "quantidade de sistemas solares"), 1, 9);
    int qtd_p = escolheInt("Digite a " C_FMT(C_NEGRITO C_LARANJA, "quantidade de planetas"), 1, 999999);
    /*******************************************************************************************************/

    /****************************************** Executa os testes ******************************************/
    int num_testes = escolheInt("Digite a " C_FMT(C_NEGRITO C_LARANJA, "quantidade de testes"), 1, 9);
    /*-----------------------------------------------------------------------------------------------------*/
    for (int b = 0; b < num_testes; b++) {
      FilaEnc *filasEnc[qtd_f];
      FilaEst *filasEst[qtd_f];
      for (i = 0; i < qtd_f; i++) { // Cria cada uma das filas
        filasEnc[i] = filaCriaEnc();
        filasEst[i] = filaCriaEst();
      }

      /****************************************** Teste de Inserção ******************************************/
      // limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ continuar...");
      printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[FILAS - INSERIR]\n")); 
      /*-----------------------------------------------------------------------------------------------------*/
      inicio = clock();
      for (i = 0; i < qtd_f; i++) { // Percorre o vetor de filas
        for (j = 0; j < qtd_p; j++) { // Insere todos os números
          filasEnc[i] = filaInsereEnc(filasEnc[i], planetaAleatoriza(j + 1));
        }
      }
      fim = clock(); 
      tempoEnc[0] = (fim - inicio);
      /*-----------------------------------------------------------------------------------------------------*/
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_VERDE, "inserção (fila encadeada): %ld clocks\n"), tempoEnc[0]);
      /*-----------------------------------------------------------------------------------------------------*/
      inicio = clock();
      for (i = 0; i < qtd_f; i++) { // Percorre o vetor de filas
        for (j = 0; j < qtd_p; j++) { // Insere todos os números
          filasEst[i] = filaInsereEst(filasEst[i], planetaAleatoriza(j + 1));
        }
      }
      fim = clock();
      tempoEst[0] = (fim - inicio);
      /*-----------------------------------------------------------------------------------------------------*/
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_AZUL, "inserção (fila estática): %ld clocks\n"), tempoEst[0]);
      /*******************************************************************************************************/

      /****************************************** Teste de Exibição ******************************************/
      // limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ continuar...");
      printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[FILAS - EXIBIR]\n")); 
      /*-----------------------------------------------------------------------------------------------------*/
      inicio = clock();
      for (i = 0; i < qtd_f; i++) { // Mostra os elementos de cada fila
        printf("\nFila %sencadeada %s(%d)%s[%d]%s: ", C_NEGRITO C_VERDE, C_MAGENTA, i + 1, C_LARANJA, filaTamanhoEnc(filasEnc[i]), C_RESET);
        filaExibeEnc(filasEnc[i]);
      } 
      fim = clock();
      tempoEnc[1] = (fim - inicio);
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_VERDE, "exibição (fila encadeada): %ld clocks\n"), tempoEnc[1]);
      /*-----------------------------------------------------------------------------------------------------*/
      // limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ continuar...");
      printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[FILAS - EXIBIR]\n")); 
      /*-----------------------------------------------------------------------------------------------------*/
      inicio = clock();
      for (i = 0; i < qtd_f; i++) { // Mostra os elementos de cada fila
        printf("\nFila %sestática %s(%d)%s[%d]%s: ", C_NEGRITO C_AZUL, C_MAGENTA, i + 1, C_LARANJA, filaTamanhoEst(filasEst[i]), C_RESET);
        filaExibeEst(filasEst[i]);
      }
      fim = clock();
      tempoEst[1] = (fim - inicio);
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_AZUL, "exibição (fila estática): %ld clocks\n"), tempoEst[1]);
      /*******************************************************************************************************/

      /****************************************** Teste de Remoção *******************************************/
      // limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ continuar...");
      printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[BIG BANG!]\n")); 
      /*-----------------------------------------------------------------------------------------------------*/
      inicio = clock();
      for (i = 0; i < qtd_f; i++) { // Percorre o vetor de filas
        filaConsultaEnc(filasEnc[i], &estrela);
        for (j = 0; j < qtd_p; j++) { // Remove cada um dos elementos
          filasEnc[i] = filaRemoveEnc(filasEnc[i], &temp);
          estrela = planetaBigBang(temp, estrela);
        }
        printf(C_FMT(C_NEGRITO C_SUBLINHADO C_ROXO, "\n✯ Ganhador ✯\n"));
        planetaExibe(estrela);
      }
      fim = clock();
      tempoEnc[2] = (fim - inicio);
      /*-----------------------------------------------------------------------------------------------------*/
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_VERDE, "remoção (fila encadeada): %ld clocks\n"), tempoEnc[2]);
      /*-----------------------------------------------------------------------------------------------------*/
      inicio = clock();
      for (i = 0; i < qtd_f; i++) { // Percorre o vetor de filas
        filaConsultaEst(filasEst[i], &estrela);
        for (j = 0; j < qtd_p; j++) { // Remove cada um dos elementos
          filasEst[i] = filaRemoveEst(filasEst[i], &temp);
          estrela = planetaBigBang(temp, estrela);
        }
        printf(C_FMT(C_NEGRITO C_SUBLINHADO C_ROXO, "\n✯ Ganhador ✯\n"));
        planetaExibe(estrela);
      }
      fim = clock();
      tempoEst[2] = (fim - inicio);
      /*-----------------------------------------------------------------------------------------------------*/
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_AZUL, "remoção (fila estática): %ld clocks\n"), tempoEst[2]);
      /*******************************************************************************************************/

      /****************************************** Libera as Filas ********************************************/
      for (i = 0; i < qtd_f; i++) { // Percorre o vetor de filas
        filaLiberaEnc(filasEnc[i]);
        filaLiberaEst(filasEst[i]);
      }
      /*******************************************************************************************************/

      /****************************************** Salva os tempos ********************************************/
      arquivoSalva("filaEnc_t.csv", b + 1, qtd_p, tempoEnc);
      arquivoSalva("filaEst_t.csv", b + 1, qtd_p, tempoEst);
      /*******************************************************************************************************/
    }
    /*******************************************************************************************************/

  } while (simOuNao("testar novamente"));
  limpaTela("Aperte " C_FMT(C_NEGRITO C_VERMELHO, "[ENTER]") " p/ terminar...");
  return 0;
}