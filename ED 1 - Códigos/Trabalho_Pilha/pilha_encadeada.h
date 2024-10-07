#ifndef PILHA_ENCADEADA_H
#define PILHA_ENCADEADA_H 

#include "RPG.h"

typedef struct stackEnc PilhaEnc;

/* Cria e inicializa a pilha encadeada */
PilhaEnc *pilhaCriaEnc();
 
/* Libera a memória alocada p/ uma pilha encadeada */
PilhaEnc *pilhaLiberaEnc(PilhaEnc *Ptf);

/* Verifica se a pilha encadeada está vazia */
int pilhaVaziaEnc(PilhaEnc *Ptf);

/* Insere um planeta na pilha encadeada (push) */
PilhaEnc *pilhaInsereEnc(PilhaEnc *Ptf, RPG rp);

/* Remove um planeta da pilha encadeada (pop) */
PilhaEnc *pilhaRemoveEnc(PilhaEnc *Ptf, RPG *rp);

/* Consulta o último jogo da pilha encadeada */
int pilhaConsultaEnc(PilhaEnc *Ptf, RPG *rp); 

/* Exibe a pilha encadeada */
int pilhaExibeEnc(PilhaEnc *Ptf);

/* Encontra o tamanho da pilha encadeada */
int pilhaTamanhoEnc(PilhaEnc *Ptf);

#endif 