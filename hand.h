#ifndef HAND_H
#define HAND_H

#include "card.h"
#include "button.h"

#define HAND_MARGIN 20

typedef struct {
  Card **cards;
  struct CardModel **models;
  int size;
  int max_size;
  Card *activeCard;
  float x;
  float y;
  Button *button;
} Hand;

int Hand_Init(Hand *hand, int max_size);
int Hand_AddCard(Hand *hand, Card *card, struct CardModel *model, int index);
void Hand_Update(Hand *hand, float deltaTime);
void Hand_Render(SDL_Renderer *renderer, Hand *hand, int x, int y, TTF_Font *font);
int Hand_Cleanup(Hand *hand);
int Hand_MakeActive(Hand *hand, int index);
int Hand_MakeInactive(Hand *hand, int index);
void Hand_DeactivateAllCards(Hand *hand);

#endif