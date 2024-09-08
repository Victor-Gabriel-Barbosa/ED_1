// Arquivo "dog.h"
#ifndef DOG_H
#define DOG_H

// Tipo incompleto
typedef struct Dog Dog;

// Funções para criar, destruir e manipular o cachorro
Dog* dog_criar(const char* nome);
void dog_destruir(Dog* dog);

void dog_latir(Dog* dog);
void dog_correr(Dog* dog);

#endif
