#include "hand.h"
#include "card.h"
#include "screen.h"

int Hand_Init(Hand *hand, int max_size) {
  hand->size = 0;
  hand->max_size = max_size;
  hand->cards = (Card **)malloc(sizeof(Card *) * max_size);

  if (hand->cards == NULL) {
    // Memory allocation failed
    return -1;
  }

  for (int i = 0; i < max_size; i++) {
    hand->cards[i] = NULL;
  }

  return 0;
}

int Hand_AddCard(Hand *hand, Card *card, int index) {
  if (index + 1 > hand->max_size) {
    return -1;
  }

  hand->cards[index] = card;
  hand->size++;

  return 0;
}

int Hand_RemoveCard(Hand *hand, int index) 
{
  if (index + 1 > hand->max_size) {
    return -1;
  }

  hand->cards[index] = NULL;
  hand->size--;

  return 0;
}

int Hand_MakeActive(Hand *hand, int index)
{
  if (index + 1 > hand->max_size) {
    return -1;
  }

  hand->activeCard = hand->cards[index];
  return 0;
}

int Hand_MakeInactive(Hand *hand)
{
  hand->activeCard = NULL;
  return 0;
}

void Hand_Render(SDL_Renderer *renderer, Hand *hand, int x, int y) {
  for (int i = 0; i < hand->size; i++) {
    Card_Render(renderer, hand->cards[i], x + (CARD_WIDTH * i) + (HAND_MARGIN * i), y);
  }
}

int Hand_Cleanup(Hand *hand) 
{
  free(hand->cards);
  return 0;
}