#include "deck.h"
#include "card.h"

const int DECK_MARGIN = 20;

int Deck_Init(Deck *deck, int max_size)
{
  deck->size = 0;
  deck->x = 0;
  deck->y = 0;
  deck->max_size = max_size;
  deck->cards = (Card **)malloc(sizeof(Card *) * max_size);

  if (deck->cards == NULL) {
    // Memory allocation failed
    return -1;
  }


  for (int i = 0; i < max_size; i++) {
    deck->cards[i] = NULL; // Assign some value, e.g., i * 2
  }

  return 0;
}

int Deck_AddCard(Deck *deck, Card *card, int index)
{
  if(index + 1 > deck->max_size)
  {
    return -1;
  }

  card->x = index * (deck->x + card->w + DECK_MARGIN);
  card->y = deck->y;

  deck->cards[index] = card;
  deck->size++;

  return 0;
}

void Deck_Render(SDL_Renderer *renderer, Deck *deck)
{
  for(int i = 0; i < deck->size; i++)
  {
    Card_Render(renderer, deck->cards[i]);
  }
}