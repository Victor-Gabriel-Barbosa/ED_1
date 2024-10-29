#ifndef ARVORE_H
#define ARVORE_H

typedef struct No *Arvore;

Arvore arvoreCria();

Arvore arvoreLibera(Arvore arvore);

Arvore arvoreVazia(Arvore arvore);

Arvore arvoreInsere(Arvore arvore, int dado);

Arvore encontraMinimo(Arvore arvore);

Arvore arvoreRemove(Arvore arvore, int dado);

int arvoreBusca(Arvore arvore, int dado);

int arvoreExibe(Arvore arvore, int nivel);

#endif