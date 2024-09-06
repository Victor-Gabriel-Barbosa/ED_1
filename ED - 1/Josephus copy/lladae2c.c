#include "lladae2c.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct no {
  Pessoas dados;
  struct no* prox;
  struct no* ant;
};

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
  Lista* Ptnodo = (Lista*)malloc(sizeof(struct no));
  if (Ptnodo == NULL) return Ptl;
  Ptnodo->dados = dados;
  if (Ptl == NULL) {  
    Ptnodo->prox = Ptnodo;
    Ptnodo->ant = Ptnodo;
    Ptl = Ptnodo;
  } else {  
    Ptnodo->prox = Ptl->prox;
    Ptnodo->ant = Ptl;
    Ptl->prox->ant = Ptnodo;
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
  Lista *atual = Ptl, *aux;
  if (Ptl == NULL) return NULL;  
  do {
    if (atual->dados.num == dados.num) {
      if (atual->prox == atual) { 
        free(atual);
        return NULL;
      } else {
        aux = atual;
        atual->ant->prox = atual->prox;
        atual->prox->ant = atual->ant;
        if (atual == Ptl) Ptl = atual->ant;
        free(aux);
        return Ptl;
      }
    }
    atual = atual->prox;
  } while (atual != Ptl);
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
    printf("Posição inválida!\n");
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

Lista* Jogo_josephus(Lista* josephus, int N) { // Jogo de Josephus
  srand(time(NULL));
  while (Tamanho_lista(josephus) > 1) {
    int k = (rand() % Tamanho_lista(josephus)) + 1;
    Lista* aux = josephus;
    for (int i = 1; i < k; i++) {
      aux = aux->prox;
    }
    Pessoas saida = aux->dados;
    printf("\nSaída: %s (%d)\n", saida.nome, saida.num);
    Grava_arquivo(saida, "saida.txt");

    josephus = Remove_elem(josephus, saida);
  }
  Pessoas ultimo = josephus->dados;
  printf("\nÚltimo(a) restante: %s (%d)\n", ultimo.nome, ultimo.num);
  Grava_ganhador(ultimo, "ultimo.txt");
  return josephus;
}