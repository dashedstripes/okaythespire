#ifndef ENEMY_H
#define ENEMY_H

#include "deck.h"
#include "hand.h"
#include "text.h"

typedef struct {
  Deck *deck;
  Hand *hand;
  int health;
  int energy;
} Enemy;

int Enemy_Init(Enemy *enemy);
int Enemy_Render(SDL_Renderer *renderer, Enemy *enemy, TTF_Font *font);

#endif