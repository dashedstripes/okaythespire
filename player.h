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
  int block;
} Player;

int Player_Init(Player *player, Deck *deck, Hand *hand);
int Player_SelectCard(Player *player, int cardIndex);
int Player_UseCard(Player *player, Enemy *enemy);
int Player_Render(SDL_Renderer *renderer, Player *player, TTF_Font *font);

#endif