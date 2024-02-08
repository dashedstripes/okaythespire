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
  return 0;
}

int Enemy_Render(SDL_Renderer *renderer, Enemy *enemy, TTF_Font *font) 
{
  // render health
  char healthText[20];
  sprintf(healthText, "Enemy Health: %d", enemy->health);
  TTF_SetFontSize(font, 24);
  TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
  SDL_Surface *healthSurface = Text_Create(font, healthText, (SDL_Color){255, 255, 255});
  Text_Render(renderer, healthSurface, SCREEN_WIDTH - (healthSurface->w + 32), 32);

  return 0;
}