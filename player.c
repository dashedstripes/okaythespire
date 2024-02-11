#include "player.h"
#include "enemy.h"
#include "deck.h"
#include "card.h"
#include "screen.h"

int Player_Init(Player *player) 
{
  player->handCapacity = 5;
  player->handSize = 0;
  player->hand = (Card**)malloc(sizeof(Card*) * player->handCapacity);
  player->activeCard = NULL;
  player->health = PLAYER_INITIAL_HEALTH;
  player->energy = PLAYER_INITIAL_ENERGY;
  player->block = 0;
  return 0;
}

void Player_AddCard(Player *player, Card *card, int index) 
{
  player->hand[index] = card;
  player->handSize++;

  int lengthOfAllCards = (player->handCapacity * CARD_WIDTH) + ((player->handCapacity - 1) * 20);
  int handStartPosition = (SCREEN_WIDTH - lengthOfAllCards) / 2;

  player->hand[index]->model->x = handStartPosition + ((index * CARD_WIDTH) + (index * 20) + 20);
  player->hand[index]->model->y = SCREEN_HEIGHT - CARD_HEIGHT - 20;
}

int Player_SelectCard(Player *player, int cardIndex) 
{
  player->activeCard = player->hand[cardIndex];
  return 0;
}

int Player_UseCard(Player *player, Enemy *enemy) 
{
  if (player->energy < 1) 
  {
    return -1;
  }

  if(player->activeCard == NULL)
  {
    return -1;
  }

  if(player->activeCard->type == ATTACK_CARD)
  {
    enemy->health -= player->activeCard->value;
  }

  if(player->activeCard->type == BLOCK_CARD)
  {
    player->block += player->activeCard->value;
  }

  player->energy -= player->activeCard->cost;
  
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

  // render block
  char blockText[12];
  sprintf(blockText, "Block: %d", player->block);
  TTF_SetFontSize(font, 24);
  TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
  SDL_Surface *blockSurface = Text_Create(font, blockText, (SDL_Color){255, 255, 255});
  Text_Render(renderer, blockSurface, 32, SCREEN_HEIGHT - 128);

  // render hand
  for (int i = 0; i < player->handSize; i++) 
  {
    if (player->hand[i] != NULL) 
    {
      Card_Render(renderer, player->hand[i], font);
    }
  }

  return 0;
}
