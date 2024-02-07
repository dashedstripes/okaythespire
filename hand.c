#include "hand.h"
#include "card.h"

int Hand_Init(Hand *hand, int max_size, int x, int y) {
  hand->size = 0;
  hand->x = x;
  hand->y = y;
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

  card->x = hand->x + (card->w * index) + (HAND_MARGIN * index);
  card->y = hand->y;

  hand->cards[index] = card;
  hand->size++;

  return 0;
}

void Hand_Render(SDL_Renderer *renderer, Hand *hand) {
  for (int i = 0; i < hand->size; i++) {
    Card_Render(renderer, hand->cards[i]);
  }
}

int Hand_Cleanup(Hand *hand) 
{
  free(hand->cards);
  return 0;
}