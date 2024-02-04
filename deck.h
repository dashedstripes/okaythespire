#pragma once

#include "card.h"

typedef struct {
  Card **cards;
  int size;
  int max_size;
  int x;
  int y;
} Deck;

int Deck_Init(Deck *deck, int max_size);
int Deck_AddCard(Deck *deck, Card *card, int index);
void Deck_Render(SDL_Renderer *renderer, Deck *deck);