#include "enemy.h"
#include "hand.h"
#include "deck.h"
#include "text.h"
#include "screen.h"

int Enemy_Init(Enemy *enemy) 
{
  enemy->deck = NULL;
  enemy->hand = NULL;
  enemy->health = 100;
  enemy->energy = 3;
  enemy->font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 64);
  return 0;
}

int Enemy_Render(SDL_Renderer *renderer, Enemy *enemy) 
{
  // render health
  char healthText[20];
  sprintf(healthText, "Enemy Health: %d", enemy->health);
  TTF_SetFontSize(enemy->font, 24);
  Text_Render(renderer, enemy->font, healthText, SCREEN_WIDTH - 256, 32, (SDL_Color){255, 255, 255});

  // // render energy
  // char energyText[4];
  // sprintf(energyText, "%d", enemy->energy);
  // Text_Render(renderer, enemy->font, energyText, 10, 30, (SDL_Color){255, 255, 255});

  return 0;
}