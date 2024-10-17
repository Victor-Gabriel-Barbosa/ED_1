#ifndef ARVORE_H
#define ARVORE_H

typedef struct No *Arvore;

Arvore arvoreCria();

Arvore arvoreDestroi(Arvore arvore);

Arvore arvoreVazia(Arvore arvore);

Arvore arvoreInsere(Arvore arvore, int data);

Arvore arvoreRemove(Arvore arvore, int data);

int arvoreBusca(Arvore arvore, int data);

#endif