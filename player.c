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
  return 0;
}

int Player_SelectCard(Player *player, int cardIndex) 
{
  player->hand->activeCard = player->hand->cards[cardIndex];
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

  player->energy -= player->hand->cards[cardIndex]->cost;
  return 0;
}

int Player_Render(SDL_Renderer *renderer, Player *player, TTF_Font *font) 
{
  // render health
  char healthText[12];
  sprintf(healthText, "Health: %d", player->health);
  TTF_SetFontSize(font, 24);
  TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
  SDL_Surface *healthSurface = Text_Create(font, healthText, (SDL_Color){255, 255, 255});
  Text_Render(renderer, healthSurface, 32, SCREEN_HEIGHT - 192);

  // // render energy
  char energyText[8];
  sprintf(energyText, "Mana: %d", player->energy);
  TTF_SetFontSize(font, 24);
  TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
  SDL_Surface *energySurface = Text_Create(font, energyText, (SDL_Color){255, 255, 255});
  Text_Render(renderer, energySurface, 32, SCREEN_HEIGHT - 160);

  return 0;
}
