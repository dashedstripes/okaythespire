#pragma once

#include <SDL2/SDL.h>

typedef struct {
  int id;
  int x;
  int y;
  int w;
  int h;
} Card;

int Card_Init(Card *card, int id);
void Card_Render(SDL_Renderer *renderer, Card *card);
int Card_Intersect(Card *card, int x, int y);