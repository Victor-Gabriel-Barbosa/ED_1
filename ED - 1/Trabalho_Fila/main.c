#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "utils.h"
#include "cores.h"
#include "fila_encadeada.h"
#include "fila_estatica.h"

int main() {
  srand(time(NULL));
  do { 
    /****************************************** Cria as variáveis ******************************************/
    limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ iniciar...");
    printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[INÍCIO]\n"));
    clock_t inicio, fim;
    int i, j;
    Planeta temp;
    int qtd_l = escolheInt("Digite a " C_FMT(C_NEGRITO C_LARANJA, "quantidade de filas") " p/ testar", 1, 9);
    int qtd_n = escolheInt("Digite a " C_FMT(C_NEGRITO C_LARANJA, "quantidade de planetas") " p/ testar", 1, 999999);
    /*-----------------------------------------------------------------------------------------------------*/
    Fila_E *filas_e[qtd_l];
    Fila_S *filas_s[qtd_l];
    for (i = 0; i < qtd_l; i++) { // Cria cada uma das filas
      filas_e[i] = filaCria_E();
      filas_s[i] = filaCria_S();
    }
    /*******************************************************************************************************/

    /****************************************** Teste de Inserção ******************************************/
    limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ continuar...");
    printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[FILAS - INSERIR]\n")); 
    /*-----------------------------------------------------------------------------------------------------*/
    inicio = clock();
    for (i = 0; i < qtd_l; i++) { // Percorre o vetor de filas
      for (j = 0; j < qtd_n; j++) { // Insere todos os números
        filas_e[i] = filaInsere_E(filas_e[i], planetaAleatoriza(j + 1));
      }
    }
    fim = clock(); 
    /*-----------------------------------------------------------------------------------------------------*/
    printf("\nTempo de execução " C_FMT(C_NEGRITO C_VERDE, "inserção (fila encadeada): %.15lf clocks\n"), (double)(fim - inicio));
    /*-----------------------------------------------------------------------------------------------------*/
    inicio = clock();
    for (i = 0; i < qtd_l; i++) { // Percorre o vetor de filas
      for (j = 0; j < qtd_n; j++) { // Insere todos os números
        filas_s[i] = filaInsere_S(filas_s[i], planetaAleatoriza(j + 1));
      }
    }
    fim = clock();
    /*-----------------------------------------------------------------------------------------------------*/
    printf("\nTempo de execução " C_FMT(C_NEGRITO C_AZUL, "inserção (fila estática): %.15lf clocks\n"), (double)(fim - inicio));
    /*******************************************************************************************************/

    /****************************************** Teste de Exibição ******************************************/
    limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ continuar...");
    printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[FILAS - EXIBIR]\n")); 
    /*-----------------------------------------------------------------------------------------------------*/
    if (simOuNao("exibir as filas encadeadas")) { // Confirma se o usuário deseja exibir as filas
      inicio = clock();
      for (i = 0; i < qtd_l; i++) { // Mostra os elementos de cada fila
        printf("\nFila %sencadeada %s(%d)%s[%d]%s: ", C_NEGRITO C_VERDE, C_MAGENTA, i + 1, C_LARANJA, filaTamanho_E(filas_e[i]), C_RESET);
        filaExibe_E(filas_e[i]);
      } 
      fim = clock();
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_VERDE, "exibição (fila encadeada): %.15lf clocks\n"), (double)(fim - inicio));
    }
    /*-----------------------------------------------------------------------------------------------------*/
    limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ continuar...");
    printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[FILAS - EXIBIR]\n")); 
    /*-----------------------------------------------------------------------------------------------------*/
    if (simOuNao("exibir as filas estáticas")) { // Confirma se o usuário deseja exibir as filas
      inicio = clock();
      for (i = 0; i < qtd_l; i++) { // Mostra os elementos de cada fila
        printf("\nFila %sestática %s(%d)%s[%d]%s: ", C_NEGRITO C_AZUL, C_MAGENTA, i + 1, C_LARANJA, filaTamanho_S(filas_s[i]), C_RESET);
        filaExibe_S(filas_s[i]);
      }
      fim = clock();
      printf("\nTempo de execução " C_FMT(C_NEGRITO C_AZUL, "exibição (fila estática): %.15lf clocks\n"), (double)(fim - inicio));
    }
    /*******************************************************************************************************/

    /****************************************** Teste de Remoção *******************************************/
    limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ continuar...");
    printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[FILAS - REMOVER]\n")); 
    /*-----------------------------------------------------------------------------------------------------*/
    inicio = clock();
    // printf(C_FMT(C_NEGRITO C_VERMELHO, "\nElementos removidos: "));
    for (i = 0; i < qtd_l; i++) { // Percorre o vetor de filas
      for (j = 0; j < qtd_n; j++) { // Remove cada um dos elementos
        filas_e[i] = filaRemove_E(filas_e[i], &temp);
        // planetaExibe(temp);
      }
    }
    fim = clock();
    /*-----------------------------------------------------------------------------------------------------*/
    printf("\nTempo de execução " C_FMT(C_NEGRITO C_VERDE, "remoção (fila encadeada): %.15lf clocks\n"), (double)(fim - inicio));
    /*-----------------------------------------------------------------------------------------------------*/
    inicio = clock();
    // printf(C_FMT(C_NEGRITO C_VERMELHO, "\nElementos removidos: "));
    for (i = 0; i < qtd_l; i++) { // Percorre o vetor de filas
      for (j = 0; j < qtd_n; j++) { // Remove cada um dos elementos
        filas_s[i] = filaRemove_S(filas_s[i], &temp);
        // planetaExibe(temp);
      }
    }
    fim = clock();
    /*-----------------------------------------------------------------------------------------------------*/
    printf("\nTempo de execução " C_FMT(C_NEGRITO C_AZUL, "remoção (fila estática): %.15lf clocks\n"), (double)(fim - inicio));
    /*******************************************************************************************************/

    /****************************************** Teste de Execução ******************************************/
    limpaTela("Aperte " C_FMT(C_NEGRITO C_AZUL, "[ENTER]") " p/ continuar...");
    printf(C_FMT(C_NEGRITO C_SUBLINHADO C_AZUL, "\n[FILAS - TERMINAR]\n")); 
    for (i = 0; i < qtd_l; i++) { // Mostra os elementos de cada fila
      printf("\nFila %sencadeada %s(%d)%s[%d]%s: ", C_NEGRITO C_VERDE, C_MAGENTA, i + 1, C_LARANJA, filaTamanho_E(filas_e[i]), C_RESET);
      if (simOuNao("exibir essa fila encadeada")) filaExibe_E(filas_e[i]);
      printf("\nFila %sestática %s(%d)%s[%d]%s: ", C_NEGRITO C_AZUL, C_MAGENTA, i + 1, C_LARANJA, filaTamanho_S(filas_s[i]), C_RESET);
      if (simOuNao("exibir essa fila estática")) filaExibe_S(filas_s[i]);
    } 
    /*******************************************************************************************************/

    /****************************************** Libera as Filas ********************************************/
    for (i = 0; i < qtd_l; i++) { // Percorre o vetor de 
      filaLibera_E(filas_e[i]);
      filaLibera_S(filas_s[i]);
    }
    /*******************************************************************************************************/
  } while (simOuNao("testar novamente"));
  limpaTela("Aperte " C_FMT(C_NEGRITO C_VERMELHO, "[ENTER]") " p/ terminar...");
  return 0;
}