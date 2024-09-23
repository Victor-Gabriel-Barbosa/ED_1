#ifndef PILHA_ESTATICA_H
#define PILHA_ESTATICA_H

#include "RPG.h"

#define MAX 999999

typedef struct stackEst PilhaEst; 

/* Cria e inicializa a pilha estática */ 
PilhaEst *pilhaCriaEst();

/* Libera a memória alocada p/ pilha estática */
PilhaEst *pilhaLiberaEst(PilhaEst *Ptf);

/* Verifica se a pilha estática está vazia */
int pilhaVaziaEst(PilhaEst *Ptf);

/* Insere um jogo na pilha estática (push) */
PilhaEst *pilhaInsereEst(PilhaEst *Ptf, RPG rp);
  
/* Remove um planeta da pilha (pop) */
PilhaEst *pilhaRemoveEst(PilhaEst *Ptf, RPG *rp);

/* Consulta um jogo da pilha estática */
int pilhaConsultaEst(PilhaEst *Ptf, RPG *rp);

/* Exibe a pilha estática */ 
int pilhaExibeEst(PilhaEst *Ptf);

/* Encontra o tamanho da pilha estática */
int pilhaTamanhoEst(PilhaEst *Ptf);

#endif 