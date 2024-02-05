#pragma once

#include "card.h"

typedef struct {
  Card** cards;
  int size;
} Deck;

void Deck_Init(Deck* deck, int size);
int Deck_AddCard(Deck* deck, Card* card, int index);