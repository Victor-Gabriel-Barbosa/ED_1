#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "cores.h"
#include "utils.h"
#include "lladae2_cocktail_sort.h"

#define sizeofvet(vet) (sizeof(vet) / sizeof((vet)[0]))

int main() {
  cls();
  printArquivo("arte.txt", C_MAGENTA);
  srand(time(NULL));  
  clock_t inicio, fim;
  int i, qtd_l = intervalo("a quantidade de listas p/ testar...", 1, 5);
  int qtd_n = potencia(10, intervalo("a base [10^n] p/ testar...", 0, 6)); 
  int prev = !simOuNao("alterar o nome dos arquivos");
  double tempo[qtd_l];
  char *nome_arquivos[] = {prev ? "base_dados.csv" : arquivoNome("base"), 
                           prev ? "lista_desordenada.csv" : arquivoNome("lista desordenada"), 
                           prev ? "lista_ordenada.csv" : arquivoNome("lista ordenada"),
                           prev ? "lista_mesclada.csv" : arquivoNome("lista mesclada")}; 
  Lista *listas[qtd_l], *mesclada;

  for (i = 0; i < sizeofvet(nome_arquivos); i++) { // Exclui todos os arquivos com nome repetido
    arquivoExclui(nome_arquivos[i]);
  }

  arquivoAleatoriza(nome_arquivos[0], 1, 99999, qtd_n); // Cria um arquivo com a base de dados de teste

  for (i = 0; i < qtd_l; i++) { // Inicializa cada uma das listas
   listas[i] = listaCria();
  }
  mesclada = listaCria(); // Inicializa a lista mesclada

  for (i = 0; i < qtd_l; i++) { // Percorre o vetor de listas e carrega as informações da base de dados
    listas[i] = arquivoCarrega(listas[i], nome_arquivos[0], qtd_n);
  }

  for (i = 0; i < qtd_l; i++) { // Salva as listas em arquivos
    arquivoSalva(listas[i], nome_arquivos[1]);
  }
   
  /* 
  for (i = 0; i < qtd_l; i++) { // Mostra os elementos de cada lista
    printf("\n\nLista %soriginal%s(%d)%s[%d]%s:\n", C_VERD, C_MAGENTA, i + 1, C_AMARELO, listaSize(listas[i]), C_RESET);
    listaImprime(listas[i]);
  } 
  */

  for (i = 0; i < qtd_l; i++) { // Ordena cada uma das listas usando o Cocktail Sort e salva o tempo gasto
    printf("\n%sOrdenando%s a lista%s(%d)%s...\n", C_AZUL, C_RESET, C_MAGENTA, i + 1, C_RESET);
    inicio = clock(); // Pega o tempo inicial
    listas[i] = listaCocktailSort(listas[i]); // Ordena as listas
    fim = clock(); // Pega o tempo final
    tempo[i] = (double) (fim - inicio) / CLOCKS_PER_SEC; // Calcula o tempo gasto
  }

  /* 
  for (i = 0; i < qtd_l; i++) { // Mostra os elementos de cada lista depois de ordenar
    printf("\n\nLista %sordenada%s(%d)%s[%d]%s:\n", C_AZUL, C_MAGENTA, i + 1, C_AMARELO, listaSize(listas[i]), C_RESET);
    listaImprime(listas[i]);
  } 
  */

  printf("\n%sMesclando%s listas...\n", C_AZUL, C_RESET);
  for (i = 0; i < qtd_l; i++) { // Mescla todas as listas
    mesclada = listaMescla(mesclada, listas[i]);
  } 

  /*
  printf("\nLista %sresultante%s[Tam.:%d]%s:\n", C_AZUL, C_AMARELO, listaSize(mesclada), C_RESET);
  listaImprime(mesclada); 
  */

  for (i = 0; i < qtd_l; i++) { // Mostra o tempo p/ ordenar cada uma das listas
    printf("\nTempo p/ %sordenar%s a lista%s(%d)%s: %s%.4f%s segundos\n", C_AZUL, C_RESET, C_MAGENTA, i + 1, C_RESET, C_AMARELO, tempo[i], C_RESET);
  }

  for (i = 0; i < qtd_l; i++) { // Salva as listas ordenadas em arquivos
    arquivoSalva(listas[i], nome_arquivos[2]);
  }
  arquivoSalva(mesclada, nome_arquivos[3]);

  for (i = 0; i < qtd_l; i++) { // Libera a memória de todas as listas
    listas[i] = listaLibera(listas[i]);
  }
  mesclada = listaLibera(mesclada); // Libera a memória da lista mesclada

  limpaTela("Aperte " C_FMT(C_MAGENTA, "[ENTER]")  " p/ fechar...");
  return 0;
}