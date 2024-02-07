#ifndef ENEMY_H
#define ENEMY_H

#include "deck.h"
#include "hand.h"

typedef struct {
  Deck *deck;
  Hand *hand;
  int health;
  int energy;
} Enemy;

int Enemy_Init(Enemy *enemy);

#endif