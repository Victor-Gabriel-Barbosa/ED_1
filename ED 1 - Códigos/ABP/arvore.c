#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

// Estrutura da Árvore Binária de Pesquisa (ABP)
typedef struct No {
  int dado;
  struct No* direita;
  struct No* esquerda;
} *Arvore;

// Cria uma nova árvore vazia
Arvore arvoreCria() {
  return NULL;
}

// Libera a memória alocada para uma árvore
Arvore arvoreLibera(Arvore arvore) {
  if (arvore != NULL) { // Verifica o nó não é vazio
    arvoreLibera(arvore->esquerda); // Libera o lado esquerdo
    arvoreLibera(arvore->direita); // Libera o lado direito
    free(arvore); // Libera a árvore em si
  }
  return NULL;
}

// Insere um elemento na árvore
Arvore arvoreInsere(Arvore arvore, const int dado) {
  // Cria um nó para o novo elemento 
  Arvore no = (Arvore)malloc(sizeof(struct No));
  if (no == NULL) return arvore;
  no->dado = dado;
  no->esquerda = NULL;
  no->direita = NULL;

  if (arvore == NULL) return no; // Se a árvore está vazia, o novo nó é a raiz
  Arvore atual = arvore;
  Arvore pai = NULL;
  while (atual != NULL) { // Percorre a árvore para inserir o elemento
    pai = atual; // Atualiza o pai
    if (dado < atual->dado) atual = atual->esquerda; // Se o elemento é menor vai para a esquerda
    else atual = atual->direita; // Senão vai para a direita
  }
  if (dado < pai->dado) pai->esquerda = no; // Se o elemento é menor que o pai vai para a esquerda
  else pai->direita = no; // Senão vai para a direita
  return arvore;
}

// Busca um elemento na árvore
Arvore arvoreBusca(Arvore arvore, const int dado) {
  Arvore atual = arvore;
  while (atual != NULL) { // Percorre a árvore fazendo a busca
    if (dado == atual->dado) return atual; // Se encontrou o elemento, retorna o nó atual
    else if (dado < atual->dado) atual = atual->esquerda; // Senão, se o elemento é menor vai para a esquerda
    else atual = atual->direita; // Senão vai para a direita
  }
  return NULL; // Se não encontrou retorna 'NULL' 
}

// Encontra e retorna o nó de menor valor da árvore
Arvore encontraMinimo(Arvore arvore) {
  while (arvore != NULL && arvore->esquerda != NULL) arvore = arvore->esquerda; // Percorre a árvore pela esquerda
  return arvore;
}

// Encontra e retorna o nó de maior valor da árvore
Arvore encontraMaximo(Arvore arvore) {
  while (arvore != NULL && arvore->direita != NULL) arvore = arvore->direita; // Percorre a árvore pela direita
  return arvore;
}

// Remove um elemento da árvore
Arvore arvoreRemove(Arvore arvore, const int dado) {
  if (arvore == NULL) return NULL; // Verifica se a árvore é vazia
  if (dado < arvore->dado) arvore->esquerda = arvoreRemove(arvore->esquerda, dado); // Se o elemento é menor, remove pela esquerda
  else if (dado > arvore->dado) arvore->direita = arvoreRemove(arvore->direita, dado); // Senão, remove pela direita
  else { // Encontrou o nó a ser removido
    if (arvore->esquerda == NULL) { // Se não tem filho esquerdo, conecta o nó direito ao pai do nó a ser removido
      Arvore temp = arvore->direita;
      free(arvore);
      return temp;
    } else if (arvore->direita == NULL) { // Senão, se não tem filho direito, conecta o nó esquerdo ao pai do nó a ser removido
      Arvore temp = arvore->esquerda;
      free(arvore);
      return temp;
    } else { // Senão, se tem ambos os filhos, remove o nó sucessor em-ordem da direita
      Arvore temp = encontraMinimo(arvore->direita);
      arvore->dado = temp->dado;
      arvore->direita = arvoreRemove(arvore->direita, temp->dado);
    }
  }
  return arvore;
}

// Conta a quantidade total de nós da árvore
int arvoreContaNos(Arvore arvore) {
  if (arvore == NULL) return 0; // Verifica se a árvore é vazia
  return 1 + arvoreContaNos(arvore->esquerda) + arvoreContaNos(arvore->direita); // Conta os nós da esquerda e da direita
}

// Conta a quantidade de 'galhos' da árvore
int arvoreContaGalhos(Arvore arvore) {
  if (arvore == NULL || (arvore->esquerda == NULL && arvore->direita == NULL)) return 0; // Se a árvore é vazia ou o nó não tem filhos, retorna 0
  return 1 + arvoreContaGalhos(arvore->esquerda) + arvoreContaGalhos(arvore->direita); // Conta os galhos da esquerda e da direita
}

// Conta a quantidade de 'folhas' da árvore
int arvoreContaFolhas(Arvore arvore) {
  if (arvore == NULL) return 0; // Se a árvore é vazia, retorna 0
  if (arvore->esquerda == NULL && arvore->direita == NULL) return 1; // Senão, se o nó não tem filhos, retorna 1
  return arvoreContaFolhas(arvore->esquerda) + arvoreContaFolhas(arvore->direita); // Conta as folhas da esquerda e da direita
}

// Encontra a altura da árvore
int arvoreAltura(Arvore arvore) {
  if (arvore == NULL) return -1; // Se a árvore é vazia, retorna -1 
  int alturaEsquerda = arvoreAltura(arvore->esquerda); // Encontra a altura do lado esquerdo
  int alturaDireita = arvoreAltura(arvore->direita); // Encontra a altura do lado direito
  return 1 + (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita); // Retorna a maior altura
}

// Encontra o menor valor da árvore
int arvoreMenor(Arvore arvore) {
  if (arvore == NULL) return -1; // Verifica se a árvore é vazia
  while (arvore->esquerda != NULL) arvore = arvore->esquerda; // Percorre a árvore pela esquerda
  return arvore->dado;
}

// Encontra o maior valor da árvore
int arvoreMaior(Arvore arvore) {
  if (arvore == NULL) return -1; // Verifica se a árvore é vazia
  while (arvore->direita != NULL) arvore = arvore->direita; // Percorre a árvore pela direita
  return arvore->dado;
}

// Espelha a árvore
int arvoreEspelho(Arvore arvore) {
  if (arvore == NULL) return 0; // Verifica se o nó é vazio

  // Troca o nó da esquerda com o da direita
  Arvore temp = arvore->esquerda;
  arvore->esquerda = arvore->direita;
  arvore->direita = temp;

  arvoreEspelho(arvore->esquerda); // Espelha o lado esquerdo
  arvoreEspelho(arvore->direita); // Espelha o lado direito
  return 1;
}

// Exibe a árvore em pré-ordem
int arvoreExibePreOrdem(Arvore arvore) {
  if (arvore == NULL) return 0; // Verifica se a árvore é vazia
  printf("%d ", arvore->dado);         
  arvoreExibePreOrdem(arvore->esquerda); // Exibe o lado esquerdo
  arvoreExibePreOrdem(arvore->direita); // Exibe o lado direito  
  return 1;
}

// Exibe a árvore em ordem
int arvoreExibeEmOrdem(Arvore arvore) {
  if (arvore == NULL) return 0; // Verifica se a árvore é vazia
  arvoreExibeEmOrdem(arvore->esquerda); // Exibe o lado esquerdo   
  printf("%d ", arvore->dado);        
  arvoreExibeEmOrdem(arvore->direita); // Exibe o lado direito  
  return 1; 
}

// Exibe a árvore em pós-ordem
int arvoreExibePosOrdem(Arvore arvore) {
  if (arvore == NULL) return 0; // Verifica se a árvore é vazia
  arvoreExibePosOrdem(arvore->esquerda); // Exibe o lado esquerdo     
  arvoreExibePosOrdem(arvore->direita); // Exibe o lado direito
  printf("%d ", arvore->dado); 
  return 1;     
}