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

struct no {
  struct no* ant;
  Ingresso info;
  struct no* prox;
};

Lista* Cria_lista(void) {
  return NULL;
}
  
//versao para libera - nao esta de acordo com TAD definido
Lista* Libera_lista(Lista *Ptl) {
  Lista   *aux;
  while (Ptl!= NULL) {
    aux = Ptl;
    Ptl = Ptl->prox;
    free(aux);
  }
  return NULL;
}

int E_vazia(Lista *Ptl) {
  if (Ptl == NULL)
    return 1;
  else return 0;
}

int E_cheia(Lista *Ptl) {
   return 0;
}  


Lista* Insere_elem(Lista *Ptl, Ingresso elem) {
  Lista *Ptnodo;
  Ptnodo = (Lista*)malloc(sizeof(Lista));
  if (Ptnodo == NULL)
    return Ptl;
  Ptnodo->info = elem;
  Ptnodo->prox = Ptl;
  Ptnodo->ant = NULL;
  if(Ptl != NULL)
      Ptl->ant = Ptnodo;
  Ptl = Ptnodo;
  return Ptl;
}

Lista* Remove_elem(Lista *Ptl, Ingresso elem) {
  Lista *atual;
  if (Ptl == NULL)
    return Ptl;

  atual = Ptl;
  while (atual != NULL && elem.ID != atual->info.ID) {
     atual = atual->prox;
  }
  if (atual == NULL)// não achou
    return Ptl;
  
  if (atual == Ptl)// primeiro nodo a ser removido
      Ptl = atual->prox;   
  else // nodo removido do meio ou do final da lista
       atual->ant->prox = atual->prox;
       
  if (atual->prox != NULL)
           atual->prox->ant = atual->ant;
  free(atual);
  return Ptl;  
}


int Tamanho_lista(Lista *Ptl) {
  Lista *pt;
  int cont;
  pt = Ptl;
  cont = 0;
  while (pt != NULL) {
    cont++;
    pt = pt->prox;
  }
  return cont;
}

  
int Consulta_nodo(Lista *Ptl, int ID, Ingresso *elem) {
  Lista *pt;
  pt = Ptl;
  while (pt!= NULL && pt->info.ID!= ID) {
    pt = pt->prox;
  }
  if (pt == NULL) 
    return 0;
  *elem = pt->info;
  return 1;
}

Lista* Vender_ingresso(Lista* Ptl, Lista* Ptc, int ID) {
  Ingresso elem;
  if (Consulta_nodo(Ptl, ID, &elem) == 0) {
    printf("Posicão inválida!\n");
    return Ptl;
  }
  Ptl = Remove_elem(Ptl, elem);
  Ptc = Insere_elem(Ptc, elem);
  printf("Ingresso %d vendido!\n", elem.ID);
  return Ptl;
}

Lista* Cancelar_venda(Lista* Ptl, Lista* Ptc, int ID) {
  Ingresso elem;
  if (Consulta_nodo(Ptc, ID, &elem) == 0) {
    printf("Posicão inválida!\n");
    return Ptc;
  }
  Ptc = Remove_elem(Ptc, elem);
  Ptl = Insere_elem(Ptl, elem);
  printf("Ingresso %d cancelado!\n", elem.ID);
  return Ptc;
}

void Listar_ingressos(Lista* Ptl) {
  Lista *pt;
  pt = Ptl;
  while (pt!= NULL) {
    printf("ID: %d\n", pt->info.ID);
    printf("Assento: %d\n", pt->info.assento);
    printf("Filme: %s\n", pt->info.filme);
    pt = pt->prox;
  }
}

int Escolha_menu() {
  int opcao;
  printf("\n[Menu]\n");
  printf("1 - Vender ingresso\n");
  printf("2 - Cancelar venda\n");
  printf("3 - Listar ingressos disponíveis\n");
  printf("4 - Listar ingressos vendidos\n");
  printf("0 - Sair\n");
  printf("Escolha uma opcao: ");
  scanf("%d", &opcao);
  Limpa_buffer();
  return opcao;
}

void Limpa_buffer() {
  char c;
  while ((c = getchar())!= '\n' && c!= EOF);
}

void Limpa_tela(char *msg) {
  printf("\n%s\n", msg);
  Limpa_buffer();
  printf("\033[H\033[2J");
}
