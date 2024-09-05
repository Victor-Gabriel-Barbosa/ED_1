/* 
Júlia, uma funcionária que trabalha em uma bilheteria de cinema, diz que sua rotina está
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

/* Variáveis que armazenam cores de texto */
const char *rset = "\033[0m";
const char *azul = "\033[38;5;39m";
const char *verd = "\033[38;5;46m";
const char *cian = "\033[38;5;51m";
const char *verm = "\033[38;5;196m";
const char *mage = "\033[38;5;201m";
const char *amar = "\033[38;5;220m";

Lista* Cria_lista(Lista *Ptl) { // Cria uma lista vazia
  return NULL;
}
  
Lista* Libera_lista(Lista *Ptl) { // Libera todos os elementos da lista
  Lista *aux;
  while (Ptl!= NULL) {
    aux = Ptl;
    Ptl = Ptl->prox;
    free(aux);
  }
  return NULL;
}

int E_vazia(Lista *Ptl) { // Verifica se a lista está vazia
  if (Ptl == NULL) return 1;
  return 0;
}

int E_cheia(Lista *Ptl) { // Verifica se a lista está cheia
  return 0;
}  

Lista* Insere_elem(Lista *Ptl, Ingresso elem) { // Insere um novo elemento no final da lista
  Lista *Ptnodo = (Lista*)malloc(sizeof(Lista));
  if (Ptnodo == NULL) return Ptl;
  Ptnodo->info = elem; 
  Ptnodo->prox = NULL;   
  Ptnodo->ant = NULL;   
  if (Ptl == NULL) return Ptnodo;
  Lista *pt = Ptl;
  while (pt->prox != NULL) {
    pt = pt->prox;
  }
  pt->prox = Ptnodo;
  Ptnodo->ant = pt;
  return Ptl; 
}


Lista* Remove_elem(Lista *Ptl, Ingresso elem) { // Remove um elemento da lista
  Lista *atual;
  if (Ptl == NULL) return Ptl;
  atual = Ptl;
  while (atual != NULL && elem.ID != atual->info.ID) {
    atual = atual->prox;
  }
  if (atual == NULL) return Ptl;
  if (atual == Ptl) Ptl = atual->prox;   
  else atual->ant->prox = atual->prox;   
  if (atual->prox != NULL) atual->prox->ant = atual->ant;
  free(atual);
  return Ptl;  
}

int Tamanho_lista(Lista *Ptl) { // Retorna o número de elementos na lista
  Lista *pt;
  int cont = 0;
  pt = Ptl;
  while (pt != NULL) {
    cont++;
    pt = pt->prox;
  }
  return cont;
}

int Consulta_nodo(Lista* Ptl, int ID, Ingresso* elem) { // Consulta um elemento na lista
  Lista *pt;
  pt = Ptl;
  while (pt != NULL && pt->info.ID != ID) {
    pt = pt->prox;
  }
  if (pt == NULL) return 0;
  *elem = pt->info;
  return 1;
 }

int Vender_ingresso(Lista** Ptl, Lista** Ptc, int ID) { // Vende um ingresso
  Ingresso elem;
  if (Consulta_nodo(*Ptl, ID, &elem) == 0) return 0;
    *Ptl = Remove_elem(*Ptl, elem);
    *Ptc = Insere_elem(*Ptc, elem);
  return 1;
}

int Cancelar_venda(Lista** Ptl, Lista** Ptc, int ID) { // Cancela uma venda
  Ingresso elem;  
  if (Consulta_nodo(*Ptc, ID, &elem) == 0) return 0;
  *Ptc = Remove_elem(*Ptc, elem);
  *Ptl = Insere_elem(*Ptl, elem);
  return 1;
}

void Listar_ingressos(Lista* Ptl) { // Lista todos os ingressos disponíveis
  if (Ptl == NULL) {
    printf("%s[Nenhum ingresso encontrado!]%s\n", verm, rset);
    return;
  }
  Lista *pt = Ptl;
  printf("──────────────────────\n");
  while (pt != NULL) {
    printf("ID: %d\n", pt->info.ID);
    printf("Assento: %d\n", pt->info.assento);
    printf("Filme: %s\n", pt->info.filme);
    printf("──────────────────────\n");
    pt = pt->prox;
  }
}

int Escolha_menu() { // Mostra o menu e retorna a opção escolhida
  Limpa_tela("Aperte [ENTER] para continuar...");
  int opcao;
  printf("╭──────────────────────────────────╮\n");
  printf("│          [Menu Principal]        │\n");
  printf("├──────────────────────────────────┤\n");
  printf("│ 1 - Vender ingresso              │\n");
  printf("│ 2 - Cancelar venda               │\n");
  printf("│ 3 - Listar ingressos disponíveis │\n");
  printf("│ 4 - Listar ingressos vendidos    │\n");
  printf("│ 0 - Sair                         │\n");
  printf("╰──────────────────────────────────╯\n");
  printf("Escolha uma opção: ");
  scanf("%d", &opcao);
  Limpa_buffer();
  return opcao;
}

void Limpa_buffer() { // Limpa o buffer do teclado para evitar problemas com scanf
  char c;
  while ((c = getchar())!= '\n' && c!= EOF);
}

void Limpa_tela(char *msg) { // Limpa a tela e exibe uma mensagem
  printf("\n%s\n", msg);
  Limpa_buffer();
  printf("\033[H\033[2J");
}

int Escolhe_ID() { // Escolhe um ID para um ingresso
  int ID;
  printf("Escolha o ID: ");
  scanf("%d", &ID);
  Limpa_buffer();
  return ID;
}