#ifndef LLADAE2D_H
#define LLADAE2D_H

#include <stddef.h>

/* Variáveis que armazenam cores de texto */
extern const char *rset;
extern const char *azul;
extern const char *verd;
extern const char *cian;
extern const char *verm;
extern const char *mage;
extern const char *amar;

typedef struct ingresso {
    int ID, assento;
    char filme[100];
} Ingresso;

typedef struct no {
    struct no* ant;
    Ingresso info;
    struct no* prox;
} Lista;

Lista* Cria_lista();

Lista* Libera_lista(Lista* Ptl);

int E_vazia(Lista* Ptl);

int E_cheia(Lista* Ptl);

Lista* Insere_elem(Lista* Ptl, Ingresso elem);

Lista* Remove_elem(Lista* Ptl, Ingresso elem);

int Tamanho_lista(Lista* Ptl);

int Consulta_nodo(Lista* Ptl, int ID, Ingresso *elem);

int Vender_ingresso(Lista** Ptl, Lista** Ptc, int ID);

int Cancelar_venda(Lista** Ptl, Lista** Ptc, int ID);

void Listar_ingressos(Lista* Ptl);

int Escolha_menu();

void Limpa_buffer();

void Limpa_tela();

int Escolhe_ID();

#endif