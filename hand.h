#ifndef HAND_H
#define HAND_H

#include "card.h"

#define HAND_MARGIN 20

typedef struct {
  Card **cards;
  int size;
  int max_size;
} Hand;

int Hand_Init(Hand *hand, int max_size);
int Hand_AddCard(Hand *hand, Card *card, int index);
int Hand_RemoveCard(Hand *hand, int index);
void Hand_Render(SDL_Renderer *renderer, Hand *hand, int x, int y);
int Hand_Cleanup(Hand *hand);

#endif