#include "player.h"
#include "enemy.h"
#include "hand.h"
#include "deck.h"
#include "card.h"

int Player_Init(Player *player, Deck *deck, Hand *hand) 
{
  player->deck = deck;
  player->hand = hand;
  player->health = PLAYER_INITIAL_HEALTH;
  player->energy = PLAYER_INITIAL_ENERGY;
  return 0;
}

int Player_UseCard(Player *player, int cardIndex, Enemy *enemy) 
{
  if (player->energy < 1) 
  {
    return -1;
  }

  if(cardIndex < 0 || cardIndex >= player->hand->max_size)
  {
    return -1;
  }

  if(player->hand->cards[cardIndex] == NULL)
  {
    return -1;
  }

  if(player->hand->cards[cardIndex]->type == ATTACK_CARD)
  {
    enemy->health -= player->hand->cards[cardIndex]->value;
  }

  player->energy -= 1;
  Hand_RemoveCard(player->hand, cardIndex);
  return 0;
}