#ifndef PILHA_ESTATICA_H
#define PILHA_ESTATICA_H

#define MAX 999999

typedef struct stackEst PilhaEst; 

/* Cria e inicializa a pilha estática */ 
PilhaEst *pilhaCriaEst();

/* Libera a memória alocada p/ pilha estática */
PilhaEst *pilhaLiberaEst(PilhaEst *Ptf);

/* Verifica se a pilha estática está vazia */
int pilhaVaziaEst(PilhaEst *Ptf);

/* Insere um elemento na pilha estática (push) */
PilhaEst *pilhaInsereEst(PilhaEst *Ptf, char letra);
  
/* Remove um planeta da pilha (pop) */
PilhaEst *pilhaRemoveEst(PilhaEst *Ptf, char *letra); 

/* Consulta um elemento da pilha estática */
int pilhaConsultaEst(PilhaEst *Ptf, char *letra);

/* Exibe a pilha estática */ 
int pilhaExibeEst(PilhaEst *Ptf);

/* Encontra o tamanho da pilha estática */
int pilhaTamanhoEst(PilhaEst *Ptf);

/* Verifica se uma palavra é um palíndromo */ 
int pilhaPalinEst(PilhaEst *Ptp, char *palavra);

#endif 