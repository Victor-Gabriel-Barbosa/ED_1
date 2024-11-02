#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore.h"
#include "cores.h"

void limpaBuffer() {
  char c;
  while((c = getchar()) != '\n' && c != EOF);
}

#define timer(func)                                           \
  ({                                                          \
    clock_t inicio, fim;                                      \
    inicio = clock();                                         \
    if (inicio == (clock_t)-1) {                              \
      perror("Erro ao iniciar o temporizador");               \
    }                                                         \
    func;                                                     \
    fim = clock();                                            \
    if (fim == (clock_t)-1) {                                 \
      perror("Erro ao parar o temporizador");                 \
    }                                                         \
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC; \
    printf("\nTempo de execução: %g segundos\n", tempo);        \
    tempo;                                                    \
  })

int main() {
  srand(time(NULL));
  Arvore arvore = arvoreCria();
  int qtd, busca;

  printf(f(BOLD UNDERLINE CYAN, "TESTE ÁRVORE (ABP)\n"));

  printf(f(BOLD YELLOW, "Digite a quantidade de elementos: "));
  scanf("%d", &qtd);
  limpaBuffer();
  printf(f(BOLD UNDERLINE MAGENTA, "\nInserção de elementos\n"));
  timer(for(int i = 0; i < qtd; i++) arvore = arvoreInsere(arvore, rand() % 100););

  printf(f(BOLD MAGENTA, "\nÁrvore em ordem crescente:\n"));
  timer(arvoreExibeEmOrdem(arvore););

  printf(f(BOLD UNDERLINE MAGENTA, "\nBusca de um elemento\n"));
  printf(f(BOLD YELLOW, "Digite o valor para buscar: "));
  scanf("%d", &busca);
  limpaBuffer();
  timer(
    if(arvoreBusca(arvore, busca) != NULL) printf(f(BOLD BLUE, "\nValor %d encontrado!\n"), busca);
    else printf(f(BOLD RED, "\nValor %d não encontrado!\n"), busca);
  );

  printf(f(BOLD UNDERLINE MAGENTA, "\nRemoção de um elemento\n"));
  printf(f(BOLD YELLOW,"Digite o valor para remover: "));
  scanf("%d", &busca);
  limpaBuffer();
  timer(arvore = arvoreRemove(arvore, busca););
  printf(f(BOLD UNDERLINE MAGENTA, "\nÁrvore em ordem após remover o elemento %d:\n"), busca);
  arvoreExibeEmOrdem(arvore);

  printf(f(BOLD UNDERLINE MAGENTA, "\n\nDados da árvore\n"));
  printf(f(BOLD GREEN, "Altura da árvore: %d"), arvoreAltura(arvore));
  printf(f(BOLD GREEN, "\nQuantidade total de nós da árvore: %d"), arvoreContaNos(arvore));
  printf(f(BOLD GREEN, "\nQuantidade de nós folhas da árvore: %d"), arvoreContaFolhas(arvore));
  printf(f(BOLD GREEN, "\nQuantidade de galhos da árvore: %d"), arvoreContaGalhos(arvore));
  printf(f(BOLD GREEN, "\nMaior nó da árvore: %d"), arvoreMaior(arvore));

  printf(f(BOLD UNDERLINE MAGENTA, "\n\nÁrvore espelhada\n"));
  timer(arvoreEspelho(arvore););
  arvoreExibeEmOrdem(arvore);
  arvoreExibeEmOrdem(arvore);

  printf(f(BOLD UNDERLINE MAGENTA, "\n\nÁrvore libera memória\n"));
  timer(arvore = arvoreLibera(arvore););
  printf(f(BOLD GREEN, "Árvore liberada com sucesso!\n"));

  printf(f(BOLD UNDERLINE CYAN, "\nFIM DO PROGRAMA!\n"));
  return 0;
}