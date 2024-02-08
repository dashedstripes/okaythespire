#include "deck.h"
#include "card.h"

void Deck_Init(Deck* deck, int size)
{
  deck->size = 0;
  deck->cards = NULL;
}

int Deck_AddCard(Deck* deck, Card* card, int index)
{
  Card** newCards = NULL;

  if(deck->cards == NULL)
  {
    newCards = (Card**)malloc(sizeof(Card*));
  }
  else 
  {
    newCards = (Card**)malloc(sizeof(Card*) * (deck->size + 1));
    for (int i = 0; i < deck->size; i++)
    {
      newCards[i] = deck->cards[i];
    }
    free(deck->cards);
  }

  deck->cards = newCards;
  deck->cards[index] = card;
  deck->size++;
  return 0;
}

int Deck_Cleanup(Deck* deck)
{
  if(deck->cards != NULL)
  {
    Card_Cleanup(deck->cards[0]);
    free(deck->cards);
  }
  return 0;
}