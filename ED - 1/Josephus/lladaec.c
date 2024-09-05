#include "lladaec.h"
#include <stdio.h>
#include <stdlib.h>
           
Lista* Cria_lista(void) { // Cria uma lista vazia
  return NULL;
}

Lista* Libera_lista(Lista* Ptl) { // Libera a memória de uma lista
  Lista  *pt, *aux;
  if (Ptl == NULL) return NULL;
  pt = Ptl->prox;
  while (pt != Ptl) {
    aux = pt;
    pt = pt->prox;
    free(aux);
  }
  free(pt);
  return NULL;
}

int E_vazia(Lista* Ptl) { // Verifica se a lista está vazia
  if (Ptl == NULL) return 1;
  return 0;
}

Lista* Insere_elem(Lista* Ptl, Pessoas dados) { // Insere um elemento na lista
  Lista *Ptnodo, *aux;
  Ptnodo = (Lista*)malloc(sizeof(struct no));
  if (Ptnodo == NULL) return Ptl;
  Ptnodo->dados = dados;
  if (Ptl == NULL) {
    Ptl = Ptnodo;
    Ptnodo->prox = Ptl;
  } else {
    Ptnodo->prox = Ptl->prox;
    Ptl->prox = Ptnodo;
    Ptl = Ptnodo;
  }
  return Ptl;
}

Lista* Remove_elem_v1(Lista* Ptl, Pessoas dados) { // Remove um elemento da lista
  Lista *ant,*atual,*Ptaux;
  if (Ptl == NULL) return Ptl;
  atual = Ptl;
  if (atual->dados.num == dados.num) {
    if (atual->prox == Ptl) {
      Ptl = NULL;
      free(atual);
      return Ptl;
    } else {
      Ptaux = atual;
      while(Ptaux->prox != Ptl) {
        Ptaux = Ptaux->prox;
      }
      Ptaux->prox = atual->prox;
      Ptl = atual->prox;
      free(atual);
      return Ptl;
    }
  }
  ant = atual;
  atual = atual->prox;
  while (atual != Ptl && atual->dados.num != dados.num) {
    ant = atual;
    atual = atual->prox;
  }
  if (atual == Ptl) return Ptl;
  ant->prox = atual->prox;
  free(atual);
  return Ptl;
}

Lista* Remove_elem(Lista* Ptl, Pessoas dados) { // Remove um elemento da lista
  Lista *ant, *atual, *aux; 
  if (Ptl == NULL) return Ptl;
  atual = Ptl->prox;
  ant = Ptl;
  while (atual!= Ptl && atual->dados.num != dados.num) {
    ant = atual;
    atual = atual->prox;
  }
  if (atual->dados.num == dados.num) { 
    if (atual == ant) Ptl = NULL;
    else {
      ant->prox = atual->prox;
      if (atual == Ptl) Ptl = ant;
    }  
    free(atual);
  }
  return Ptl;  
}   

int Tamanho_lista(Lista* Ptl) { // Retorna o número de elementos na lista
  Lista *pt;
  int cont;
  if (Ptl == NULL) return 0;
  pt = Ptl->prox;
  cont = 1;
  while (pt != Ptl) {
    pt = pt->prox;
    cont++;
  }
  return cont;
}

int Consulta_nodo(Lista* Ptl, int pos, Pessoas* dados) { // Consulta o valor de um nodo em uma posição específica
  int cont;
  Lista *pt;
  if( Ptl == NULL || pos <= 0) return 0;
  cont = 1;
  pt = Ptl->prox;
  while(pt != Ptl && cont < pos) {
    pt = pt->prox;
    cont++;
  }
  if (cont == pos) {
    *dados = pt->dados;
    return 1;
  }
  return 0;
}

void Exibe_elem(Lista* Ptl, int pos) { // Exibe o valor de um nodo em uma posição específica
  Pessoas dados;
  if (Consulta_nodo(Ptl, pos, &dados)) {
    printf("Número: %d\n", dados.num);
    printf("Nome: %s\n", dados.nome);
  } else {
    printf("Posicao inválida!\n");
  }
}

void Limpa_buffer() { // Limpa o buffer de entrada
  char c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void Grava_arquivo(Pessoas dados, char* nome_arq) {
  FILE *arq;
  arq = fopen(nome_arq, "a");
  if (arq == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }
  fprintf(arq, "%d;%s\n", dados.num, dados.nome);
  fclose(arq);
}

void Grava_ganhador(Pessoas dados, char* nome_arq) {
  FILE *arq;
  arq = fopen(nome_arq, "a");
  if (arq == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }
  fprintf(arq, "\nÚltimo(a) restante: %s (%d)\n", dados.nome, dados.num);
  fprintf(arq, "Parabéns! Você é o(a) grande vencedor(a) e recebe um prêmio de 1 milhão de moedas de ouro!\n");
  fclose(arq);
}