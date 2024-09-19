#ifndef PLANETAS_H
#define PLANETAS_H

typedef struct planetas {
  char nome[20];
  float massa;
  float gravidade;
  float distancia_sol;
} Planeta;

/* Aleatoriza as informações de um planeta */
Planeta planetaAleatoriza(const int posi);

/* Mostra um planeta */
void planetaExibe(const Planeta planeta);

#endif