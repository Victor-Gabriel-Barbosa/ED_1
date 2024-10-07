#ifndef PLANETAS_H
#define PLANETAS_H

typedef struct planetas {
  char nome[20];
  float massa;
  float gravidade;
  float distancia_sol;
} Planeta;
 
/* Aleatoriza as informações de um planeta */
Planeta planetaAleatoriza(int *posi);

/* Mostra um planeta */
void planetaExibe(const Planeta plan); 

/* Faz a colisão entre dois planetas */
Planeta planetaBigBang(const Planeta plan1, const Planeta plan2);

#endif