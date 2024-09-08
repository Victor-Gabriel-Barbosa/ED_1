// Arquivo "dog.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dog.h"

// Definição completa da estrutura Dog
struct Dog {
    char nome[50];  // Nome do cachorro
};

// Função para criar um cachorro
Dog* dog_criar(const char* nome) {
    Dog* dog = (Dog*)malloc(sizeof(Dog));
    if (dog) {
        strncpy(dog->nome, nome, sizeof(dog->nome) - 1);
        dog->nome[sizeof(dog->nome) - 1] = '\0';  // Certifique-se de que o nome termine em '\0'
    }
    return dog;
}

// Função para destruir o cachorro
void dog_destruir(Dog* dog) {
    free(dog);
}

// Função para o cachorro latir
void dog_latir(Dog* dog) {
    printf("%s está latindo: Au Au!\n", dog->nome);
}

// Função para o cachorro correr
void dog_correr(Dog* dog) {
    printf("%s está correndo!\n", dog->nome);
}
