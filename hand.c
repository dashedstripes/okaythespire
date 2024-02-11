#include "hand.h"
#include "card.h"
#include "screen.h"
#include "text.h"
#include "button.h"

int Hand_Init(Hand *hand, int max_size) {
  hand->size = 0;
  hand->max_size = max_size;
  hand->cards = (Card **)malloc(sizeof(Card *) * max_size);
  hand->models = (struct CardModel **)malloc(sizeof(struct CardModel *) * max_size);
  hand->x = (SCREEN_WIDTH - ((CARD_WIDTH * max_size) + (HAND_MARGIN * (max_size - 1)))) / 2;
  hand->y = SCREEN_HEIGHT - CARD_HEIGHT - HAND_MARGIN;
  hand->button = NULL;

  if (hand->cards == NULL) {
    // Memory allocation failed
    return -1;
  }

  if(hand->models == NULL) {
    return -1;
  }

  for (int i = 0; i < max_size; i++) {
    hand->cards[i] = NULL;
    hand->cards[i]->model = NULL;
  }

  return 0;
}

int Hand_AddCard(Hand *hand, Card *card, struct CardModel *model, int index) {
  if (index + 1 > hand->max_size) {
    return -1;
  }
  
  hand->size++;
  
  hand->cards[index] = card;
  hand->cards[index]->model = model;
  hand->cards[index]->model->x = hand->x + (index * (CARD_WIDTH + HAND_MARGIN));
  hand->cards[index]->model->y = hand->y;

  return 0;
}

int Hand_MakeActive(Hand *hand, int index)
{
  if (index + 1 > hand->max_size) {
    return -1;
  }

  for(int i = 0; i < hand->size; i++) {
    if(hand->cards[i] != NULL) {
      if(hand->cards[i] != hand->cards[index]) {
        Card_Toggle(hand->cards[i], hand->cards[i]->model, 0);
      }
    }
  }

  hand->activeCard = hand->cards[index];
  return 0;
}

int Hand_MakeInactive(Hand *hand, int index)
{
  hand->activeCard = NULL;
  return 0;
}

void Hand_RemoveCard(Hand *hand, Card *card) {
  // remove the card from the hand
  for(int i = 0; i < hand->size; i++) {
    if(hand->cards[i] == card) {
      hand->cards[i] = NULL;
      hand->cards[i]->model = NULL;
      hand->size--;
    }
  }

  hand->x = (SCREEN_WIDTH - ((CARD_WIDTH * hand->size) + (HAND_MARGIN * (hand->size - 1)))) / 2;

  // shift the cards to the left
  for(int i = 0; i < hand->size; i++) {
    if(hand->cards[i] == NULL) {
      for(int j = i; j < hand->size; j++) {
        hand->cards[j] = hand->cards[j + 1];
        hand->models[j] = hand->models[j + 1];
      }
    }
  }

  // reset the x positions of the cards
  for(int i = 0; i < hand->size; i++) {
    hand->cards[i]->model->x = hand->x + (i * (CARD_WIDTH + HAND_MARGIN));
  }
}

void Hand_DeactivateAllCards(Hand *hand)
{
  for(int i = 0; i < hand->size; i++) {
    if(hand->cards[i] != NULL) {
      Card_Toggle(hand->cards[i], hand->cards[i]->model, 0);
    }
  }

  hand->activeCard = NULL;
}

void Hand_Update(Hand *hand, float deltaTime) 
{
  for (int i = 0; i < hand->size; i++) {
    if (hand->cards[i] != NULL) {
      Card_Update(hand->cards[i], hand->cards[i]->model, deltaTime);
    }
  }
}

void Hand_Render(SDL_Renderer *renderer, Hand *hand, int x, int y, TTF_Font *font) {
  for (int i = 0; i < hand->size; i++) {
    Card_Render(renderer, hand->cards[i], hand->cards[i]->model, font);
  }

  if(hand->activeCard != NULL) {
    Button_Render(renderer, hand->button, font);
  }
}

int Hand_Cleanup(Hand *hand) 
{
  free(hand->models);
  free(hand->cards);
  return 0;
}