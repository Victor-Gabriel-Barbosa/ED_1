/* 
Considere o seguinte jogo:
N pessoas identificadas por um nome e um número inteiro estão sentadas em círculo, organizadas  aleatoriamente.
Um número é sorteado no intervalo [1,N].
A pessoa associada a este número sai do círculo.
Um novo número é sorteado.
Contando da pessoa seguinte àquela que saiu, a enésima pessoa sai do círculo.
O sorteio continua até que reste apenas uma pessoa.

Faça um programa que, usando a lladaec.h, forme o círculo de pessoas, lembrando que são N pessoas sentadas aleatoriamente.
Sorteie, a cada iteração um número, e retire uma pessoa do círculo, conforme as regras do jogo.
A cada saída, grave em disco a posição e o número de quem saiu.
No final do jogo, grave o nome  e o número da pessoa que sobrou e indique seu prêmio ou castigo.
*/

#include "lladaec.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main() {
  Lista* josephus = Cria_lista();
  Pessoas temp;
  int N;
  char nome[50];
  printf("Digite o número de pessoas: ");
  scanf("%d", &N);
  Limpa_buffer();
  srand(time(NULL));
  for (int i = 1; i <= N; i++) {
    printf("Digite o nome da pessoa %d: ", i);
    scanf("%49[^\n]", nome);
    Limpa_buffer(); 
    strcpy(temp.nome, nome);
    temp.num = i;
    josephus = Insere_elem(josephus, temp);
  }
  while (Tamanho_lista(josephus) > 1) {
    int k = (rand() % Tamanho_lista(josephus)) + 1;
    Lista* aux = josephus;
    for (int i = 1; i < k; i++) {
      aux = aux->prox;
      if (aux == NULL) aux = josephus;
    }
    Pessoas saida = aux->dados;
    printf("\nSaída: %s (%d)\n", saida.nome, saida.num);
    Grava_arquivo(saida, "saida.txt");
    josephus = Remove_elem(josephus, saida);
  }
  Pessoas ultimo = josephus->dados;
  printf("\nÚltimo(a) restante: %s (%d)\n", ultimo.nome, ultimo.num);
  Grava_ganhador(ultimo, "ultimo.txt");
  josephus = Libera_lista(josephus);
  return 0;
}