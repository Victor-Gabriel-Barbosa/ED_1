/* Júlia, uma funcionária que trabalha em uma bilheteria de cinema, diz que sua rotina está
sendo muito cansativa devido sua divisão de faculdade de computação e trabalho. Cansada de
fazer a venda de ingressos manualmente, ela decidiu criar um programa que faça tudo
automaticamente sem que ela precise vender um a um, porém, ela precisa também de sua
ajuda para conseguir montar o sistema. Ajude Júlia a implementar lista duplamente
encadeada. Você deverá implementar duas listas encadeada, uma para os ingressos vendidos e
outra para os ingressos disponíveis. Seu programa deverá permitir:
 Vender um ingresso a um filme
 Cancelar um ingresso
 Listar todos os ingressos disponíveis para um filme específico
 Exibir todos os ingressos vendidos em ordem de compra
*/

#include <stdio.h>
#include <stdlib.h>
#include "lladae2d.h"

int main() {
  Lista* vendidos = Cria_lista();
  Lista* disponiveis = Cria_lista();

  Ingresso ingresso = {1, 5, "Avengers"};
  disponiveis = Insere_elem(disponiveis, ingresso);
  Ingresso ingresso2 = {2, 11, "Filme 2"};
  disponiveis = Insere_elem(disponiveis, ingresso2);

  
  int opcao, ID_filme, loop = 1;
  while (loop) {
    Limpa_tela("Aperte [ENTER] para voltar ao menu...");
    if ((opcao = Escolha_menu()) == 0) {
      printf("Saindo...\n");
      loop = 0;
    } else if (opcao == 1) {
      printf("ID do filme: ");
      scanf("%d", &ID_filme);
      Limpa_buffer();
      vendidos = Vender_ingresso(vendidos, disponiveis, ID_filme);
      printf("\n");
      Listar_ingressos(vendidos);
      printf("\n");
      Listar_ingressos(disponiveis);
      printf("\n");
    } else if (opcao == 2) {
      printf("ID do ingresso: ");
      scanf("%d", &ID_filme);
      Limpa_buffer();
      disponiveis = Cancelar_venda(vendidos, disponiveis, ID_filme);
      printf("\n");
      Listar_ingressos(vendidos);
      printf("\n");
      Listar_ingressos(disponiveis);
      printf("\n");
    } else if (opcao == 3) {
      Listar_ingressos(disponiveis);
      printf("\n");
    } else if (opcao == 4) {
      Listar_ingressos(vendidos);
      printf("\n");
    } else {
      printf("Opção inválida!\n");
    }
  }
  vendidos = Libera_lista(vendidos);
  disponiveis = Libera_lista(disponiveis);
}