#include "player.h"
#include "enemy.h"
#include "hand.h"
#include "deck.h"
#include "card.h"
#include "screen.h"

int Player_Init(Player *player, Deck *deck, Hand *hand) 
{
  player->deck = deck;
  player->hand = hand;
  player->health = PLAYER_INITIAL_HEALTH;
  player->energy = PLAYER_INITIAL_ENERGY;
  player->font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 64);
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
  return 0;
}

int Player_Render(SDL_Renderer *renderer, Player *player) 
{
  // render health
  char healthText[12];
  sprintf(healthText, "Health: %d", player->health);
  TTF_SetFontSize(player->font, 24);
  Text_Render(renderer, player->font, healthText, 32, SCREEN_HEIGHT - 192, (SDL_Color){255, 255, 255});

  // render energy
  char energyText[8];
  sprintf(energyText, "Mana: %d", player->energy);
  Text_Render(renderer, player->font, energyText, 32, SCREEN_HEIGHT - 160, (SDL_Color){255, 255, 255});

  return 0;
}
