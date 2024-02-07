#pragma once

#include "card.h"

#define HAND_MARGIN 20

typedef struct {
  Card **cards;
  int size;
  int max_size;
  int x;
  int y;
} Hand;

int Hand_Init(Hand *hand, int max_size, int x, int y);
int Hand_AddCard(Hand *hand, Card *card, int index);
void Hand_Render(SDL_Renderer *renderer, Hand *hand);
int Hand_Cleanup(Hand *hand);
