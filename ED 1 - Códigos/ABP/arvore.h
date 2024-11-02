#ifndef ARVORE_H
#define ARVORE_H

// Estrutura abstrata da Árvore Binária de Pesquisa (ABP)
typedef struct No *Arvore;

// Cria uma nova árvore vazia
Arvore arvoreCria();

// Libera a memória alocada para uma árvore
Arvore arvoreLibera(Arvore arvore);

// Encontra e retorna o nó de menor valor da árvore
Arvore arvoreVazia(Arvore arvore);

// Remove um elemento da árvore
Arvore arvoreInsere(Arvore arvore, int data);

// Busca um elemento na árvore
Arvore arvoreBusca(Arvore arvore, const int dado);

// Conta a quantidade total de nós da árvore
Arvore arvoreRemove(Arvore arvore, int data);

// Conta a quantidade total de nós da árvore
int arvoreContaNos(Arvore arvore);

// Conta a quantidade de 'galhos' da árvore
int arvoreContaGalhos(Arvore arvore);

// Conta a quantidade de 'folhas' da árvore
int arvoreContaFolhas(Arvore arvore);

// Encontra a altura da árvore
int arvoreAltura(Arvore arvore);

// Encontra o menor valor da árvore
int arvoreMenor(Arvore arvore);

// Encontra o maior valor da árvore
int arvoreMaior(Arvore arvore);

// Espelha a árvore
int arvoreEspelho(Arvore arvore);

// Exibe a árvore em pré-ordem
int arvoreExibePreOrdem(Arvore arvore);

// Exibe a árvore em ordem
int arvoreExibeEmOrdem(Arvore arvore);

// Exibe a árvore em pós-ordem
int arvoreExibePosOrdem(Arvore arvore);

#endif