#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"
#include "hand.h"
#include "enemy.h"

#define PLAYER_INITIAL_HEALTH 100
#define PLAYER_INITIAL_ENERGY 3

typedef struct {
  Deck *deck;
  Hand *hand;
  int health;
  int energy;
} Player;

int Player_Init(Player *player);
int Player_UseCard(Player *player, int cardIndex, Enemy *enemy);

#endif