#ifndef RPG_H
#define RPG_H

typedef enum {
  ATAQUE_FISICO,
  ATAQUE_MAGICO
} tipoAtaque;

typedef struct jogadores {
  char nome[20];
  int atq, mp, lvl, hp, def, vel;
  tipoAtaque tipAtq;
} Jogador; 

typedef struct jogosRPG {
  Jogador p1, p2; 
  int turno;
} RPG;

/* Aleatoriza as informações de um jogador */
Jogador jogadorAleatoriza();

/* Aleatoriza as informações de uma partida de RPG */
RPG rpgAleatoriza(const int turno);

/* Realiza uma batalha entre dois players */
RPG rpgBatalha(RPG rp); 

/* Mostra o estado de uma partida de RPG */
void rpgExibe(const RPG rp);

#endif