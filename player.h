#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"
#include "enemy.h"

#define PLAYER_INITIAL_HEALTH 100
#define PLAYER_INITIAL_ENERGY 3

typedef struct {
  Card **hand;
  int handSize;
  int handCapacity;
  Card* activeCard;
  int health;
  int energy;
  int block;
} Player;

int Player_Init(Player *player);
void Player_AddCard(Player *player, Card *card, int index);
void Player_SelectCard(Player *player, int cardIndex);
int Player_UseCard(Player *player, Enemy *enemy);
void Player_HandleClick(Player *player, int x, int y);
void Player_Update(Player *player, float deltaTime);
int Player_Render(SDL_Renderer *renderer, Player *player, TTF_Font *font);

#endif