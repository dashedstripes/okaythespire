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
  SDL_Surface *healthSurface = Text_Create(enemy->font, healthText, (SDL_Color){255, 255, 255});
  Text_Render(renderer, healthSurface, SCREEN_WIDTH - (healthSurface->w + 32), 32);

  return 0;
}