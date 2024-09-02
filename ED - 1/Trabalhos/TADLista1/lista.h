#ifndef FUNCOES_H
#define FUNCOES_H

#include <stddef.h>

/* Variáveis que armazenam cores de texto */
extern const char *rset;
extern const char *azul;
extern const char *verd;
extern const char *cian;
extern const char *verm;
extern const char *mage;
extern const char *amar;

/* Variáveis que armazenam formatos de bordas */
extern const char *brd_vaz[];
extern const char *brd_dup[];
extern const char *brd_lev[];
extern const char *brd_dlv[];
extern const char *brd_lin[];
extern const char *brd_neg[];
extern const char *brd_crv[];
extern const char *brd_dcr[];
extern const char *brd_rsc[];
extern const char *brd_nrc[];
extern const char *brd_grd[];
extern const char *brd_grs[];
extern const char *brd_esp[];
extern const char *brd_trc[];
extern const char *brd_pnt[];


/* Estrutura p/ armazenar datas */
typedef struct { 
  int dia, mes, ano;
} Data;

/* Estrutura p/ armazenar horas */
typedef struct {
  int hora, minuto, segundo;
} Hora; 

/* Tipos de transações */
typedef enum { 
  DEBITO,
  CREDITO
} TipoTransacao;

/* Estrutura p/ armazenar uma transação */
typedef struct transacao { 
  TipoTransacao tipo;
  int ID;
  float valor;
  Data data;
  Hora hora;
  char descricao[100]; 
} Transacao;

/* Estrutura p/ armazenar a lista */
typedef struct lista Lista; 

Lista* Cria_lista(void); /* Cria a lista */
Lista* Libera_lista(Lista* Ptl); /* Libera a lista */
Lista* Insere_elem(Lista* Ptl, Transacao info); /* Insere um elemento no final da lista */
Lista* Remove_elem(Lista *Ptl, int valor_ID); /* Remove um elemento da lista */
Lista* Remove_elem_mov(Lista *Ptl, int valor_ID); /* Remove um elemento da lista */
int Consulta_nodo(Lista *Ptl, int pos, Transacao *info); /* Retorna o elemento da posição pos */
int Tamanho_lista(Lista* Ptl); /* Retorna o tamanho da lista */
int E_cheia(Lista* Ptl); /* Verifica se a lista está cheia */
int E_vazia(Lista* Ptl); /* Verifica se a lista está vazia */
void Limpa_buffer(); /* Limpa o buffer do teclado */
void Cls_screen(); /* Limpa a tela do terminal */
void Limpa_tela(); /* Aguarda uma entrada do usuário p/ limpar a tela do terminal */
void Barra_div(const char *i, const char *f); /* Exibe uma barra de divisão */
int Sim_ou_nao(const char *msg); /* Solicita e retorna a confirmação de uma ação do usuário */
Data Get_data(); /* Retorna a data atual */
Hora Get_hora(); /* Retorna a hora atual */
void Exibe_transacao(Transacao info); /* Exibe uma transação da lista */
int Exibe_lista(); /* Exibe a lista de transações */
int Grava_lista(Lista* Ptl, char* nome_arqv); /* Grava a lista em um arquivo */
Transacao Get_transacao(); /* Função para capturar os dados da transação */
int Compara_datas(Data a1, Data a2); /* Compara duas datas */
Lista *Edita_transacao(Lista *Ptl, int valor_ID); /* Edita uma transação existente */
void Filtra_transacoes(Lista *Ptl, int tipo); /* Exibe transações de um tipo específico */
void Exibe_transacoes_por_data(Lista *Ptl, Data inicio, Data fim); /* Exibe transações dentro de um intervalo de datas */
float Calcula_saldo(Lista *Ptl); /* Calcula o saldo total */
void Ordena_transacoes_por_data(Lista *Ptl); /* Ordena transações por data */
int Escolha_menu(); /* Função para exibir o menu e capturar a escolha do usuário */

#endif