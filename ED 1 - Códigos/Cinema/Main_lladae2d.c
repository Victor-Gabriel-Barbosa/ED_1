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

  Ingresso ing1[10] = {
    {1, 1, "Vingadores: Guerra Infinita"},
    {2, 2, "Vingadores: Guerra Infinita"},
    {3, 3, "Vingadores: Guerra Infinita"},
    {4, 4, "Vingadores: Guerra Infinita"},
    {5, 5, "Vingadores: Guerra Infinita"},
    {6, 6, "Vingadores: Guerra Infinita"},
    {7, 7, "Vingadores: Guerra Infinita"},
    {8, 8, "Vingadores: Guerra Infinita"},
    {9, 9, "Vingadores: Guerra Infinita"},
    {10, 10, "Vingadores: Guerra Infinita"}
  };
  Ingresso ing2[10] = {
    {11, 1, "Avengers: Endgame"},
    {12, 2, "Avengers: Endgame"},
    {13, 3, "Avengers: Endgame"},
    {14, 4, "Avengers: Endgame"},
    {15, 5, "Avengers: Endgame"},
    {16, 6, "Avengers: Endgame"},
    {17, 7, "Avengers: Endgame"},
    {18, 8, "Avengers: Endgame"},
    {19, 9, "Avengers: Endgame"},
    {20, 10, "Avengers: Endgame"}
  };
  
  for (int i = 0; i < 10; i++) {
    disponiveis = Insere_elem(disponiveis, ing1[i]);
    disponiveis = Insere_elem(disponiveis, ing2[i]);
  }
  
  int opcao, loop = 1, max = 10;
  while (loop) { // Menu principal
    if ((opcao = Escolha_menu()) == 0) {
      Limpa_tela("Aperte [ENTER] para continuar...");
      printf("\n%s[Saindo...]%s\n", amar, rset);
      loop = 0;
    } else if (opcao == 1) { // Vender ingresso
      if (!E_vazia(disponiveis)) {
        if (Tamanho_lista(vendidos) < max) {
          Limpa_tela("Aperte [ENTER] para continuar...");
          printf("\n%s[Ingressos Disponíveis]%s\n", verd, rset);
          Listar_ingressos(disponiveis);
          if (Vender_ingresso(&disponiveis, &vendidos, Escolhe_ID())) { // Verifica se o ingresso foi vendido com sucesso
            printf("\n%s[Ingresso vendido com sucesso!]%s\n", azul, rset);
            Limpa_tela("Aperte [ENTER] para continuar...");
            printf("\n%s[Ingressos Disponíveis]%s\n", verd, rset);
            Listar_ingressos(disponiveis);
            printf("\n%s[Ingressos Vendidos]%s\n", mage, rset);
            Listar_ingressos(vendidos);
          } else {
            printf("\n%s[Ingresso não encontrado!]%s\n", verm, rset);
          }
        } else {
          printf("\n%s[Limite de ingressos atingido!]%s\n", verm, rset);
        }
      } else {
        printf("\n%s[Nenhum ingresso disponível!]%s\n", verm, rset);
      }
    } else if (opcao == 2) { // Cancelar venda
      if (!E_vazia(vendidos)) {
        Limpa_tela("Aperte [ENTER] para continuar...");
        printf("\n%s[Ingressos Vendidos]%s\n", mage, rset);
        Listar_ingressos(vendidos);
        if (Cancelar_venda(&disponiveis, &vendidos, Escolhe_ID())) { // Verifica se o ingresso foi cancelado com sucesso
          printf("\n%s[Ingresso cancelado com sucesso!]%s\n", azul, rset);
          Limpa_tela("Aperte [ENTER] para continuar...");
          printf("\n%s[Ingressos Disponíveis]%s\n", verd, rset);
          Listar_ingressos(disponiveis);
          printf("\n%s[Ingressos Vendidos]%s\n", mage, rset);
          Listar_ingressos(vendidos);
        } else {
          printf("\n%s[Ingresso não encontrado!]%s\n", verm, rset);
        }
      } else {
        printf("\n%s[Nenhum ingresso vendido!]%s\n", verm, rset);
      }
    } else if (opcao == 3) { // Listar ingressos disponíveis
      Limpa_tela("Aperte [ENTER] para continuar...");
      printf("\n%s[Ingressos Disponíveis]%s\n", verd, rset);
      Listar_ingressos(disponiveis);
    } else if (opcao == 4) { // Listar ingressos vendidos
      Limpa_tela("Aperte [ENTER] para continuar...");
      printf("\n%s[Ingressos Vendidos]%s\n", mage, rset);
      Listar_ingressos(vendidos);
      printf("\n");
    } else { // Opção inválida
      printf("Opção inválida!\n");
    }
  }
  vendidos = Libera_lista(vendidos);
  disponiveis = Libera_lista(disponiveis);
}