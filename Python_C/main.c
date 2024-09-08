// Arquivo "main.c"
#include <stdio.h>
#include "dog.h"

int main() {
    // Cria um novo cachorro
    Dog* meuDog = dog_criar("Rex");

    // Faz o cachorro latir e correr
    dog_latir(meuDog);
    dog_correr(meuDog);

    // Destrói o cachorro
    dog_destruir(meuDog);

    return 0;
}
