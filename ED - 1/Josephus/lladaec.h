#ifndef LLADAEC_H
#define LLADAEC_H

#include <stddef.h>

typedef struct pessoas {
  int num;
  char nome[50];
} Pessoas;

typedef struct no {
  Pessoas dados;
  struct no* prox;
} Lista;

Lista* Cria_lista();
Lista* Libera_lista(Lista* Ptl);
int E_vazia(Lista* Ptl);
int E_cheia(Lista* Ptl);
Lista* Insere_elem(Lista* Ptl, Pessoas dados);
Lista* Remove_elem(Lista* Ptl, Pessoas dados);
int Tamanho_lista(Lista* Ptl);
int Consulta_nodo(Lista* Ptl, int pos, Pessoas* dados);
void Exibe_elem(Lista* Ptl, int pos);
void Limpa_buffer();
void Grava_arquivo(Pessoas dados, char* nome_arq);
void Grava_ganhador(Pessoas dados, char* nome_arq);

#endif